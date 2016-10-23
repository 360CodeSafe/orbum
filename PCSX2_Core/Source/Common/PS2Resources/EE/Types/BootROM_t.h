#pragma once

#include <string>

#include "Common/PS2Resources/Types/MappedMemory/ROMappedMemory_t.h"

/*
A memory object that exposes the loadBIOS() function to load in the BIOS image.
It should be loaded before emulation starts.
*/
class BootROM_t : public ROMappedMemory_t
{
public:
	BootROM_t();

	/*
	Reads in the BIOS at the given path and stores it in the raw underlying memory.
	*/
	void loadBIOS(const std::string & biosPath) const;
};

