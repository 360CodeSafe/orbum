#include "stdafx.h"

#include <fstream>

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/HwordMemory_t.h"

HwordMemory_t::HwordMemory_t(const size_t byteSize) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mMemoryByteSize(byteSize),
	mMemory(mMemoryByteSize / 2, 0),
	mMnemonic("")
{
	// Check that mMemoryByteSize is a multiple of 2 (Constants::NUMBER_BYTES_IN_HWORD).
	if ((mMemoryByteSize % Constants::NUMBER_BYTES_IN_HWORD) != 0)
		throw std::runtime_error("HwordMemory_t was constructed with a bad byteSize parameter (not a multiple of 2).");

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mMemorySize > 0)
		log(Debug, "(%s, %d) HwordMemory allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMemory.data(), mMemorySize);
#endif
}

HwordMemory_t::HwordMemory_t(const size_t byteSize, const char * mnemonic) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mMemoryByteSize(byteSize),
	mMemory(mMemoryByteSize / 2, 0),
	mMnemonic(mnemonic)
{
	// Check that mMemoryByteSize is a multiple of 2 (Constants::NUMBER_BYTES_IN_HWORD).
	if ((mMemoryByteSize % Constants::NUMBER_BYTES_IN_HWORD) != 0)
		throw std::runtime_error("HwordMemory_t was constructed with a bad byteSize parameter (not a multiple of 2).");

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mMemorySize > 0)
		log(Debug, "(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mMemory.data(), mMemorySize);
#endif
}

#if defined(BUILD_DEBUG)
HwordMemory_t::HwordMemory_t(const size_t byteSize, const char* mnemonic, bool debugReads, bool debugWrites) :
	mDebugReads(debugReads), mDebugWrites(debugWrites),
	mMemoryByteSize(byteSize),
	mMemory(mMemoryByteSize / 2, 0),
	mMnemonic(mnemonic)
{
	// Check that mMemoryByteSize is a multiple of 2 (Constants::NUMBER_BYTES_IN_HWORD).
	if ((mMemoryByteSize % Constants::NUMBER_BYTES_IN_HWORD) != 0)
		throw std::runtime_error("HwordMemory_t was constructed with a bad byteSize parameter (not a multiple of 2).");

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mMemorySize > 0)
		log(Debug, "(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mMemory.data(), mMemorySize);
#endif
}
#endif

u16 HwordMemory_t::readHword(const System_t context, size_t hwordOffset)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mMemory[hwordOffset]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void HwordMemory_t::writeHword(const System_t context, size_t hwordOffset, u16 value)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mMemory[hwordOffset]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u32 HwordMemory_t::readWord(const System_t context, size_t hwordOffset)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mMemory[hwordOffset]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void HwordMemory_t::writeWord(const System_t context, size_t hwordOffset, u32 value)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mMemory[hwordOffset]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u64 HwordMemory_t::readDword(const System_t context, size_t hwordOffset)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mMemory[hwordOffset]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void HwordMemory_t::writeDword(const System_t context, size_t hwordOffset, u64 value)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mMemory[hwordOffset]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u128 HwordMemory_t::readQword(const System_t context, size_t hwordOffset)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mMemory[hwordOffset]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mMemory[hwordOffset + Constants::NUMBER_BYTES_IN_DWORD]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#endif
	}
#endif

	return u128(*hostMemoryAddressLSB, *hostMemoryAddressMSB);
}

void HwordMemory_t::writeQword(const System_t context, size_t hwordOffset, u128 value)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mMemory[hwordOffset]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mMemory[hwordOffset + Constants::NUMBER_BYTES_IN_DWORD]);

	// Write the value.
	*hostMemoryAddressLSB = value.lo;
	*hostMemoryAddressMSB = value.hi;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getSystemStr(context), getMnemonic(), hwordOffset, *hostMemoryAddress);
#endif
	}
#endif
}

size_t HwordMemory_t::getSize()
{
	return mMemoryByteSize;
}

std::vector<u16>& HwordMemory_t::getContainer()
{
	return mMemory;
}

const char * HwordMemory_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

void HwordMemory_t::readFile(const char * fileStr, const size_t fileHwordOffset, const size_t fileHwordLength, const size_t memoryHwordOffset)
{
	// Check it is not too big.
	if (((mMemoryByteSize / Constants::NUMBER_BYTES_IN_HWORD) - memoryHwordOffset) < (fileHwordLength)) // TODO: check... brain too tired...
		throw std::runtime_error("readFile() file was too big to read in.");

	// Open file.
	// MSVC bug? Using std::basic_ifstream<u16> is WAY slower than using ifstream...
	std::ifstream file(fileStr, std::ios_base::binary);
	if (file.fail())
		throw std::runtime_error("readFile() tried to open file, but it failed! Check file exists and has read permissions.");

	// Read file in.
	file.seekg(fileHwordOffset);
	file.read((char*)&mMemory[memoryHwordOffset], fileHwordLength * Constants::NUMBER_BYTES_IN_HWORD);

	// STL method below super slow for some reason...
	/*
	// Read file in.
	std::istreambuf_iterator<u16> start(file);
	std::advance(start, fileHwordOffset);
	std::copy_n(start, fileHwordLength, mMemory.begin() + memoryHwordOffset);
	*/
}

void HwordMemory_t::dump(const char * fileStr)
{
	// Open file.
	// MSVC bug? Using std::basic_ofstream<u16> is WAY slower than using ofstream...
	std::ofstream file(fileStr, std::ios_base::binary);
	if (file.fail())
		throw std::runtime_error("dump() tried to open file, but it failed! Check file exists and has read permissions.");

	// Write file out.
	file.write((char*)&mMemory[0], mMemoryByteSize);

	// STL method below super slow for some reason...
	/*
	// Write file out.
	std::ostreambuf_iterator<u16> start(file);
	std::copy(mMemory.begin(), mMemory.end(), start);
	*/
}
