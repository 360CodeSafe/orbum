#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::LB()
{
	// Rd = MEM[SB]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordS(0, static_cast<s64>(getMMUHandler()->readByteS(PS2VirtualAddress)));
}

void InterpreterEECore::LBU()
{
	// Rd = MEM[UB]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordU(0, static_cast<u64>(getMMUHandler()->readByteU(PS2VirtualAddress)));
}

void InterpreterEECore::LD()
{
	// Rd = MEM[UD]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordU(0, getMMUHandler()->readDwordU(PS2VirtualAddress));
}

void InterpreterEECore::LDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UD] = Rd. Exceptions generated through other components.
	// Unaligned memory read. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned read. LDL is to be used with LDR, to read in a full 64-bit value.
	// LDL reads in the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDR.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = sourceReg->readWordU(0) + imm;
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = getMMUHandler()->readDwordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((8 - (offset + 1)) * 8); // A shift value used thoughout.
	u64 MSBMask = Constants::VALUE_U64_MAX >> MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 MSBValue = (alignedValue & MSBMask) << MSBShift; // Calculate the MSB value part.

	u64 keepMask = ~(MSBMask << MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeDwordU(0, (destReg->readDwordU(0) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.
}

void InterpreterEECore::LDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Exceptions generated through other components.
	// Unaligned memory read. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned read. LDR is to be used with LDL, to read in a full 64-bit value.
	// LDR reads in the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDL.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = sourceReg->readWordU(0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = getMMUHandler()->readDwordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u64 LSBMask = Constants::VALUE_U64_MAX << LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 LSBValue = (alignedValue & LSBMask) >> LSBShift; // Calculate the LSB value part.

	u64 keepMask = ~(LSBMask >> LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeDwordU(0, (destReg->readDwordU(0) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.
}

void InterpreterEECore::LH()
{
	// Rd = MEM[SH]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordS(0, static_cast<s64>(getMMUHandler()->readHwordS(PS2VirtualAddress)));
}

void InterpreterEECore::LHU()
{
	// Rd = MEM[UH]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordU(0, static_cast<u64>(getMMUHandler()->readHwordU(PS2VirtualAddress)));
}

void InterpreterEECore::LUI()
{
	// Rd = Imm << 16. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	destReg->writeDwordS(0, static_cast<s64>(imm << 16));
}

void InterpreterEECore::LW()
{
	// Rd = MEM[SW]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordS(0, static_cast<s64>(getMMUHandler()->readWordS(PS2VirtualAddress)));
}

void InterpreterEECore::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Exceptions generated through other components.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWL is to be used with LWR, to read in a full 32-bit value.
	// LWL reads in the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDR.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = sourceReg->readWordU(0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = getMMUHandler()->readWordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((4 - (offset + 1)) * 8); // A shift value used thoughout.
	u32 MSBMask = Constants::VALUE_U32_MAX >> MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 MSBValue = (alignedValue & MSBMask) << MSBShift; // Calculate the MSB value part.

	u32 keepMask = ~(MSBMask << MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeDwordS(0, static_cast<s64>(static_cast<s32>((destReg->readWordU(0) & keepMask) | MSBValue))); // Calculate the new desination register value and write to it.
}

void InterpreterEECore::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Exceptions generated through other components.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWR is to be used with LWL, to read in a full 32-bit value.
	// LWR reads in the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LWL.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = sourceReg->readWordU(0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = getMMUHandler()->readWordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u32 LSBMask = Constants::VALUE_U32_MAX << LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 LSBValue = (alignedValue & LSBMask) >> LSBShift; // Calculate the LSB value part.

	u32 keepMask = ~(LSBMask >> LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeDwordS(0, static_cast<s64>(static_cast<s32>((destReg->readWordU(0) & keepMask) | LSBValue))); // Calculate the new desination register value and write to it.
}

void InterpreterEECore::LWU()
{
	// Rd = MEM[UW]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordU(0, static_cast<u64>(getMMUHandler()->readWordU(PS2VirtualAddress)));
}

void InterpreterEECore::LQ()
{
	// Rd = MEM[UQ]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = (sourceReg->readWordU(0) + imm) & (~static_cast<u32>(0xF)); // Strip the last 4 bits, as the access must be aligned (the documentation says to do this).

	// TODO: Im not sure if this is correct for big-endian.
	destReg->writeDwordU(0, getMMUHandler()->readDwordU(PS2VirtualAddress)); // Get first 8 bytes (bytes 0 -> 7).
	destReg->writeDwordU(1, getMMUHandler()->readDwordU(PS2VirtualAddress + 8)); // Get second 8 bytes (bytes 8 -> 15).
}

void InterpreterEECore::LWC1()
{
	// Ft = MEM[UQ]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getIRt()]; // Ft
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = (sourceReg->readWordU(0) + imm);
	destReg->writeWordU(getMMUHandler()->readWordU(PS2VirtualAddress));
}