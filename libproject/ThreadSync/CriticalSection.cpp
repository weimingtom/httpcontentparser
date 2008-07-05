#include "StdAfx.h"
#include ".\criticalsection.h"
#include "returncode.h"

namespace SyncObjects {

CriticalSection::CriticalSection(const std::string &name) : SyncObject(name) {
	InitializeCriticalSection(&cs_);
	SyncObject::type_ = SyncObject::CRITICAL_SECTION;
}

CriticalSection::~CriticalSection(void) {
	DeleteCriticalSection(&cs_);
}


int CriticalSection::Lock() {
	EnterCriticalSection(&cs_);
	return SUCC_RETURN_CODE;
}
int CriticalSection::Unlock() {
	LeaveCriticalSection(&cs_);
	return SUCC_RETURN_CODE;
}

};
