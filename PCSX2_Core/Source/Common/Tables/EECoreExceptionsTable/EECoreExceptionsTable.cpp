#include "stdafx.h"

#include "Common/Tables/EECoreExceptionsTable/EECoreExceptionsTable.h"

const EECoreExceptionsTable::ExceptionProperties_t * EECoreExceptionsTable::getExceptionInfo(const EECoreException_t & exception)
{
	return &ExceptionProperties[static_cast<int>(exception)];
}
