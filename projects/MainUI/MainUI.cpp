// MainUI.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\Globalvariable.h"
#include ".\Services.h"
#include <apputility.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <com\comutility.h>
#include <AppinstallValidate.h>
#include <softwareStatus.h>
#include <logger_name.h>
#include ".\share.h"
#include <logger_name.h>
#include <log4cxx/logger.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/simplelayout.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma   comment(linker,"/section:shared,rws")   
#pragma data_seg("shared")
HWND share_hwnd = 0;
#pragma data_seg()

#define MUTEX_NAME TEXT("2A144C85-AF84-4f88-8F7D-6C794A2800EB")


IDNSSetting *g_dnssetting = NULL;
extern bool g_parentModel = false;

// 初始化COM
namespace {
AutoInitInScale g_auto_com_init;
};


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

BOOL CMainUIApp::InitInstance() {

	initLogger(MAINUI_LOGGER_ERROR_FILE);
	LOGGER_WRITE(MAINUI_LOGGER_ERROR, "CMainUIApp::InitInstance()");
	{
		CMutex mutext(0, MUTEX_NAME);
		CSingleLock(&mutext, true);
		if (share_hwnd != NULL) {
			ShowWindow(share_hwnd, SW_SHOW);
			SetForegroundWindow(share_hwnd);
			return 0;
		}
	}

	// 获取应用程序状态
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			LOGGER_WRITE_COM_FAILED(MAINUI_LOGGER_ERROR, "Create Snowsetting", hr);
		}
		pSetting->getApplicationStatus(&app_status);
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER_ERROR, "CATCH(...)");
	}

	// 初始化LOGGER
	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair();


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
	LOGGER_WRITE(MAINUI_LOGGER_ERROR, TEXT("CMainUIApp::ExitInstance()"));
	GdiplusShutdown( m_GdiplusToken);
	SafeRelease(g_dnssetting);

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
		LOGGER_WRITE_COM_FAILED(MAINUI_LOGGER_ERROR, "Create DNSString", hr);
		AfxMessageBox(str);
		return FALSE;
	}

	g_parentModel = Services::isParentModel();
	return TRUE;
}
