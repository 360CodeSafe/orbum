#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperRegister16ByteMMU_t.h"

MapperRegister16ByteMMU_t::MapperRegister16ByteMMU_t(const u32 physicalAddress, const std::shared_ptr<Register16_t> & register16) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mRegister16(register16)
{
}

size_t MapperRegister16ByteMMU_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_HWORD;
}

const char* MapperRegister16ByteMMU_t::getMnemonic() const
{
	return mRegister16->getMnemonic();
}

u8 MapperRegister16ByteMMU_t::readByte(const System_t context, size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with unaligned index. Not allowed.");
	return mRegister16->readByte(context, storageIndex / 1);
}

void MapperRegister16ByteMMU_t::writeByte(const System_t context, size_t storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with unaligned index. Not allowed.");
	mRegister16->writeByte(context, storageIndex / 1, value);
}

u16 MapperRegister16ByteMMU_t::readHword(const System_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with unaligned index. Not allowed.");
	return mRegister16->readHword(context);
}

void MapperRegister16ByteMMU_t::writeHword(const System_t context, size_t storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with unaligned index. Not allowed.");
	mRegister16->writeHword(context, value);
}

u32 MapperRegister16ByteMMU_t::readWord(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister16ByteMMU_t::writeWord(const System_t context, size_t storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with larger than allowed size. Not allowed.");
}

u64 MapperRegister16ByteMMU_t::readDword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister16ByteMMU_t::writeDword(const System_t context, size_t storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with larger than allowed size. Not allowed.");
}

u128 MapperRegister16ByteMMU_t::readQword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister16ByteMMU_t::writeQword(const System_t context, size_t storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MapperRegister16ByteMMU_t with larger than allowed size. Not allowed.");
}
