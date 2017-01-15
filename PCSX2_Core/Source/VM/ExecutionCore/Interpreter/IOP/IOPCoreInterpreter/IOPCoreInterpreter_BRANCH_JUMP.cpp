#include "stdafx.h"

#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/MIPS/LinkRegister32_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::IOP));

	if (source1Val == source2Val)
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));

	if (source1Val >= 0)
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));

	if (source1Val >= 0)
	{
		getResources()->IOP->IOPCore->R3000->LinkRegister->setLinkAddress();
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
	}
}

void IOPCoreInterpreter::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));

	if (source1Val > 0)
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));

	if (source1Val <= 0)
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));

	if (source1Val < 0)
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));

	if (source1Val < 0)
	{
		getResources()->IOP->IOPCore->R3000->LinkRegister->setLinkAddress();
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
	}
}

void IOPCoreInterpreter::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::IOP));

	if (source1Val != source2Val)
		getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::J()
{
	// JUMP(). No Exceptions.
	getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter::JR()
{
	// JUMP_REGISTER().
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCAbsolute(source1Reg->readWord(Context_t::IOP), 2);
}

void IOPCoreInterpreter::JAL()
{
	// JUMP_LINK(). No exceptions.
	getResources()->IOP->IOPCore->R3000->LinkRegister->setLinkAddress();
	getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter::JALR()
{
	// JUMP_LINK_REGISTER().
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWord(Context_t::IOP, static_cast<u32>(getResources()->IOP->IOPCore->R3000->PC->readWord(Context_t::IOP) + Constants::SIZE_MIPS_INSTRUCTION));
	getResources()->IOP->IOPCore->R3000->BD->setBranchDelayPCAbsolute(sourceReg->readWord(Context_t::IOP), 2);
}

