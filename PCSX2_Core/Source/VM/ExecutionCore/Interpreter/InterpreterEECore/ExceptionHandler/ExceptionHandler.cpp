#include "stdafx.h"

#include <stdexcept>

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/ExceptionHandler/ExceptionHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/Types/PCRegister32_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"

ExceptionHandler::ExceptionHandler(const VMMain *const vmMain) : 
	VMExecutionCoreComponent(vmMain), 
	mPS2Exception(nullptr)
{
}

void ExceptionHandler::checkExceptionQueue()
{
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	if (!ExceptionQueue->empty())
	{
		handleException(ExceptionQueue->front());
		ExceptionQueue->pop();
	}
}

void ExceptionHandler::handleException(const EECoreException_t& PS2Exception)
{
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	// Set the PS2Exception pointer.
	mPS2Exception = &PS2Exception;

	// Get the exception properties.
	auto& exceptionProperties = ExceptionProperties[static_cast<size_t>(mPS2Exception->mExType)];

#if defined(BUILD_DEBUG)
	// Debug print exception type.
	logDebug("(%s, %d) ExceptionHandler called! Type = %s", __FILENAME__, __LINE__, exTypeStrings[static_cast<size_t>(PS2Exception.mExType)]);
#endif

	// Call the exception specific handler contained in the ExceptionProperties_t.
	(this->*exceptionProperties.ExceptionHandlerFunction)();

	// Call the Level 1 or Level 2 exception handler based on the exception, or throw runtime_error if exception type/properties does not exist.
	switch(exceptionProperties.mLevel)
	{
	case 1:
		handleException_L1(exceptionProperties);
		break;
	case 2:
		handleException_L2(exceptionProperties);
		break;
	default:
		throw std::runtime_error("PS2Exception parsed contained an unknown exception type.");
	}
}

void ExceptionHandler::handleException_L1(const ExceptionProperties_t & exceptionProperties) const
{
	// Exception level 1 handler code. Adapted from EE Core Users Manual page 91.

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::ExcCode, exceptionProperties.mExeCode);

	// If already in exception handler (EXL == 1), do not update EPC and Cause.BD. Also use general exception handler vector.
	if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::EXL) == 1)
	{
		vectorOffset = PS2Constants::EE::EECore::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	// Normal exception processing.
	else
	{
		// Set EPC and Cause.BD fields.
		if (getVM()->getResources()->EE->EECore->R5900->isInBranchDelaySlot()) // Check if in the branch delay slot.
		{
			u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue() - 4;
			getVM()->getResources()->EE->EECore->COP0->EPC->setFieldValue(RegisterEPC_t::Fields::EPC, pcValue);
			getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD, 1);
		}
		else
		{
			u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue();
			getVM()->getResources()->EE->EECore->COP0->EPC->setFieldValue(RegisterEPC_t::Fields::EPC, pcValue);
			getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD, 0);
		}

		// Set to kernel mode and disable interrupts.
		getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(RegisterStatus_t::Fields::EXL, 1);

		// Select the vector to use (set vectorOffset).
		if (exceptionProperties.mExceptionInfo == EECoreException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD
			|| exceptionProperties.mExceptionInfo == EECoreException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD)
		{
			vectorOffset = PS2Constants::EE::EECore::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (exceptionProperties.mExceptionInfo == EECoreException_t::ExType::EX_INTERRUPT)
		{
			vectorOffset = PS2Constants::EE::EECore::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else
		{
			vectorOffset = PS2Constants::EE::EECore::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::BEV) == 1)
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::Exceptions::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		} 
		else
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::Exceptions::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}

void ExceptionHandler::handleException_L2(const ExceptionProperties_t & exceptionProperties) const
{
	// Exception level 2 handler code. Adapted from EE Core Users Manual page 92.

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.EXC2 value.
	getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::EXC2, exceptionProperties.mEXC2);

	// Set EPC and Cause.BD fields.
	if (getVM()->getResources()->EE->EECore->R5900->isInBranchDelaySlot()) // Check if in the branch delay slot.
	{
		u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue() - 4;
		getVM()->getResources()->EE->EECore->COP0->ErrorEPC->setFieldValue(RegisterErrorEPC_t::Fields::ErrorEPC, pcValue);
		getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD2, 1);
	}
	else
	{
		u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue();
		getVM()->getResources()->EE->EECore->COP0->ErrorEPC->setFieldValue(RegisterErrorEPC_t::Fields::ErrorEPC, pcValue);
		getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD2, 0);
	}

	// Set to kernel mode and disable interrupts.
	getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(RegisterStatus_t::Fields::ERL, 1);

	// Select vector to use and set PC to use it.
	if (exceptionProperties.mExceptionInfo == EECoreException_t::ExType::EX_NMI 
		|| exceptionProperties.mExceptionInfo == EECoreException_t::ExType::EX_RESET) 
	{
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::Exceptions::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
	}
	else
	{
		if (exceptionProperties.mExceptionInfo == EECoreException_t::ExType::EX_PERFORMANCE_COUNTER)
		{
			vectorOffset = PS2Constants::EE::EECore::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_COUNTER;
		}
		else if (exceptionProperties.mExceptionInfo == EECoreException_t::ExType::EX_DEBUG)
		{
			vectorOffset = PS2Constants::EE::EECore::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_DEBUG;
		}
		else
		{
			// Use V_TLB_REFIL (offset 0x00000000) (should get optimised out).
			vectorOffset = PS2Constants::EE::EECore::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::DEV) == 1)
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::Exceptions::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		}
		else
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::Exceptions::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}

void ExceptionHandler::EX_HANDLER_RESET()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	// Initalise all of the COP0 registers.
	for (auto i = 0; i < PS2Constants::EE::EECore::COP0::NUMBER_REGISTERS; i++)
		COP0->Registers[i]->initaliseAllFields();
	
	// Other funcionality in "operation", just in case the inital values are different.
	COP0->Status->setFieldValue(RegisterStatus_t::Fields::ERL, 1);
	COP0->Status->setFieldValue(RegisterStatus_t::Fields::BEV, 1);
	COP0->Status->setFieldValue(RegisterStatus_t::Fields::BEM, 0);

	COP0->Cause->setFieldValue(RegisterCause_t::Fields::EXC2, 0);

	COP0->Config->setFieldValue(RegisterConfig_t::Fields::DIE, 0);
	COP0->Config->setFieldValue(RegisterConfig_t::Fields::ICE, 0);
	COP0->Config->setFieldValue(RegisterConfig_t::Fields::DCE, 0);
	COP0->Config->setFieldValue(RegisterConfig_t::Fields::NBE, 0);
	COP0->Config->setFieldValue(RegisterConfig_t::Fields::BPE, 0);

	COP0->Random->setFieldValue(RegisterRandom_t::Fields::Random, 47);

	COP0->Wired->setFieldValue(RegisterWired_t::Fields::Wired, 0);

	// I think this is a typo. In manual it says CCR.CTE where it should be PCCR.CTE.
	COP0->PCCR->setFieldValue(RegisterPCCR_t::Fields::CTE, 0);

	COP0->BPC->setFieldValue(RegisterBPC_t::Fields::IAE, 0);
	COP0->BPC->setFieldValue(RegisterBPC_t::Fields::DRE, 0);
	COP0->BPC->setFieldValue(RegisterBPC_t::Fields::DWE, 0);

	// TODO: Set cache flags (data and instruction caches) as described.
}

void ExceptionHandler::EX_HANDLER_NMI()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;
	COP0->Status->setFieldValue(RegisterStatus_t::Fields::ERL, 1);
	COP0->Status->setFieldValue(RegisterStatus_t::Fields::BEV, 1);
}

void ExceptionHandler::EX_HANDLER_PERFORMANCE_COUNTER()
{
	// No additional processing needed.
}

void ExceptionHandler::EX_HANDLER_DEBUG()
{
	// No additional processing needed.
}

void ExceptionHandler::EX_HANDLER_INTERRUPT()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;
	
	// The EE Core Users Manual page 99 mentions that if an interrupt signal is asserted and deasserted in a very short time, the Cause.IP[i] may not
	//  be reliable to rely on for information. This may need investigation if the timing is critical to some games.
	// TODO: check for timing issues.
	COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP2, mPS2Exception->mIntExceptionInfo->mInt2);
	COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP3, mPS2Exception->mIntExceptionInfo->mInt3);
	COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP7, mPS2Exception->mIntExceptionInfo->mInt7);
}

void ExceptionHandler::EX_HANDLER_TLB_MODIFIED()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(RegisterBadVAddr_t::Fields::BadVAddr, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::PTEBase, mPS2Exception->mTLBExceptionInfo->mPageTableAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::BadVPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::ASID, mPS2Exception->mTLBExceptionInfo->mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
}

void ExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(RegisterBadVAddr_t::Fields::BadVAddr, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::PTEBase, mPS2Exception->mTLBExceptionInfo->mPageTableAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::BadVPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::ASID, mPS2Exception->mTLBExceptionInfo->mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
	COP0->Random->setFieldValue(RegisterRandom_t::Fields::Random, mPS2Exception->mTLBExceptionInfo->mTLBIndex);
}

void ExceptionHandler::EX_HANDLER_TLB_REFILL_STORE()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(RegisterBadVAddr_t::Fields::BadVAddr, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::PTEBase, mPS2Exception->mTLBExceptionInfo->mPageTableAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::BadVPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::ASID, mPS2Exception->mTLBExceptionInfo->mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
	COP0->Random->setFieldValue(RegisterRandom_t::Fields::Random, mPS2Exception->mTLBExceptionInfo->mTLBIndex);
}

void ExceptionHandler::EX_HANDLER_TLB_INVALID_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;

	COP0->BadVAddr->setFieldValue(RegisterBadVAddr_t::Fields::BadVAddr, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::PTEBase, mPS2Exception->mTLBExceptionInfo->mPageTableAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::BadVPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::ASID, mPS2Exception->mTLBExceptionInfo->mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
	COP0->Random->setFieldValue(RegisterRandom_t::Fields::Random, mPS2Exception->mTLBExceptionInfo->mTLBIndex);
}

void ExceptionHandler::EX_HANDLER_TLB_INVALID_STORE()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(RegisterBadVAddr_t::Fields::BadVAddr, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::PTEBase, mPS2Exception->mTLBExceptionInfo->mPageTableAddress);
	COP0->Context->setFieldValue(RegisterContext_t::Fields::BadVPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::ASID, mPS2Exception->mTLBExceptionInfo->mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
	COP0->Random->setFieldValue(RegisterRandom_t::Fields::Random, mPS2Exception->mTLBExceptionInfo->mTLBIndex);
}

void ExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(RegisterBadVAddr_t::Fields::BadVAddr, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress);
	COP0->Context->setRegisterValue(0);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, 0);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
}

void ExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(RegisterBadVAddr_t::Fields::BadVAddr, mPS2Exception->mTLBExceptionInfo->mPS2VirtualAddress);
	COP0->Context->setRegisterValue(0);
	COP0->EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, 0);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
}

void ExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void ExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void ExceptionHandler::EX_HANDLER_SYSTEMCALL()
{
	// No additional processing needed.
}

void ExceptionHandler::EX_HANDLER_BREAK()
{
	// No additional processing needed.
}

void ExceptionHandler::EX_HANDLER_RESERVED_INSTRUCTION()
{
	// No additional processing needed.
}

void ExceptionHandler::EX_HANDLER_COPROCESSOR_UNUSABLE()
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;

	COP0->Cause->setFieldValue(RegisterCause_t::Fields::CE, mPS2Exception->mCOPExceptionInfo->mCOPUnusable);
}

void ExceptionHandler::EX_HANDLER_OVERFLOW()
{
	// No additional processing needed.
}

void ExceptionHandler::EX_HANDLER_TRAP()
{
	// No additional processing needed.
}
