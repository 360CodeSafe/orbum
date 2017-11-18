#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Common/Types/Register/MapperHwordWordRegister.hpp"
#include "Common/Types/Mips/MipsCoprocessor.hpp"

#include "Resources/Ee/Vpu/VuCoreRegisters.hpp"

class EeCoreCop0;

/// A base class for a VU unit resource.
class VuCore_Base
{
public:
	VuCore_Base(const int core_id);

	/// ID of the VU.
	int core_id;

	/// VU floating point registers (VF) (128-bit) and integer registers (VI) (16-bit).
	/// See VU Users Manual page 18.
	SizedQwordRegister vf[Constants::EE::VPU::VU::NUMBER_VF_REGISTERS];
	SizedHwordRegister vi[Constants::EE::VPU::VU::NUMBER_VI_REGISTERS];

	/// ACC register. Used by instructions such as ADDA and MULA.
	/// See VU Users Manual page 33.
	SizedQwordRegister acc;

	/// I register. Used to store immediate values.
	/// See VU Users Manual page 33.
	SizedWordRegister i;

	/// Q register. Used to store division/sqrt values.
	/// See VU Users Manual page 34.
	SizedWordRegister q;

	/// R register. Used to store random numbers generated.
	/// See VU Users Manual page 34.
	SizedWordRegister r;

	/// P register. Used to store EFU result values.
	/// See VU Users Manual page 34.
	SizedWordRegister p;

	/// The Flag registers (MAC, Status and Clipping), used to hold special results from calculations.
	/// See VU Users Manual page 40.
	/// The MAC register is dependant on the Status register for special functionality.
	VuCoreRegister_Status   status;
	VuCoreRegister_Mac      mac;
	VuCoreRegister_Clipping clipping;

	/// PC (program counter) register for micro subroutines.
	/// Also known as the TPC (termination PC), treated as the same thing.
	/// Made to be 32-bit even though only 16-bits are used (bus maps easier).
	SizedWordRegister pc;

	/// The CMSAR register used for micro subroutine execution.
	/// See VU Users Manual page 202.
	VuCoreRegister_Cmsar cmsar;

	/// VU0 contains a physical memory map of its real working space (& mirrors) and the VU1 registers.
	/// For VU1, it is just a direct map of its real working space (needed to keep it OOP friendly).
	/// See EE Users Manual page 84.
	ByteBus bus;
	
	/// Mappers for the VI (Hword) registers to WordRegisters.
	/// Used by different things, eg: ccr registers for VU0 and bus mappings for VU1.
	MapperHwordWordRegister vi_32[Constants::EE::VPU::VU::NUMBER_VI_REGISTERS];
};

/// Represents VU0.
/// It is attached as a MIPS coprocessor to the EE Core, as COP2.
class VuCore_Vu0 : public VuCore_Base, public MipsCoprocessor
{
public:
	VuCore_Vu0(const int core_id);

	/// Check if this VU unit is usable in macro mode from the EE Core by
	/// checking the EE Core's COP0.Status.CU2 bit.
	bool is_usable() override;

	/// VU memory, defined on page 18 of the VU Users Manual.
	ArrayByteMemory memory_micro; // 4 KiB.
	ArrayByteMemory memory_mem; // 4 KiB.

	/// The CCR (control registers) array (32) needed for the CTC2 and CFC2 EE Core instructions.
	/// See VU Users Manual page 200 & 201.
	/// The first 16 registers are allocated to the VU0 VI registers, 
	/// with the last 16 registers allocated to various control registers.
	WordRegister * ccr[Constants::EE::VPU::VU::NUMBER_VU0_CCR_REGISTERS];

	/// Reference to the EE Core COP0 coprocessor, needed for the Status register.
	EeCoreCop0 * cop0;
};

/// Represents VU1.
class VuCore_Vu1 : public VuCore_Base
{
public:
	VuCore_Vu1(const int core_id);

	/// VU memory, defined on page 18 of the VU Users Manual.
	ArrayByteMemory memory_micro; // 16 KiB.
	ArrayByteMemory memory_mem; // 16 KiB.
};