#include "StdAfx.h"
#include ".\sysmutex.h"
#include "exception.h"
#include "returncode.h"
#include <string>

namespace SyncObjects {

CSysMutex::CSysMutex(const std::string &name) : SyncObject(name) {
	hMutex_ = NULL;
}

CSysMutex::~CSysMutex(void) {
	if (hMutex_ != NULL) {
		CloseHandle(hMutex_);
	}
}

int CSysMutex::Lock() {
	if (hMutex_ == NULL) {
		hMutex_ = getMutex();
	}

	::WaitForSingleObject(hMutex_, INFINITE);
	return SUCC_RETURN_CODE;
}
int CSysMutex::Unlock() {
	if( FALSE == ::ReleaseMutex(hMutex_)) {
		throw yanglei::exception(GetLastError());
		return FAIL_RETURN_CODE;
	} else {
		return SUCC_RETURN_CODE;
	}
}

HANDLE CSysMutex::getMutex() {
	HANDLE handle = CreateMutex(NULL, FALSE, getName().c_str());
	if (NULL != handle) {
		return handle;
	} else {
		throw yanglei::exception("Create Mutext failed");
		return NULL;
	}
}
};
