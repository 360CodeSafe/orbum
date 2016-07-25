#pragma once

#include <memory>

#include "Globals.h"
#include "PS2Constants.h"

class MainMemory_t
{
public:
	MainMemory_t() : mainMemory(new u8[PS2Constants::EE::SIZE_MAIN_MEMORY])
	{
	}

	~MainMemory_t()
	{
		delete mainMemory;
	}

	INLINE void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(mainMemory);
	}
private:
	u8 *const mainMemory;
};