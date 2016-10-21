#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h"

class R3000_t;
class IOPCOP0_t;
class IOPExceptions_t;
class MappedMemory_t;

class IOP_t : public PS2ResourcesSubobject
{
public:
	explicit IOP_t(const PS2Resources_t *const PS2Resources);

	/*
	The R3000 CPU.
	*/
	std::shared_ptr<R3000_t> R3000;

	/*
	COP0 coprocessor.
	*/
	std::shared_ptr<IOPCOP0_t> COP0;

	/*
	Exception/Interrupt State.
	*/
	std::shared_ptr<IOPExceptions_t> Exceptions;

	/*
	IOP Memory (2MB).
	*/
	std::shared_ptr<MappedMemory_t> IOPMemory;
	
	/*
	HW mapped registers (64KB)
	DEBUG
	*/
	std::shared_ptr<MappedMemory_t> IOP_HW_Registers;

	/*
	The IOP physical memory space.
	*/
	std::shared_ptr<PhysicalMMU_t> PhysicalMMU;
};

