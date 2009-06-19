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
#include <logger\logger.h>

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

	// 如果用户出去OVERTIME状态，则直接退出。
	// 无论用户处于任何状态，都有该修复
	// 万一用户无法访问呢？

	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// 获取应用程序状态
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) 
			pSetting->getApplicationStatus(&app_status);
	} catch (...) {
	}

	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair(true);

	TCHAR errMsg[MAX_PATH];
	validator.getErrorMessage(errMsg, MAX_PATH);
	if (_tcslen(errMsg) > 0) {
		__LERR__("failed  on repair on reason that "<<errMsg);
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

	// 设置状态， 如果
	app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// 获取应用程序状态
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			pSetting->getApplicationStatus(&app_status);

			// 如果程序为卸载状态， 则设置为trial状态
			// 这一措施用于保证用户在安装程序的时候
			// 不需要覆盖设置， 就可以达到重新安装的目的
			// 但是这一行为必须保证用户能够正确获取状态信息
			// 不能是用户安装之后，从超期状态到注册状态

			if (app_status == SNOWMAN_STATUS_UNINSTALL) {
				pSetting->setApplicationStatus(SNOWMAN_STATUS_TRIAL);
			}
		}
	} catch (...) {
	}

	__LTRC__("succeeded on repair.");


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
	set_logger_level(level::debug);
#else
	init_app_logger(".\\log\\repair.log");
	set_logger_level(level::warning);
#endif
	}
};
LoggerInit g_logger_init;
};