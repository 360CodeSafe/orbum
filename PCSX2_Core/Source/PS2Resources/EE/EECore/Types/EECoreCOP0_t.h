#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"
#include "Common/Types/MIPSCoprocessor/MIPSCoprocessor0_t.h"

/*
COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
See EE Core Users Manual page 62 onwards.
*/

class BitfieldRegister32_t;
class COP0RegisterReserved_t;
class EECoreCOP0Register_Index_t;
class EECoreCOP0Register_Random_t;
class EECoreCOP0Register_EntryLo0_t;
class EECoreCOP0Register_EntryLo1_t;
class EECoreCOP0Register_Context_t;
class EECoreCOP0Register_PageMask_t;
class EECoreCOP0Register_Wired_t;
class EECoreCOP0Register_BadVAddr_t;
class EECoreCOP0Register_Count_t;
class EECoreCOP0Register_EntryHi_t;
class EECoreCOP0Register_Compare_t;
class EECoreCOP0Register_Status_t;
class EECoreCOP0Register_Cause_t;
class COP0RegisterEPC_t;
class EECoreCOP0Register_PRId_t;
class EECoreCOP0Register_Config_t;
class EECoreCOP0Register_BadPAddr_t;
class EECoreCOP0Register_TagLo_t;
class EECoreCOP0Register_TagHi_t;
class EECoreCOP0Register_ErrorEPC_t;
class EECoreCOP0Register_BPC_t;
class EECoreCOP0Register_IAB_t;
class EECoreCOP0Register_IABM_t;
class EECoreCOP0Register_DAB_t;
class EECoreCOP0Register_DABM_t;
class EECoreCOP0Register_DVB_t;
class EECoreCOP0Register_DVBM_t;
class EECoreCOP0Register_PCCR_t;
class EECoreCOP0Register_PCR0_t;
class EECoreCOP0Register_PCR1_t;

class EECoreCOP0_t : public MIPSCoprocessor0_t, public PS2ResourcesSubobject
{
public:
	explicit EECoreCOP0_t(const PS2Resources_t* const PS2Resources);

	/*
	Checks if the EECore COP0 coprocessor is usable. 
	Can be used by the component calling this to raise a EECoreException_t(coprocessor unusable) if not available.
	*/
	bool isCoprocessorUsable() const override;

	/*
	Initalises the COP0 registers.
	*/
	void initalise() override;

	/*
	Functions to determine the CPU context. Uses the Status register.
	*/
	bool isOperatingUserMode() const override;
	bool isOperatingSupervisorMode() const override;
	bool isOperatingKernelMode() const override;

	/*
	EECore COP0 register implementations. Follows EE Core Users Manual.
	Note: Registers r24 and r25 have been split up into 7 and 3 registers respectively as per the docs, 
	       as it is not feasible to implement them as sub-registers.
	The new registers have been assigned register numbers from 32 -> 39 (for PCSX2 reference).
	*/
	// General registers.
	std::shared_ptr<EECoreCOP0Register_Index_t>		Index;	    // r0:  Index that specifies TLB entry for reading for writing.
	std::shared_ptr<EECoreCOP0Register_Random_t>	Random;	    // r1:  Pseudo-random index for TLB replacement.
	std::shared_ptr<EECoreCOP0Register_EntryLo0_t>  EntryLo0;   // r2:  Low half of TLB entry (for even PFN).
	std::shared_ptr<EECoreCOP0Register_EntryLo1_t>  EntryLo1;   // r3:  Low half of TLB entry (for odd PFN).
	std::shared_ptr<EECoreCOP0Register_Context_t>	Context;    // r4:  Pointer to PTE table.
	std::shared_ptr<EECoreCOP0Register_PageMask_t>  PageMask;   // r5:  Most significant part of the TLB entry (page size mark).
	std::shared_ptr<EECoreCOP0Register_Wired_t>		Wired;      // r6:  Number of wired TLB entries.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved7;  // r7:  Reserved.
	std::shared_ptr<EECoreCOP0Register_BadVAddr_t>  BadVAddr;   // r8:  Bad virtual address value (for exceptions).
	std::shared_ptr<EECoreCOP0Register_Count_t>		Count;      // r9:  Timer Compare.
	std::shared_ptr<EECoreCOP0Register_EntryHi_t>	EntryHi;    // r10: High half (Virtual page number and ASID) of TLB entry.
	std::shared_ptr<EECoreCOP0Register_Cause_t>		Cause;	    // r13: Result of last exception taken. NEED TO BE INITALISED BEFORE COMPARE!
	std::shared_ptr<EECoreCOP0Register_Compare_t>	Compare;    // r11: Timer reference value. CLEARS THE TIMER INTERRUPT BIT OF CAUSE WHEN WRITTEN TO!
	std::shared_ptr<EECoreCOP0Register_Status_t>	Status;     // r12: Processor Status Register.
	std::shared_ptr<COP0RegisterEPC_t>		        EPC;        // r14: Exception Program Counter.
	std::shared_ptr<EECoreCOP0Register_PRId_t>		PRId;       // r15: Processor Revision Identifier.
	std::shared_ptr<EECoreCOP0Register_Config_t>	Config;     // r16: Configuration Register.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved17; // r17: Reserved.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved18; // r18: Reserved.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved19; // r19: Reserved.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved20; // r20: Reserved.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved21; // r21: Reserved.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved22; // r22: Reserved.
	std::shared_ptr<EECoreCOP0Register_BadPAddr_t>  BadPAddr;   // r23: Bad Physical Address value (for exceptions).
												                // r24: See below for r24.
													            // r25: See below for r25.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved26; // r26: Reserved.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved27; // r27: Reserved.
	std::shared_ptr<EECoreCOP0Register_TagLo_t>		TagLo;      // r28: Low bits of the Cache Tag.
	std::shared_ptr<EECoreCOP0Register_TagHi_t>		TagHi;      // r29: High bits of the Cache Tag.
	std::shared_ptr<EECoreCOP0Register_ErrorEPC_t>  ErrorEPC;   // r30: Error Exception Program Counter.
	std::shared_ptr<COP0RegisterReserved_t>			Reserved31; // r31: Reserved.

	// Debug registers.
	std::shared_ptr<EECoreCOP0Register_BPC_t>		BPC;        // r24: Registers related to debug function.
	std::shared_ptr<EECoreCOP0Register_IAB_t>		IAB;        // r32: Instruction address breakpoint settings.
	std::shared_ptr<EECoreCOP0Register_IABM_t>		IABM;       // r33: Instruction address breakpoint settings.
	std::shared_ptr<EECoreCOP0Register_DAB_t>		DAB;	    // r34: Data address breakpoint settings.
	std::shared_ptr<EECoreCOP0Register_DABM_t>		DABM;	    // r35: Data address breakpoint settings.
	std::shared_ptr<EECoreCOP0Register_DVB_t>		DVB;	    // r36: Data value breakpoint settings.
	std::shared_ptr<EECoreCOP0Register_DVBM_t>		DVBM;	    // r37: Data value breakpoint settings.

	// Performance registers.
	std::shared_ptr<EECoreCOP0Register_PCCR_t>		PCCR;	    // r25: Performance counter and control register.
	std::shared_ptr<EECoreCOP0Register_PCR0_t>		PCR0;       // r38: Performance counter.
	std::shared_ptr<EECoreCOP0Register_PCR1_t>		PCR1;       // r39: Performance counter.

	// Array of above registers (needed by some EECore instructions to access by index). 
	// Generally you will never access registers directly through this, only the PS2 OS will.
	std::shared_ptr<BitfieldRegister32_t> Registers[PS2Constants::EE::EECore::COP0::NUMBER_REGISTERS];

	// Array of PCR0/PCR1, used by the MFPC/MTPC instructions.
	std::shared_ptr<BitfieldRegister32_t> PCRRegisters[PS2Constants::EE::EECore::COP0::NUMBER_PCR_REGISTERS];


};