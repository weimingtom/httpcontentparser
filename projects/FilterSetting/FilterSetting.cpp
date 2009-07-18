// FilterSetting.cpp : WinMain 的实现

#include "stdafx.h"
#include "resource.h"
#include "globalvariable.h"
#include "FilterSetting.h"
#include ".\servthread.h"
#include ".\driverMngr.h"
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

#define FILTERSETTING_LOGGER_FILE		TEXT(".\\log\\service.log")
#define FILTERSETTING_DEBUG_FILE		TEXT(".\\log\\dservice.log")

#define COM_SERVICE_MUTEX		TEXT("D2C30A28-477B-4651-B392-81246240A169")

void initlogger() ;
void initializeSetting();
bool checkEmbedding(LPCTSTR lpstrCmdLine) ;
class AppCheck : public CheckProcessCreate {
public:
	virtual bool enable_process_create(const char * process_path_name) {
		return checkApppath(process_path_name);
	}
};

AppCheck appchecker;
AppController appcontroller(&appchecker);

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



extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR lpCmdLine, int nShowCmd)
{
	// 根据lpCmdLine进行区分， 如果是注册组件或者卸载组件
	// 则直接运行_AtlModule.WinMain(nShowCmd);
	// 如果是COM方式运行，则应该执行下面一些列操作

	if (checkEmbedding(lpCmdLine)) {
		_DEBUG_STREAM_TRC_("[Family007 Service] Cmd line "<<lpCmdLine);
		// 只应该运行一次
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

		// 开启检测应用程序的线程
		appcontroller.begin();
	} else {
		_DEBUG_STREAM_TRC_("[Family007 Service] Cmd line without "<<lpCmdLine);
	}

	 return _AtlModule.WinMain(nShowCmd);
}


void CFilterSettingModule::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	CAtlServiceModuleT<CFilterSettingModule,IDS_SERVICENAME>::ServiceMain(dwArgc, lpszArgv);
}

void initlogger() {
	using namespace boost::logging;
	init_debug_logger(".\\log\\dEyecare.log");
	init_app_logger(".\\log\\Eyecare.log");
	set_logger_level(LOGGER_LEVEL);
}


bool checkEmbedding(LPCTSTR lpstrCmdLine) {
	return true;
}

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
