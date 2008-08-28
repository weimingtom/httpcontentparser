#include "StdAfx.h"
#include ".\servthread.h"
#include "assert.h"

#define TIME_ESCAPE  800
#define ID_TIMER     1

//==================================
// static members
ServThread * ServThread::pInstance = NULL;

ServThread * ServThread::getInstance() {
	try {
		if (pInstance == NULL) {
			pInstance = new ServThread();
			pInstance->startServer();
			return pInstance;
		} else {
			return pInstance;
		}
	} catch (...) {
		return NULL;
	}
}

//=================================
// constructor and deconstructor
ServThread::ServThread(void) {
	dwThreadId_ = 0;
	hThread_ = NULL;
}

ServThread::~ServThread(void) {
}


//=====================================
// 线程包括的任务
// 1. 启动眼睛保护
// 2. 响应HOTKEY
// 3. 屏幕保存
DWORD ServThread::TreadProc(LPVOID param) {
	ServThread *server = (ServThread*)param;
	MSG msg = {0};
	HWND hwnd = (HWND)server->getThreadHandle();
	SetTimer(hwnd, ID_TIMER, TIME_ESCAPE, NULL);

	while(GetMessage(&msg, hwnd, NULL, NULL)) {
		switch(msg.message) {
			case WM_SETHOTKEY:
				break;
			case WM_TIMER:
				break;
		}
	}

	return 0;
}

//=====================================
// other members
void ServThread::startServer() {
	assert (dwThreadId_ == 0);

	hThread_ = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)TreadProc, (LPVOID)this, 0, &dwThreadId_);
}
