#include "stdafx.h"

#include "Common/Types/Registers/MIPS/LinkRegister128_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"

LinkRegister128_t::LinkRegister128_t(const std::shared_ptr<PCRegister32_t> & pcRegister) :
	mPCRegister(pcRegister)
{
}

void LinkRegister128_t::setLinkAddress()
{
	writeDword(Context_t::RAW, 0, mPCRegister->readWord(Context_t::RAW) + Constants::SIZE_MIPS_INSTRUCTION);
}
