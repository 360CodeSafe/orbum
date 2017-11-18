#include "Resources/Ee/REe.hpp"

REe::REe() :
	bus(16, 2), // Number of page index bits optimised for minimum memory usage.
	main_memory(Constants::EE::MainMemory::SIZE_MAIN_MEMORY),
	unknown_1a000000(0x10000),
	memory_f410(0x04),
	memory_f450(0xB0)
{
}