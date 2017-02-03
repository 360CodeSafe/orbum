#include "stdafx.h"

#include <memory>

#include "Common/Types/Memory/Memory_t.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"

IOPCore_t::IOPCore_t() :
	R3000(std::make_shared<IOPCoreR3000_t>()),
	COP0(std::make_shared<IOPCoreCOP0_t>()),
	ScratchpadMemory(std::make_shared<Memory_t>(Constants::IOP::IOPCore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, "IOP Core Scratchpad Memory"))
{
}
