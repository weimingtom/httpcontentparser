// MainUI.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\Globalvariable.h"
#include ".\Services.h"
#include <apputility\apputility.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <com\comutility.h>
#include <apputility\AppinstallValidate.h>
#include <softwareStatus.h>
#include ".\share.h"
#include <logger\logger.h>
#include <logger\loggerlevel.h>
#include ".\firstpwddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma   comment(linker,"/section:shared,rws")   
#pragma data_seg("shared")
HWND share_hwnd = 0;
int mainui_app_count = 0;
#pragma data_seg()

#define MUTEX_NAME TEXT("2A144C85-AF84-4f88-8F7D-6C794A2800EB")
#define LOGGER_FILE		".\\log\\Family007.log"
#define DEBUG_LOGGER_FILE		".\\log\\dFamily007.log"

IDNSSetting *g_dnssetting = NULL;
extern bool g_parentModel = false;

// 初始化COM
namespace {
AutoInitInScale g_auto_com_init;

void initlogger() {
	using namespace boost::logging;
	init_debug_logger(DEBUG_LOGGER_FILE);
	init_app_logger(LOGGER_FILE);
	set_logger_level(LOGGER_LEVEL);
}

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

bool exit_directly() {
	HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
	if (hMutex == NULL) {
		__LFAT__("CreateMutex FAILED with ERRNO : " << GetLastError());
	}

	WaitForSingleObject(hMutex, INFINITE);

	bool result = false;
	if (mainui_app_count != 0) {
		result =  true;
	}	else {
		mainui_app_count++;
		result =  false;
	}

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return result;
}

BOOL CMainUIApp::InitInstance() {
	if (exit_directly() == true) {
		// 如果share_hwnd已经初始化
		if (share_hwnd != NULL) {
			ShowWindow(share_hwnd, SW_SHOW);
			SetForegroundWindow(share_hwnd);
		}
		__LTRC__("Exit directly");
		return FALSE;
	}

	// 获取应用程序状态
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			__LERR__( "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr);
		}
		pSetting->getApplicationStatus(&app_status);
	} catch (...) {
		__LERR__("CATCH(...)");
	}

	// 初始化LOGGER
	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair();

	if (Services::firstOpen()) {
		CFirstPwdDlg dlg;
		dlg.DoModal();
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
		__LERR__("Create DNSString with HRESULT vlaue "<<std::hex<<hr);
		AfxMessageBox(str);
		return FALSE;
	}

	g_parentModel = Services::isParentModel();
	return TRUE;
}
