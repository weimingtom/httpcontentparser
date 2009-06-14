#include "StdAfx.h"
#include ".\servthread.h"
#include "assert.h"
#include "globalvariable.h"
#include <app_constants.h>
#include <apputility.h>
#include <PrintScreen.h>
#include <searchengine_define.h>
#include <searchkeywordutil.h>
#include ".\log.h"

#define TIME_ESCAPE_SAVE_SCREEN  8000
#define ID_TIMER_SAVE_SCREEN     1

#define TIME_ESCAPE_SAVE_EYECARE 1000	
#define ID_TIMER_EYECARE_TRY	3

#define TIME_ESCAPE_SAVE_HISTORY	1000 * 60 * 10
#define ID_TIMER_SAVE_HISTORY 5

#define WM_USER_SCREEN_SAVE (WM_USER + 0x10)
#define WM_USER_EYECARE (WM_USER + 0x15)


// WPARAM (vKey + vModifier) LPARAM (ID)
// WPARAM , HIWORD = vModifier 
#define WM_REGISTER_HOTKEY (WM_USER + 0x20)

extern HINSTANCE g_hInstance;

namespace {

	void startEyecare() {
		// TODO ����ø�ɶ����
		// HWND hwnd = FindWindow(, );
	}

	void startMainUI() {
		HWND hwnd = FindWindow(MAIN_WINDOW_CLASS, MAIN_WINDOW_TITLE);
		if (hwnd != NULL) {
			ShowWindow(hwnd, SW_SHOW);
		} else {
			UINT result = WinExec(TEXT("Mainui.exe"), SW_SHOW);
			if (0 != result) {
				LERR_<<"WinExec failed with return value "<<result<< " LastErorr : "<<GetLastError();
			}
		}
	}
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
	if (type == HOTKEY_LANUCH_MAINUI) { 
		return (int)SendMessage(hwnd_, WM_REGISTER_HOTKEY, MAKEWPARAM(vKey, fsModifiers), (LPARAM)type);
	} else {
		return TRUE;
	} 
}

void ServThread::initialize() {
}

TCHAR szWindowClass[] = TEXT("None");
// ����һ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	try {
		// ������ʱ��
		static DWORD tickAutoSaver = GetTickCount();
		static DWORD tickEyecare = GetTickCount();
		ServThread *server = ServThread::getInstance();

		switch (message) {
		case WM_CREATE:
			// ����
			SetTimer(hWnd, ID_TIMER_SAVE_SCREEN,	TIME_ESCAPE_SAVE_SCREEN, NULL);
			SetTimer(hWnd, ID_TIMER_EYECARE_TRY,	TIME_ESCAPE_SAVE_EYECARE, NULL);
			SetTimer(hWnd, ID_TIMER_SAVE_HISTORY, TIME_ESCAPE_SAVE_HISTORY, NULL);

			// ����HOTKEY
			{
				DWORD hotkey = g_configuration.getHotkey()->getHotkey(CONFIG_HOTKEY_LAUNCH);
				if ( 0 != hotkey) 
					server->setHotKey(HIWORD(hotkey), LOWORD(hotkey), HOTKEY_LANUCH_MAINUI);
			}
			break;
		case WM_HOTKEY:
			{
				const int hotkey_id = (int)wParam;
				if (hotkey_id == HOTKEY_LANUCH_MAINUI) {
					StartMainUI();
				}
			}
		case WM_TIMER:
			// ÿ�ζ�Ҫ��������ļ��Ƿ��Ѿ��ı䣬����ı��򱣴�
			if (SettingItem::isModified() == true) {
				TCHAR config_path[MAX_PATH];
				GetAppConfigFilename(config_path, MAX_PATH);

				// �����ļ�
				g_configuration.saveConfig(config_path);
				LTRC_<<"Save Configuration";
			}

			// �Զ��л�ģʽ���ܵ����û��Ի�����ȷϳ���
			// ��������л�״̬��ʱ���ҵ�ǰ״̬�Ǽҳ�ģʽ
			//if (g_configuration.getTimeoutSwitch()->shouldSwitch()) {
			//	SettingItem::setModel(SettingItem::MODE_CHILD);
			//}

			if (ID_TIMER_SAVE_SCREEN == wParam) {
				// �Զ�������Ļ
				if (g_configuration.getScreenshotSetting()->shouldSave()) {
					TCHAR fullpath[MAX_PATH];
					GenScreenSPFile(fullpath, MAX_PATH);
					GetScreen(fullpath);
					LTRC_<<"Screen Snapshot";
				}
			} else if (ID_TIMER_EYECARE_TRY == wParam) {
				// ֻ����������ģʽ��ִ�д˲���
				if (SettingItem::MODE_CHILD == SettingItem::getModel()) {
					// �����ͼ�ı�״̬�ɹ�����״̬ΪEYECARE_TIME,
					g_configuration.getEyecareSetting()->trySwitch();
					if (g_configuration.getEyecareSetting()->getState() == EyecareSetting::EYECARE_TIME) {
						// ��������
						HWND hwnd = GetEyecareApp();
						if (NULL == hwnd) {
							StartEyecare();
						};
					}
				} 
			} else if (ID_TIMER_SAVE_HISTORY == wParam && g_configuration.getWebHistoryRecordSetting()->recordSeachKeyword()) {
				// �����¼����ʷ

				// ��ȡ�����ʻ���Ϣ
				TCHAR filename[MAX_PATH];
				GetSearchWordFile(filename, MAX_PATH);
				g_searchwordUtil.save(GetSearchWordFile(filename, MAX_PATH));

				// ��ȡ������վ����Ϣ
				GetWebSiteFile(filename, MAX_PATH);
				g_websitesUtil.save(GetWebSiteFile(filename, MAX_PATH));
				LTRC_<< "Save History";
			}
			// �Զ�����
			break;
		case WM_REGISTER_HOTKEY: 
			// ��ν��д�����
			UnregisterHotKey(hWnd, (int)lParam);
			if (0 != wParam && 0 != lParam) {	// ���û�����ü�
				return RegisterHotKey(hWnd, (int)lParam, HIWORD(wParam), LOWORD(wParam));
			}
			return TRUE;
		case WM_DESTROY:
			UnregisterHotKey(hWnd, HOTKEY_LANUCH_MAINUI);
			KillTimer(hWnd, ID_TIMER_SAVE_SCREEN);
			KillTimer(hWnd, ID_TIMER_EYECARE_TRY);
			break;

		}
	} catch(...) {
		LERR_<<"WndProc Unknown exception";
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

	LTRC_<<"Thread Exit";
	LERR_<<"Thread Exit";
	return 1;
}

//=====================================
// other members
void ServThread::startServer() {
	assert (dwThreadId_ == 0);

	hThread_ = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)TreadProc, (LPVOID)this, 0, &dwThreadId_);
	if (NULL == hThread_) {
		LERR_<<"CreateThread failed with return value "<<hThread_<< " LastErorr : "<<GetLastError();
	} 
}
