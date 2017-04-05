#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/ConstantRegister128_t.h"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Types/Register/LinkRegister128_t.h"

EECoreR5900_t::EECoreR5900_t() : 
	PC(std::make_shared<PCRegister32_t>()),
	ZeroRegister(std::make_shared<ConstantRegister128_t>()),
	LinkRegister(std::make_shared<LinkRegister128_t>(PC)),
	GPR{ ZeroRegister, std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), LinkRegister },
	HI(std::make_shared<Register128_t>()),
	LO(std::make_shared<Register128_t>()),
	SA(std::make_shared<Register32_t>())
{
}