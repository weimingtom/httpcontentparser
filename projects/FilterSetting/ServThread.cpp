#include "StdAfx.h"
#include ".\servthread.h"
#include "assert.h"
#include "globalvariable.h"
#include <app_constants.h>
#include <apputility.h>
#include <PrintScreen.h>
#include <searchengine_define.h>
#include <searchkeywordutil.h>
#include <logger\logger.h>
#include <DebugOutput.h>
#include <softwareStatus.h>

#define TIME_ESCAPE_SAVE_SCREEN  8000
#define ID_TIMER_SAVE_SCREEN     1

#define TIME_ESCAPE_SAVE_EYECARE 1000	
#define ID_TIMER_EYECARE_TRY	3

#define TIME_ESCAPE_SAVE_HISTORY	1000 * 60 * 10
#define ID_TIMER_SAVE_HISTORY 5


// ÿ��һ��ʱ�䣬���������Ƿ�ı䶼Ҫ�ı䣬������һ��
#define TIME_ESCAPE_CONFIG_SAVE	1000 * 60 * 3
#define ID_TIMER_SAVE_CONFIGURATION	 8

#define WM_USER_SCREEN_SAVE (WM_USER + 0x10)
#define WM_USER_EYECARE (WM_USER + 0x15)


// WPARAM (vKey + vModifier) LPARAM (ID)
// WPARAM , HIWORD = vModifier 
#define WM_REGISTER_HOTKEY (WM_USER + 0x20)

extern HINSTANCE g_hInstance;

namespace {

	void startMainUI() {
		UINT result = WinExec(APPLICATION_MAINUI_EXE_FILE, SW_SHOW);
		if (0 != result) {
			__LERR__("WinExec failed with return value "<<result<< " LastErorr : "<<GetLastError());
		}
	}

	void saveConfiguration() {
		TCHAR config_path[MAX_PATH];
		GetAppConfigFilename(config_path, MAX_PATH);
		
		_DEBUG_STREAM_TRC_("[Family007 Service] Save Configuration path "<<config_path);
		__LTRC__("Save Configuration on path "<<config_path);
		// �����ļ�
		g_configuration.saveConfig(config_path);	
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
			SetTimer(hWnd, ID_TIMER_SAVE_CONFIGURATION, TIME_ESCAPE_CONFIG_SAVE, NULL);

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
				saveConfiguration();
			} else if (ID_TIMER_SAVE_CONFIGURATION == wParam) {
				// ����ʹ��else��Ϊ�˷�ֹ��α���
				saveConfiguration();
			}

			// �Զ��л�ģʽ���ܵ����û��Ի�����ȷϳ���
			// ��������л�״̬��ʱ���ҵ�ǰ״̬�Ǽҳ�ģʽ
			//if (g_configuration.getTimeoutSwitch()->shouldSwitch()) {
			//	SettingItem::setModel(SettingItem::MODE_CHILD);
			//}

			if (ID_TIMER_SAVE_SCREEN == wParam) {
				// �Զ�������Ļ
				if (SettingItem::MODE_CHILD == SettingItem::getModel()) {
					if (g_configuration.getScreenshotSetting()->shouldSave()) {
						TCHAR fullpath[MAX_PATH];
						GenScreenSPFile(fullpath, MAX_PATH);
						GetScreen(fullpath);
						_DEBUG_STREAM_TRC_("[Family007 Service] Screen Snapshot on path "<<fullpath);
						__LTRC__("Screen Snapshot on path "<<fullpath);
					}
				}
			} else if (ID_TIMER_EYECARE_TRY == wParam) {
				// ֻ����������ģʽ��ִ�д˲���
				// �����ͼ�ı�״̬�ɹ�����״̬ΪEYECARE_TIME,
				/*_DEBUG_STREAM_TRC_("EyecareSettint state " 
					<< (g_configuration.getEyecareSetting()->getState()==EyecareSetting::EYECARE_TIME ? "EYECARE " : "ENTERTAIN")
					<< " Left time : "<<g_configuration.getEyecareSetting()->getRemainTime());
				_DEBUG_STREAM_TRC_(" (getAppStatus() : " << getAppStatus());*/

				g_configuration.getEyecareSetting()->trySwitch();
				if (g_configuration.getEyecareSetting()->shouldStartEyecare()) {
					// ��������
					if (functionEnabled(getAppStatus())) {
						StartEyecare();
						_DEBUG_STREAM_TRC_("[Family007 Service] Launch Eyecare ");
						__LTRC__("Launch Eyecare  ");
					}
				} 
			} else if (ID_TIMER_SAVE_HISTORY == wParam && g_configuration.getWebHistoryRecordSetting()->recordSeachKeyword()) {
				// �����¼����ʷ

				// ��ȡ�����ʻ���Ϣ
				TCHAR filename[MAX_PATH];
				GetSearchWordFile(filename, MAX_PATH);
				g_searchwordUtil.save(GetSearchWordFile(filename, MAX_PATH));
				__LTRC__("Save search word on path "<<filename);
				_DEBUG_STREAM_TRC_("[Family007 Service] Save search word on path "<<filename);

				// ��ȡ������վ����Ϣ
				GetWebSiteFile(filename, MAX_PATH);
				g_websitesUtil.save(GetWebSiteFile(filename, MAX_PATH));
				__LTRC__("Save website history on path "<<filename);
				_DEBUG_STREAM_TRC_("[Family007 Service] Save website history on path "<<filename);
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
		__LERR__("WndProc Unknown exception");
		_DEBUG_STREAM_TRC_("[Family007 Service] "<<__FUNCTION__<<" Unknown Exception ");
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

	__LTRC__("Thread Exit");
	__LERR__("Thread Exit");
	return 1;
}

//=====================================
// other members
void ServThread::startServer() {
	assert (dwThreadId_ == 0);

	hThread_ = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)TreadProc, (LPVOID)this, 0, &dwThreadId_);
	if (NULL == hThread_) {
		__LERR__("CreateThread failed with return value "<<hThread_<< " LastErorr : "<<GetLastError());
		_DEBUG_STREAM_TRC_("[Family007 Service] "<<__FUNCTION__<<" CreateThread failed with return value "<<hThread_<< " LastErorr : "<<GetLastError());
	} 
}
