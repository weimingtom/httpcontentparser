// FilterSetting.cpp : WinMain ��ʵ��

#include "stdafx.h"
#include "resource.h"
#include "globalvariable.h"
#include "FilterSetting.h"
#include ".\servthread.h"
#include ".\registerinfo.h"
#include <utility\timeutility.h>
#include <AppinstallValidate.h>
#include <apputility.h>
#include <app_constants.h>
#include <passwordtype.h>
#include <webhistoryrecordersetting.h>
#include <xmlconfiguration.h>
#include <searchengine_define.h>
#include <searchkeywordutil.h>
#include <string>
#include <time.h>


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

		return S_OK;
	}
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
};

CFilterSettingModule _AtlModule;



void initializeSetting() {
	// ��ʼ������
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH, g_hInstance);
	g_configuration.loadConfig(config_path);

	// ��ȡ�����ʻ���Ϣ
	TCHAR filename[MAX_PATH];
	g_searchwordUtil.load(GetSearchWordFile(filename, MAX_PATH));

	// ��ȡ������վ����Ϣ
	g_websitesUtil.load(GetWebSiteFile(filename, MAX_PATH));
}

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	// ����Ѿ��г�����������ֱ���Ƴ�
	HANDLE hMutex = CreateMutex(NULL, FALSE, COM_SERVICE_MUTEX);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hMutex);
		return 0;
	}

	g_hInstance = hInstance;

	// TODO enable it. it shoud be used in for auto repair.
	// AppInstallValidate validator(VALIDATE_COM);
	// validator.repair((HMODULE)hInstance);

	initializeSetting();
	g_registerInfo.initialize();

	if (g_configuration.getWebHistoryRecordAutoClean()->shouldExec()) {
		g_configuration.getWebHistoryRecordAutoClean()->reset();
		ClearHistory((HMODULE)hInstance);
		
	}
	if (g_configuration.getScreenshotAutoClean()->shouldExec()) {
		g_configuration.getScreenshotAutoClean()->reset();
		ClearScreen((HMODULE)hInstance);
	}

	 // ���������߳�
	ServThread::getInstance();
	
    return _AtlModule.WinMain(nShowCmd);
}


void CFilterSettingModule::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	CAtlServiceModuleT<CFilterSettingModule,IDS_SERVICENAME>::ServiceMain(dwArgc, lpszArgv);
}
