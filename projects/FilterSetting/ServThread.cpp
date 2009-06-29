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


// 每过一段时间，不管设置是否改变都要改变，都保存一次
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
		// 保存文件
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
// 创建一个窗口
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	try {
		// 两个计时器
		static DWORD tickAutoSaver = GetTickCount();
		static DWORD tickEyecare = GetTickCount();
		ServThread *server = ServThread::getInstance();

		switch (message) {
		case WM_CREATE:
			// 启动
			SetTimer(hWnd, ID_TIMER_SAVE_SCREEN,	TIME_ESCAPE_SAVE_SCREEN, NULL);
			SetTimer(hWnd, ID_TIMER_EYECARE_TRY,	TIME_ESCAPE_SAVE_EYECARE, NULL);
			SetTimer(hWnd, ID_TIMER_SAVE_HISTORY, TIME_ESCAPE_SAVE_HISTORY, NULL);
			SetTimer(hWnd, ID_TIMER_SAVE_CONFIGURATION, TIME_ESCAPE_CONFIG_SAVE, NULL);

			// 设置HOTKEY
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
			// 每次都要检测配置文件是否已经改变，如果改变则保存
			if (SettingItem::isModified() == true) {
				saveConfiguration();
			} else if (ID_TIMER_SAVE_CONFIGURATION == wParam) {
				// 这里使用else是为了防止多次保存
				saveConfiguration();
			}

			// 自动切换模式可能导致用户迷惑，因此先废除它
			// 如果可以切换状态的时候，且当前状态是家长模式
			//if (g_configuration.getTimeoutSwitch()->shouldSwitch()) {
			//	SettingItem::setModel(SettingItem::MODE_CHILD);
			//}

			if (ID_TIMER_SAVE_SCREEN == wParam) {
				// 自动保存屏幕
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
				// 只有运行于子模式才执行此操作
				// 如果试图改变状态成功，且状态为EYECARE_TIME,
				/*_DEBUG_STREAM_TRC_("EyecareSettint state " 
					<< (g_configuration.getEyecareSetting()->getState()==EyecareSetting::EYECARE_TIME ? "EYECARE " : "ENTERTAIN")
					<< " Left time : "<<g_configuration.getEyecareSetting()->getRemainTime());
				_DEBUG_STREAM_TRC_(" (getAppStatus() : " << getAppStatus());*/

				g_configuration.getEyecareSetting()->trySwitch();
				if (g_configuration.getEyecareSetting()->shouldStartEyecare()) {
					// 启动进程
					if (functionEnabled(getAppStatus())) {
						StartEyecare();
						_DEBUG_STREAM_TRC_("[Family007 Service] Launch Eyecare ");
						__LTRC__("Launch Eyecare  ");
					}
				} 
			} else if (ID_TIMER_SAVE_HISTORY == wParam && g_configuration.getWebHistoryRecordSetting()->recordSeachKeyword()) {
				// 保存记录的历史

				// 读取搜索词汇信息
				TCHAR filename[MAX_PATH];
				GetSearchWordFile(filename, MAX_PATH);
				g_searchwordUtil.save(GetSearchWordFile(filename, MAX_PATH));
				__LTRC__("Save search word on path "<<filename);
				_DEBUG_STREAM_TRC_("[Family007 Service] Save search word on path "<<filename);

				// 读取访问网站的信息
				GetWebSiteFile(filename, MAX_PATH);
				g_websitesUtil.save(GetWebSiteFile(filename, MAX_PATH));
				__LTRC__("Save website history on path "<<filename);
				_DEBUG_STREAM_TRC_("[Family007 Service] Save website history on path "<<filename);
			}
			// 自动开启
			break;
		case WM_REGISTER_HOTKEY: 
			// 如何进行错误处理
			UnregisterHotKey(hWnd, (int)lParam);
			if (0 != wParam && 0 != lParam) {	// 如果没有设置键
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
