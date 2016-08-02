#pragma once

#include "Common/PS2 Resources/EE/EE_t.h"
#include "Common/PS2 Resources/MainMemory/MainMemory_t.h"
#include "Common/PS2 Resources/BootROM/BootRom.h"

/*
TODO: finish writing documentation.
PS2Resources_t delares all of the resources attached to the PS2, such as the EE, GS, memory and more.
All of the reads and writes to the PS2 system state will come to here.

You should only ever need to create an object of this type from which you can access everything, 
 which is ordered by components in the documentation groups, such as PS2Resources.EE.EECore.R5900.GPR.r1.

PS2Resources_t SHOULD NOT be allocated on the stack - this object hierarchy can get quite big (even without the memory allocated),
 which is why it should be used on the heap. As such, you should create this object through std::shared_ptr (std::make_shared) or similar.
*/

class PS2Resources_t
{
public:

	// The EE structure.
	EE_t EE;
	
	// Main Memory (32MB)
	MainMemory_t MainMemory;

	// Boot ROM (4MB)
	BootROM_t BootROM;

private:
	
};