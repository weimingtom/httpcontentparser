// k2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <app_constants.h>
#include <sysutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>
#include <typeconvert.h>
#include <app_constants.h>

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


BOOL IsRuninParentModel() {
	try {
		VARIANT_BOOL parent_mode = VARIANT_FALSE;
		IAppSetting *app = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			return FALSE;
		}

		app->get_ParentModel(&parent_mode);

		return convert(parent_mode);
	} catch (_com_error &) {
		return FALSE;
	}
}
BOOL TRYSwitchMode(LPCTSTR password) {
	try {
		VARIANT_BOOL succeeded = FALSE;
		IEyecare *eyecare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&eyecare);
		if (FAILED(hr)) {
			return FALSE;
		}

		eyecare->swithToEntertainment(_bstr_t(password), &succeeded);
		eyecare->Release();

		return convert(succeeded);
	} catch (_com_error &) {
		return FALSE;
	}
}



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

				 ((p->vkCode == VK_ESCAPE) && 

				 ((p->flags & LLKHF_ALTDOWN) != 0)) ||

				 ((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0));
			 break;
		}
	}

	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, 	lParam));
}

 

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	// 如果已经有程序启动，则直接推出
	HANDLE hMutex = CreateMutex(NULL, FALSE, EYECARE_MUTEX_NAME);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hMutex);
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

	// 创建
	CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);

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
				CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
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
				CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
			}

			SetWindowText(hDlg, szBuffer);
			SetTimer(hDlg, ID_TIMER, TIME_SPAN, NULL);
			return TRUE;
		// 验证代码
		case WM_COMMAND:
			GetDlgItemText(hDlg, IDC_PASSWORD, szBuffer, MAX_PATH);
			if (LOWORD(wParam) == IDOK) {
				if (TRYSwitchMode(szBuffer)) {
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
	PAINTSTRUCT ps;
	HDC hdc;
	HHOOK hhkLowLevelKybd;

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_SIZE:
		PostMessage(hWnd,WM_MY_SHOWDIALOG , 0, 0);
		break;
	case WM_MY_SHOWDIALOG:
		hhkLowLevelKybd  = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInst, 0);
		DialogBox(hInst, (LPCTSTR)IDD_PASSWORD, hWnd, (DLGPROC)InputPasswordDlg);
		UnhookWindowsHookEx(hhkLowLevelKybd);
		DestroyWindow(hWnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
