#include "stdafx.h"
#include "syncutility.h"

namespace yanglei_utility {

CAutoCreateCS::CAutoCreateCS() {
	::InitializeCriticalSection(&cs_);
}
CAutoCreateCS::~CAutoCreateCS() {
	::DeleteCriticalSection(&cs_);
}

void CAutoCreateCS::lock() {
	EnterCriticalSection(&cs_);
}
void CAutoCreateCS::unlock() {
	LeaveCriticalSection(&cs_);

}


//============================
// class CSysMutex
CSysMutex::CSysMutex() {
	hMutex_ = NULL;
}
CSysMutex::CSysMutex(const std::string &name) {
	name_ = name;
	hMutex_ = NULL;
}

CSysMutex::~CSysMutex(void) {
	if (hMutex_ != NULL) {
		CloseHandle(hMutex_);
	}
}

void CSysMutex::Lock() {
	::WaitForSingleObject(getMutex(), INFINITE);
}
void CSysMutex::Unlock() {
	::ReleaseMutex(getMutex());
}

HANDLE CSysMutex::getMutex() {
	if (NULL != hMutex_) {
		hMutex_ = CreateMutex(NULL, FALSE, name_.length() == 0 ? NULL : name_.c_str());
		return hMutex_;
	} else {
		return NULL;
	}
}

};