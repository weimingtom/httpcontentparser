#include "stdafx.h"
#include "syncutility.h"

namespace yanglei_utility {

CAutoCreateCS::CAutoCreateCS() {
	::InitializeCriticalSection(&cs_);
	locked_ = false;
}
CAutoCreateCS::~CAutoCreateCS() {
	::DeleteCriticalSection(&cs_);
}

void CAutoCreateCS::lock() {
	if (locked_ == false) {
		EnterCriticalSection(&cs_);
		locked_ = true;
	}
}
void CAutoCreateCS::unlock() {
	if (locked_ == true) {
		LeaveCriticalSection(&cs_);
		locked_ = false;
	}
}
};