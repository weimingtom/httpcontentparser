#include "StdAfx.h"
#include ".\servthread.h"
#include "assert.h"
#include "globalvariable.h"
#include <app_constants.h>
#include <sysutility.h>
#include <PrintScreen.h>

#define TIME_ESCAPE_SAVE_SCREEN  8000
#define ID_TIMER_SAVE_SCREEN     1

// ÿ��ʮ�����Զ��洢һ�������ļ�
#define TIME_ESCAPE_SAVE_CONFIG	1000 * 60 * 10	// 10����
#define ID_TIMER_SAVE_CONFG		 2

#define TIME_ESCAPE_SAVE_EYECARE 10000	
#define ID_TIMER_EYECARE_TRY	3

#define WM_USER_SCREEN_SAVE (WM_USER + 0x10)
#define WM_USER_EYECARE (WM_USER + 0x15)


// WPARAM (vKey + vModifier) LPARAM (ID)
// WPARAM , HIWORD = vModifier 
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
}

ServThread::~ServThread(void) {
}

int ServThread::setHotKey(WORD vKey, WORD fsModifiers, int type) {
	assert (type == HOTKEY_LANUCH_MAINUI);
	return (int)SendMessage(hwnd_, WM_REGISTER_HOTKEY, MAKEWPARAM(vKey, fsModifiers), (LPARAM)type);
}

void ServThread::initialize() {
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
			// ����
			SetTimer(hWnd, ID_TIMER_SAVE_SCREEN,	TIME_ESCAPE_SAVE_SCREEN, NULL);
			SetTimer(hWnd, ID_TIMER_SAVE_CONFG,		TIME_ESCAPE_SAVE_CONFIG, NULL);
			SetTimer(hWnd, ID_TIMER_EYECARE_TRY,	TIME_ESCAPE_SAVE_EYECARE, NULL);
			break;
		case WM_HOTKEY:
			{
				OutputDebugString("hotkey.....................");
				const int hotkey_id = (int)wParam;
				if (hotkey_id == HOTKEY_LANUCH_MAINUI) {
					HWND hMainUI =  GetMainUIHWND();
					if (NULL == hMainUI) {
						StartMainUI(g_hInstance);
						::SetWindowPos(GetMainUIHWND(), HWND_TOP, 0, 0, 0, 0,
							SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOMOVE);
					} else {
						::SetWindowPos(hMainUI, HWND_TOP, 0, 0, 0, 0,
							SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOMOVE);
					}
				}
			}
		case WM_TIMER:
			if (ID_TIMER_SAVE_SCREEN == wParam) {
				// �Զ�������Ļ
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
				// �����ͼ�ı�״̬�ɹ�����״̬ΪEYECARE_TIME,
				g_configuration.getEyecareSetting()->trySwitch();
				if (g_configuration.getEyecareSetting()->getState() == EyecareSetting::EYECARE_TIME) {
					// ��������
					HWND hwnd = GetEyecareApp();
					if (NULL == hwnd) {
						StartEyecare((HMODULE)g_hInstance);
					};
				}
			}
			// �Զ�����
			break;
		case WM_REGISTER_HOTKEY: 
			// ��ν��д�����
			UnregisterHotKey(hWnd, (int)lParam);
			if (0 != wParam) {	// ���û�����ü�
				if ( 0 != wParam) {
					return RegisterHotKey(hWnd, (int)lParam, HIWORD(wParam), LOWORD(wParam));
				}
			}
			return TRUE;
		case WM_DESTROY:
			UnregisterHotKey(hWnd, HOTKEY_LANUCH_MAINUI);
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
