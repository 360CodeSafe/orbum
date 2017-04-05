#include "stdafx.h"

#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Types/Register/ConstantRegister32_t.h"
#include "Common/Types/Register/LinkRegister32_t.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

IOPCoreR3000_t::IOPCoreR3000_t() :
	PC(std::make_shared<PCRegister32_t>()),
	ZeroRegister(std::make_shared<ConstantRegister32_t>()),
	LinkRegister(std::make_shared<LinkRegister32_t>(PC)),
	GPR{ ZeroRegister, std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
		std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
		std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
		std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), LinkRegister },
	HI(std::make_shared<Register32_t>()),
	LO(std::make_shared<Register32_t>())
{
}