#include "stdafx.h"
#include "CommonUtility.h"

// Mandatory initialization of static class variable outside the header file.
static FILETIME local;
FILETIME EditRecordTimer::lastUpdatedTimeStamp = (GetSystemTimeAsFileTime(&local), local);