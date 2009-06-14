// Repair.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include ".\Repair.h"
#include ".\RepairDlg.h"
#include <apputility.h>
#include <app_constants.h>
#include <AppinstallValidate.h>
#include <softwareStatus.h>
#include <COM\FilterSetting_i.c>
#include <COM\FilterSetting.h>
#include ".\log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRepairApp

BEGIN_MESSAGE_MAP(CRepairApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRepairApp 构造

CRepairApp::CRepairApp()
{
}


// 唯一的一个 CRepairApp 对象

CRepairApp theApp;


// CRepairApp 初始化

BOOL CRepairApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CoInitialize(NULL);

	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		pSetting->getApplicationStatus(&app_status);
	} catch (...) {
	}

	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair(true);

	TCHAR errMsg[MAX_PATH];
	validator.getErrorMessage(errMsg, MAX_PATH);
	if (_tcslen(errMsg) > 0) {
		LERR_<<"failed  on repair on reason that "<<errMsg;
		if (NULL == _tcsstr(GetCommandLine(), "silence")) {
			AfxMessageBox(errMsg);
		}
		return FALSE;
	}


	CString strSucc;
	strSucc.LoadString(IDS_REPAIR_SUCCESS);
	if (NULL == _tcsstr(GetCommandLine(), "silence")) {
		AfxMessageBox(strSucc);
	}
	LTRC_<<"succeeded on repair.";
	return FALSE;


	return TRUE;
}


namespace {
class LoggerInit {
public:
	LoggerInit() {
		using namespace boost::logging;
#ifdef DEBUG
	init_debug_logger(".\\log\\drepair.log", false, true);
	init_app_logger(".\\log\\repair.log", false, true);
	g_log_level()->set_enabled(level::debug);
#else
	init_app_logger(".\\log\\repair.log");
	g_log_level()->set_enabled(level::warning);
#endif
	}
};
LoggerInit g_logger_init;
};