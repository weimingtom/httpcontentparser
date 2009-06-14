// k2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <app_constants.h>
#include <apputility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <winlockdll.h>
#include ".\log.h"

#define MAX_LOADSTRING 100
#define WM_MY_SHOWDIALOG (WM_USER + 0x0001)

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

BOOL ValidatePassword(LPCTSTR password) {
	try {
		VARIANT_BOOL succeeded = FALSE;
		IAuthorize *authorize = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&authorize);
		if (FAILED(hr)) {
			return FALSE;
		}

		authorize->checkPassword(_bstr_t(password), &succeeded);
		authorize->Release();

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
		LDBG_<<"call with cmdline";
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LOCKPC));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= ::CreateSolidBrush(RGB(58, 110, 165));
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= EYECARE_MAIN_WND_CLASS;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_LOCKPC));

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

		switch (message)
		{
		case WM_KILLFOCUS:
			SetFocus(hDlg);
			break;
		case WM_INITDIALOG:
			return TRUE;
		// 验证代码
		case WM_COMMAND:
			GetDlgItemText(hDlg, IDC_PASSWORD, szBuffer, MAX_PATH);
			if (LOWORD(wParam) == IDOK) {
				if (ValidatePassword(szBuffer)) {
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				} else {
					MessageBox(hDlg, "Wrong Password!", "Error", MB_OK | MB_ICONERROR);
				}
			}
			break;
		case WM_DESTROY:
			break;
		}
		return FALSE;
	} catch (...) {
		LERR_<<"Unknown exception";
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
	init_debug_logger(".\\log\\dLockPC.log", false, true);
	init_app_logger(".\\log\\LockPC.log", false, true);
	g_log_level()->set_enabled(level::debug);
#else
	init_app_logger(".\\log\\LockPC.log");
	g_log_level()->set_enabled(level::warning);
#endif
	}
};
};
LoggerInit g_logger_init;
