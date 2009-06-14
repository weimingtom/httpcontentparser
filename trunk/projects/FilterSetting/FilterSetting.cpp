// FilterSetting.cpp : WinMain 的实现

#include "stdafx.h"
#include "resource.h"
#include "globalvariable.h"
#include "FilterSetting.h"
#include ".\servthread.h"
#include <utility\timeutility.h>
#include <AppinstallValidate.h>
#include <apputility.h>
#include <app_constants.h>
#include <passwordtype.h>
#include <webhistoryrecordersetting.h>
#include <xmlconfiguration.h>
#include <searchengine_define.h>
#include <searchkeywordutil.h>
#include <shell\shellutility.h>
#include <softwareStatus.h>
#include <string>
#include <time.h>
#include ".\log.h"
#include <DebugOutput.h>

#define FILTERSETTING_LOGGER_FILE		".\\log\\service.log"
#define FILTERSETTING_DEBUG_FILE		".\\log\\dservice.log"


class CFilterSettingModule : public CAtlServiceModuleT< CFilterSettingModule, IDS_SERVICENAME >
{
public :
	DECLARE_LIBID(LIBID_FilterSettingLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILTERSETTING, "{92277243-F9BC-4ED8-9DD1-06D31FB572CF}")
	HRESULT InitializeSecurity() throw()
	{

		// TODO : 调用 CoInitializeSecurity 并为服务提供适当的 
		// 安全设置
		// 建议 - PKT 级别的身份验证、
		// RPC_C_IMP_LEVEL_IDENTIFY 的模拟级别
		// 以及适当的非空安全说明符。
		CSecurityDescriptor sd;
		sd.InitializeFromThreadToken();
		HRESULT hr = CoInitializeSecurity(sd, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_PKT,
				RPC_C_IMP_LEVEL_IMPERSONATE,  NULL, EOAC_NONE, NULL);
		if (FAILED(hr)) {
			LERR_<<"CoInitializeSecurity Failed with HRESULT value "<< hr;
		}

		return S_OK;
	}
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
};

CFilterSettingModule _AtlModule;

void initializeSetting() {
	// 获取注册信息
	g_licenseInfo.initialize();

	// 初始化配置
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH);
	g_configuration.loadConfig(config_path);
	LTRC_<<"AppConfig files path : "<< config_path;

	// 读取搜索词汇信息
	TCHAR filename[MAX_PATH];
	g_searchwordUtil.load(GetSearchWordFile(filename, MAX_PATH));
	LTRC_<<"SearchWord files path : "<< filename;

	// 读取访问网站的信息
	g_websitesUtil.load(GetWebSiteFile(filename, MAX_PATH));
	LTRC_<<"Website files path : "<< filename;
}

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	// 如果已经有程序启动，则直接推出
	HANDLE hMutex = CreateMutex(NULL, FALSE, COM_SERVICE_MUTEX);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hMutex);
		return 0;
	}


	g_hInstance = hInstance;
	g_licenseInfo.initialize();

	// 修复项
	// todo 此处应该直接使用函数获取状态
	// 获取应用程序状态
	AppUtility::AppInstallValidate validator(VALIDATE_COM, getAppStatus());
	validator.repair();

	initializeSetting();

	if (g_configuration.getWebHistoryRecordAutoClean()->shouldExec()) {
		g_configuration.getWebHistoryRecordAutoClean()->reset();
		LTRC_<<"Clear WebHistory";
		ClearHistory();
		
	}
	if (g_configuration.getScreenshotAutoClean()->shouldExec()) {
		g_configuration.getScreenshotAutoClean()->reset();
		LTRC_<<"Clear Screenshot";
		ClearScreen();
	}

	 // 开启服务线程
	ServThread::getInstance();
	
    return _AtlModule.WinMain(nShowCmd);
}


void CFilterSettingModule::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	CAtlServiceModuleT<CFilterSettingModule,IDS_SERVICENAME>::ServiceMain(dwArgc, lpszArgv);
}

namespace {
class LoggerInit {
public:
	LoggerInit() {
		 using namespace boost::logging;
#ifdef DEBUG
	init_debug_logger(FILTERSETTING_DEBUG_FILE, false, true);
	init_app_logger(FILTERSETTING_LOGGER_FILE, false, true);
	g_log_level()->set_enabled(level::debug);
#else
	init_app_logger(FILTERSETTING_LOGGER_FILE);
	g_log_level()->set_enabled(level::warning);
#endif
	}
};
LoggerInit g_logger_init;
};