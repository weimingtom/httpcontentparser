#include "StdAfx.h"
#include ".\servthread.h"
#include "assert.h"
#include "globalvariable.h"
#include <hotkey.h>
#include <windowtitle.h>
#include <sysutility.h>
#include <PrintScreen.h>

#define TIME_ESCAPE  8000
#define ID_TIMER     1


#define WM_USER_SCREEN_SAVE (WM_USER + 0x10)
#define WM_USER_EYECARE (WM_USER + 0x15)


// WPARAM (vKey + vModifier) LPARAM (ID)
#define WM_REGISTER_HOTKEY (WM_USER + 0x20)

extern HINSTANCE g_hInstance;

namespace {

void startEyecare() {
	// HWND hwnd = FindWindow(, );
}

void startMainUI() {
	HWND hwnd = FindWindow(MAIN_WINDOW_CLASS, MAIN_WINDOW_TITLE);
	if (hwnd != NULL) {
		ShowWindow(hwnd, SW_SHOW);
	} else {
		// WinExec(TEXT("Mainui.exe"), SW_SHOW);
	}
}

class HotKeyResponse {
};

};

//==================================
// static members
ServThread * ServThread::pInstance = NULL;

ServThread * ServThread::getInstance() {
	try {
		if (pInstance == NULL) {
			pInstance = new ServThread();
			pInstance->initialize();
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

	hotkeyid_switchuser_ = 0;
	hotkeyid_showdlg_ = 0;
}

ServThread::~ServThread(void) {
	GlobalDeleteAtom(hotkeyid_switchuser_);
	GlobalDeleteAtom(hotkeyid_showdlg_);
}

int ServThread::setHotKey(WORD vKey, WORD fsModifiers, int type) {
	int hotkeyid;
	if (type == HOTKEY_ID_POPUP_MAIN) {
		hotkeyid = hotkeyid_showdlg_;
	} else if (type == HOTKEY_ID_SWITCH_USER){
		hotkeyid = hotkeyid_switchuser_;
	} else {
		assert(false);
	}

	return (int)SendMessage(hwnd_, WM_REGISTER_HOTKEY, MAKEWPARAM(vKey, fsModifiers), (LPARAM)hotkeyid);
}

void ServThread::initialize() {
	hotkeyid_switchuser_  = GlobalAddAtom(HOTKEY_ID_POPUP_MAIN_TEXT);
	hotkeyid_showdlg_ = GlobalAddAtom(HOTKEY_ID_SWITCH_USER_TEXT);
}

TCHAR szWindowClass[] = TEXT("None");
// ����һ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// ������ʱ��
	static DWORD tickAutoSaver = GetTickCount();
	static DWORD tickEyecare = GetTickCount();
	ServThread *server = ServThread::getInstance();

	switch (message) {
		case WM_CREATE:
			// SetTimer(hWnd, ID_TIMER, TIME_ESCAPE, NULL);
			break;
		case WM_SETHOTKEY:
			return 0;
		case WM_HOTKEY:
			OutputDebugString(TEXT("jidij==================="));
			return 0;

		case WM_TIMER: 
			// �Զ�������Ļ
			if (g_screenSaver.shouldSave()) {
				TCHAR fullpath[MAX_PATH];
				GenScreenSPFile(fullpath, MAX_PATH, g_hInstance);
				GetScreen(fullpath);
			}

			// �Զ�����
			break;
		case WM_REGISTER_HOTKEY: 
			// ��ν��д�����
			UnregisterHotKey(hWnd, (int)lParam);
			return RegisterHotKey(hWnd, (int)lParam, HIWORD(wParam), LOWORD(wParam));
		case WM_DESTROY:
			UnregisterHotKey(hWnd, server->hotkeyid_switchuser_);
			UnregisterHotKey(hWnd, server->hotkeyid_showdlg_);
			break;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
HWND createWindow() {
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= ::CreateSolidBrush(RGB(58, 110, 165));
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;
	RegisterClassEx(&wcex);
	HWND hwnd = CreateWindow(szWindowClass, TEXT(""), WS_POPUP , 0, 0, 0, 0, NULL, NULL, g_hInstance, 0);
	return hwnd;
}
//=====================================
// �̰߳���������
// 1. �����۾�����
// 2. ��ӦHOTKEY
// 3. ��Ļ����
DWORD ServThread::TreadProc(LPVOID param) {
	// ����һ������
	ServThread::getInstance()->hwnd_ = createWindow();
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);	
	}

	return 1;
}

//=====================================
// other members
void ServThread::startServer() {
	assert (dwThreadId_ == 0);

	hThread_ = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)TreadProc, (LPVOID)this, 0, &dwThreadId_);
}
