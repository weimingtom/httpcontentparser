// MainUI.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\globalvariable.h"
#include ".\mainui.h"
#include ".\services.h"
#include <apputility.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <com\comutility.h>
#include <AppinstallValidate.h>


IDNSSetting *g_dnssetting = NULL;
XMLConfiguration g_configuration;	// 配置信息
extern bool g_parentModel = false;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMainUIApp

BEGIN_MESSAGE_MAP(CMainUIApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMainUIApp 构造

CMainUIApp::CMainUIApp() {
}


// 唯一的一个 CMainUIApp 对象

CMainUIApp theApp;


// CMainUIApp 初始化

void initializeSetting() {
		// 初始化配置
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH);
	g_configuration.loadConfig(config_path);
}

BOOL CMainUIApp::InitInstance()
{
	CoInitialize(NULL);
	
	// TODO enable the following code
	// AppInstallValidate validator(VLAIDATE_NONE);
	// validator.repair((HMODULE)AfxGetInstanceHandle());

	// 读取配置信息
	initializeSetting();

	HWND hwnd = GetMainUIHWND();
	if (hwnd != NULL) {
		::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOMOVE);
		return FALSE;
	}


	if (FALSE == Initialize()) {
		return FALSE;
	}

	m_GdiplusToken = NULL;
	GdiplusStartupInput gdiplusStartupInput;
	Status status = GdiplusStartup( &m_GdiplusToken, &gdiplusStartupInput, NULL);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();

	//============================================
	CMainUIDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) 	{
	}
	else if (nResponse == IDCANCEL) {
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
}

int CMainUIApp::ExitInstance()
{
	GdiplusShutdown( m_GdiplusToken);
	SafeRelease(g_dnssetting);
	CoUninitialize();

	return CWinApp::ExitInstance();
}

// 做一些初始化的工作
BOOL CMainUIApp::Initialize(void)
{
	// 初始化提示信息
	CString str;
	str.LoadString(IDS_APP_SERVER_INIT_FAILED);

	// 获取DNS列表
	HRESULT hr = CoCreateInstance(CLSID_DNSSetting, 
		NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&g_dnssetting);
	if (FAILED(hr)) {
		AfxMessageBox(str);
		return FALSE;
	}

	g_parentModel = Services::isParentModel();
	return TRUE;
}
