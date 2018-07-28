#pragma once

#include <memory>

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"

#include "Resources/Gs/RGs.hpp"
#include "Resources/Ee/REe.hpp"
#include "Resources/Iop/RIop.hpp"
#include "Resources/Cdvd/RCdvd.hpp"
#include "Resources/Spu2/RSpu2.hpp"
#include "Resources/SbusFifoQueues.hpp"
#include "Resources/SbusRegisters.hpp"

/// PS2 Resources state.
/// Some resources have dependencies which need to be initialised after the
/// resources have been created - you will need to manually call initialise().
struct RResources
{
	RResources();

	/// Sub-components.
	REe ee;
	RGs gs;
	RIop iop;
	RSpu2 spu2;
	RCdvd cdvd;

	/// Various ROM banks. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp") and the EE Users Manual page 20. 
	/// BootROM (BIOS, 4MB). Allocated in EE & IOP physical memory space @ 0x1FC00000.
	/// ROM1 (DVD Player, 256kB). Allocated in EE & IOP physical memory space @ 0x1E000000.
	/// EROM (DVD Player extensions, 1,792kB). Allocated in EE physical memory space @ 0x1E040000.
	/// ROM2 (Chinese ROM extensions, 512kB). Allocated in EE physical memory space @ 0x1E400000.
	ArrayByteMemory boot_rom;
	ArrayByteMemory rom1;
	ArrayByteMemory erom;
	ArrayByteMemory rom2;

	/// Common resources.
	/// The SBUS/SIF resources (sub-system interface), facilitates communication to and from the EE/IOP.
	/// No official documentation, most code comes from PCSX2.
	/// The PS2SDK also contains some information: https://github.com/ps2dev/ps2sdk/blob/master/iop/kernel/include/sifman.h.
	SbusRegister_Mscom sbus_mscom; // Main - Sub-CPU command buffer.
	SizedWordRegister  sbus_smcom; // Sub - Main-CPU command buffer.
	SbusRegister_Msflg sbus_msflg; // Writes OR with the previous value.
	SbusRegister_Smflg sbus_smflg; // Writes NOT AND (clears) with the previous value.
	SbusRegister_F240  sbus_f240;  // Manipulates reads/writes with magic values.
	SizedWordRegister  sbus_f250;  
	SizedWordRegister  sbus_f260;  // Always set to 0.
	SbusRegister_F300  sbus_f300;  // TODO: related to psx sif2/gpu? Investigate (see PCSX2).
	SizedWordRegister  sbus_f380;  

	/// FIFO Queue registers, attached to both the EE and IOP DMAC channels.
	DmaFifoQueue<>       fifo_vif0;
	DmaFifoQueue<>       fifo_vif1;
	DmaFifoQueue<>       fifo_gif;
	DmaFifoQueue<>       fifo_fromipu;
	DmaFifoQueue<>       fifo_toipu;
	DmaFifoQueue<>       fifo_sif0;
	DmaFifoQueue<>       fifo_sif1;
	SbusFifoQueue_Sif2   fifo_sif2;
	DmaFifoQueue<>       fifo_frommdec;
	DmaFifoQueue<>       fifo_tomdec;
	DmaFifoQueue<>       fifo_cdvd;
	DmaFifoQueue<>       fifo_spu2c0;
	DmaFifoQueue<>       fifo_pio;
	DmaFifoQueue<>       fifo_otclear;
	DmaFifoQueue<>       fifo_spu2c1;
	DmaFifoQueue<>       fifo_dev9;
	DmaFifoQueue<>       fifo_fromsio2;
	DmaFifoQueue<>       fifo_tosio2;
};

/// Initialises the resources by filling in references, performing bus mappings, etc.
/// Only perform after RResources struct has been allocated!
/// Done by the core after a reset.
void initialise_resources(const std::unique_ptr<RResources> & r);