#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Tables/IOPCoreExceptionsTable/IOPCoreExceptionsTable.h"

const IOPCoreExceptionsTable::ExceptionProperties_t * IOPCoreExceptionsTable::getExceptionInfo(const IOPCoreException_t & exception)
{
	return &ExceptionProperties[static_cast<u8>(exception)];
}
