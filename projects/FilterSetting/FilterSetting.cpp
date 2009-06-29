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
#include <logger\logger.h>
#include <logger\loggerlevel.h>
#include <DebugOutput.h>

#define COM_SERVICE_MUTEX	TEXT("7F6E3389-60CF-4b19-B1BD-BC6258E63BDC")

#define FILTERSETTING_LOGGER_FILE		".\\log\\service.log"
#define FILTERSETTING_DEBUG_FILE		".\\log\\dservice.log"

void initlogger() {
	using namespace boost::logging;
	init_debug_logger(".\\log\\dEyecare.log");
	init_app_logger(".\\log\\Eyecare.log");
	set_logger_level(LOGGER_LEVEL);
}



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
			__LERR__("CoInitializeSecurity Failed with HRESULT value "<< hr);
		}

		return S_OK;
	}
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
};

CFilterSettingModule _AtlModule;

void initializeSetting() {
	// 初始化配置
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH);
	g_configuration.loadConfig(config_path);
	__LTRC__("AppConfig files path : "<< config_path);

	// 读取搜索词汇信息
	TCHAR filename[MAX_PATH];
	g_searchwordUtil.load(GetSearchWordFile(filename, MAX_PATH));
	__LTRC__("SearchWord files path : "<< filename);

	// 读取访问网站的信息
	g_websitesUtil.load(GetWebSiteFile(filename, MAX_PATH));
	__LTRC__("Website files path : "<< filename);

	// 如果logdir不存在则创建
	TCHAR logdir[MAX_PATH];
	GetLogDirectory(logdir, MAX_PATH);
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

	initlogger();

	g_hInstance = hInstance;
	refreshAppstatus();

	// 修复项
	// todo 此处应该直接使用函数获取状态
	// 获取应用程序状态
	AppUtility::AppInstallValidate validator(VALIDATE_COM, getAppStatus());
	validator.repair();

	initializeSetting();

	if (g_configuration.getWebHistoryRecordAutoClean()->shouldExec()) {
		g_configuration.getWebHistoryRecordAutoClean()->reset();
		__LTRC__("Clear WebHistory");
		ClearHistory();
		
	}
	if (g_configuration.getScreenshotAutoClean()->shouldExec()) {
		g_configuration.getScreenshotAutoClean()->reset();
		__LTRC__("Clear Screenshot");
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