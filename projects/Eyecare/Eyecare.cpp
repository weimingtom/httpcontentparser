// k2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <app_constants.h>
#include <apputility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <EyecareSetting.h>
#include <comdef.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <winlockdll.h>
#include <logger\logger.h>

#define MAX_LOADSTRING 100
#define WM_MY_SHOWDIALOG (WM_USER + 0x0001)

#define ID_TIMER   1
#define TIME_SPAN  1000

IEyecare *pEyeCare = NULL;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


namespace {

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	BOOL fEatKeystroke = FALSE;
	if (nCode == HC_ACTION) {
		switch (wParam) {
		 case WM_KEYDOWN:
		 case WM_SYSKEYDOWN:
		 case WM_KEYUP:
		 case WM_SYSKEYUP: 
			 PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;

			 fEatKeystroke = 
				 ((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||

				 ((p->vkCode == VK_ESCAPE) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||

				 ((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0)) ||
				 ((p->vkCode == VK_LWIN) || (p->vkCode == VK_RWIN));
			 break;
		}
	}

	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, 	lParam));
}
HHOOK hhkLowLevelKybd = NULL;
// 锁定电脑
// 主要指禁用 ATL+CTRL+DEL, ATL+ESC, SWITCH, WIN...
void LockScreen() {
	hhkLowLevelKybd  = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInst, 0);

	CtrlAltDel_Enable_Disable(FALSE);
	Taskbar_Show_Hide(FALSE); 
}

void UnlockScreen() {
	assert (NULL != hhkLowLevelKybd);
	UnhookWindowsHookEx(hhkLowLevelKybd);
	hhkLowLevelKybd = NULL;

	CtrlAltDel_Enable_Disable(TRUE);
	Taskbar_Show_Hide(TRUE); 
}

};

BOOL IsRunInEnterModel() {
	try {
		IEyecare *pEyeCare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
		if (FAILED(hr)) {
			return FALSE;
		}

		LONG state;
		pEyeCare->getState(&state);
	
		pEyeCare->Release();
		return state == EyecareSetting::ENTERT_TIME ? TRUE : FALSE;
	} catch (_com_error &) {
		return FALSE;
	}
}
BOOL IsRuninParentModel() {
	try {
		VARIANT_BOOL parent_mode = VARIANT_FALSE;
		ISnowmanSetting *app = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			return FALSE;
		}

		app->get_ParentModel(&parent_mode);

		return convert(parent_mode);
	} catch (_com_error &) {
		return FALSE;
	}
}
BOOL TRYEndEyecare(LPCTSTR password) {
	try {
		VARIANT_BOOL succeeded = FALSE;
		IEyecare *eyecare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&eyecare);
		if (FAILED(hr)) {
			return FALSE;
		}

		eyecare->endEyecare(_bstr_t(password), &succeeded);
		eyecare->Release();

		return convert(succeeded);
	} catch (_com_error &) {
		return FALSE;
	}
}
 

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	if (_tcscmp(lpCmdLine, LAUNCH_PARAM) != 0) {
		__LDBG__("call with cmdline");
		return 0;
	}

	// 首先确定应用程序是否已经打开，
	HWND hOld = GetEyecareApp();
	if (NULL != hOld) {
		return 0;
	}
	

	CoInitialize(NULL);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 如果运行于Enter模式， 则直接退出
	if (IsRunInEnterModel()) {
		__LFAT__("Run in Enter Model");
		return 0;
	}

	// 如果运行于父亲模式
	if (IsRuninParentModel()) {
		__LFAT__("Run in Parent Model");
		return 0;
	}

	// 创建
	HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
	if (FAILED(hr)) 
			__LERR__("Failed on Create Eyecare with HRESULT value "<<std::hex<<hr);

 	// TODO: Place code here.
	MSG msg;
	// Initialize global strings
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);	
	}

	CoUninitialize();
	return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EYECARE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= ::CreateSolidBrush(RGB(58, 110, 165));
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= EYECARE_MAIN_WND_CLASS;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPED;
   hWnd = CreateWindowEx(WS_EX_TOPMOST, EYECARE_MAIN_WND_CLASS, EYECARE_MAIN_WND_TITLE, WS_VISIBLE | WS_MAXIMIZE |WS_POPUP,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK InputPasswordDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	try {
		TCHAR szBuffer[MAX_PATH];
		LONG state;
		LONG seconds;
		switch (message)
		{
		case WM_TIMER:
			try {
				_tcscpy(szBuffer, "Login System");

				// 如果运行在父模式下
				if (IsRuninParentModel()) {
					// 为什么不检测是否在父模式下，如果在则退出呢？
					EndDialog(hDlg, 0);
				} else {
					pEyeCare->getTimeLeft(&seconds);
					if (seconds > 60) {
						_stprintf(szBuffer, "Rest time : %d min", (int)(seconds/60));
					} else if (seconds > 0){
						_stprintf(szBuffer, "Rest time : %d second", seconds);
					} else {
						pEyeCare->trySwitch(&state);
						EndDialog(hDlg, 0);
					}
				SetWindowText(hDlg, szBuffer);
				}
			} catch (...) {
				HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
				if (FAILED(hr)) 
					__LERR__("Failed on Create Eyecare with HRESULT value "<<std::hex<<hr);
			}
			break;
		case WM_KILLFOCUS:
			SetFocus(hDlg);
			break;
		case WM_INITDIALOG:
			try {
				_tcscpy(szBuffer, "Login System");
				pEyeCare->getTimeLeft(&seconds);
			}
			catch (...) {
				HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
				if (FAILED(hr)) 
					__LERR__("Failed on Create Eyecare with HRESULT value "<<std::hex<<hr);
			}

			SetWindowText(hDlg, szBuffer);
			SetTimer(hDlg, ID_TIMER, TIME_SPAN, NULL);
			return TRUE;
		// 验证代码
		case WM_COMMAND:
			GetDlgItemText(hDlg, IDC_PASSWORD, szBuffer, MAX_PATH);
			if (LOWORD(wParam) == IDOK) {
				if (TRYEndEyecare(szBuffer)) {
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				} else {
					MessageBox(hDlg, "Wrong Password!", "Error", MB_OK | MB_ICONERROR);
				}
			}
			break;
		case WM_DESTROY:
			KillTimer(hDlg, ID_TIMER);
			break;
		}
		return FALSE;
	} catch (...) {
		return FALSE;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool bShowDialog = false;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_SIZE:
		PostMessage(hWnd,WM_MY_SHOWDIALOG , 0, 0);
		break;
	case WM_MY_SHOWDIALOG:
		if (bShowDialog)
			break;

		bShowDialog  = true;

		LockScreen();

		DialogBox(hInst, (LPCTSTR)IDD_PASSWORD, hWnd, (DLGPROC)InputPasswordDlg);
		DestroyWindow(hWnd);

		UnlockScreen();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

namespace {
class LoggerInit {
public:
	LoggerInit() {
		using namespace boost::logging;
#ifdef DEBUG
	init_debug_logger(".\\log\\dEyecare.log", false, true);
	init_app_logger(".\\log\\Eyecare.log", false, true);
	set_logger_level(level::debug);
#else
	init_app_logger(".\\log\\Eyecare.log");
	set_logger_level(level::warning);
#endif
	}
};
};
LoggerInit g_logger_init;

