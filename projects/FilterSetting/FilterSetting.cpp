// FilterSetting.cpp : WinMain ��ʵ��

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

		// TODO : ���� CoInitializeSecurity ��Ϊ�����ṩ�ʵ��� 
		// ��ȫ����
		// ���� - PKT ����������֤��
		// RPC_C_IMP_LEVEL_IDENTIFY ��ģ�⼶��
		// �Լ��ʵ��ķǿհ�ȫ˵������
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
	// ����lpCmdLine�������֣� �����ע���������ж�����
	// ��ֱ������_AtlModule.WinMain(nShowCmd);
	// �����COM��ʽ���У���Ӧ��ִ������һЩ�в���

	if (checkEmbedding(lpCmdLine)) {
		_DEBUG_STREAM_TRC_("[Family007 Service] Cmd line "<<lpCmdLine);
		// ֻӦ������һ��
		HANDLE hMutex = CreateMutex(NULL, FALSE, COM_SERVICE_MUTEX);
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			CloseHandle(hMutex);
			return 0;
		}

		initlogger();

		g_hInstance = hInstance;
		refreshAppstatus();

		// �޸���
		// todo �˴�Ӧ��ֱ��ʹ�ú�����ȡ״̬
		// ��ȡӦ�ó���״̬
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

		// ���������߳�
		ServThread::getInstance();

		// �������Ӧ�ó�����߳�
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
	// ��ʼ������
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH);
	g_configuration.loadConfig(config_path);
	__LTRC__("AppConfig files path : "<< config_path);

	// ��ȡ�����ʻ���Ϣ
	TCHAR filename[MAX_PATH];
	g_searchwordUtil.load(GetSearchWordFile(filename, MAX_PATH));
	__LTRC__("SearchWord files path : "<< filename);

	// ��ȡ������վ����Ϣ
	g_websitesUtil.load(GetWebSiteFile(filename, MAX_PATH));
	__LTRC__("Website files path : "<< filename);

	// ���logdir�������򴴽�
	TCHAR logdir[MAX_PATH];
	GetLogDirectory(logdir, MAX_PATH);
}
