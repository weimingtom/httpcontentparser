#include "StdAfx.h"
#include ".\servthread.h"
#include "assert.h"
#include "globalvariable.h"
#include <hotkey.h>
#include <windowtitle.h>
#include <sysutility.h>
#include <PrintScreen.h>

#define TIME_ESCAPE_SAVE_SCREEN  8000
#define ID_TIMER_SAVE_SCREEN     1

// 每隔十分钟自动存储一次配置文件
#define TIME_ESCAPE_SAVE_CONFIG	1000 * 60 * 10	// 10分钟
#define ID_TIMER_SAVE_CONFG		 2

#define TIME_ESCAPE_SAVE_EYECARE 10000	
#define ID_TIMER_EYECARE_TRY	3

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
// 创建一个窗口
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// 两个计时器
	static DWORD tickAutoSaver = GetTickCount();
	static DWORD tickEyecare = GetTickCount();
	ServThread *server = ServThread::getInstance();

	switch (message) {
		case WM_CREATE:
			// 启动
			SetTimer(hWnd, ID_TIMER_SAVE_SCREEN,	TIME_ESCAPE_SAVE_SCREEN, NULL);
			SetTimer(hWnd, ID_TIMER_SAVE_CONFG,		TIME_ESCAPE_SAVE_CONFIG, NULL);
			SetTimer(hWnd, ID_TIMER_EYECARE_TRY,	TIME_ESCAPE_SAVE_EYECARE, NULL);
			break;
		case WM_SETHOTKEY:
			return 0;
		case WM_HOTKEY:
			OutputDebugString(TEXT("jidij==================="));
			return 0;

		case WM_TIMER:
			if (ID_TIMER_SAVE_SCREEN == wParam) {
				// 自动保存屏幕
				if (g_configuration.getScreenSave()->shouldSave()) {
					TCHAR fullpath[MAX_PATH];
					GenScreenSPFile(fullpath, MAX_PATH, g_hInstance);
					GetScreen(fullpath);
				}
			} else if (ID_TIMER_SAVE_CONFG == wParam) {
				TCHAR config_path[MAX_PATH];
				GetModuleFileName((HMODULE)g_hInstance, config_path, MAX_PATH);
				g_configuration.saveConfig(config_path);
			} else if (ID_TIMER_EYECARE_TRY == wParam) {
				// 如果试图改变状态成功，且状态为EYECARE_TIME,
				g_configuration.getEyecareSetting()->trySwitch();
				if (g_configuration.getEyecareSetting()->getState() == EyecareSetting::EYECARE_TIME) {
					// 启动进程
					HWND hwnd = GetEyecareApp();
					if (NULL == hwnd) {
						StartEyecare((HMODULE)g_hInstance);
					};
				}
			}
			// 自动开启
			break;
		case WM_REGISTER_HOTKEY: 
			// 如何进行错误处理
			UnregisterHotKey(hWnd, (int)lParam);
			return RegisterHotKey(hWnd, (int)lParam, HIWORD(wParam), LOWORD(wParam));
		case WM_DESTROY:
			UnregisterHotKey(hWnd, server->hotkeyid_switchuser_);
			UnregisterHotKey(hWnd, server->hotkeyid_showdlg_);

			KillTimer(hWnd, ID_TIMER_SAVE_SCREEN);
			KillTimer(hWnd, ID_TIMER_SAVE_CONFG);
			KillTimer(hWnd, ID_TIMER_EYECARE_TRY);
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
// 线程包括的任务
// 1. 启动眼睛保护
// 2. 响应HOTKEY
// 3. 屏幕保存
DWORD ServThread::TreadProc(LPVOID param) {
	// 创建一个窗口
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
