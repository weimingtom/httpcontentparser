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
};