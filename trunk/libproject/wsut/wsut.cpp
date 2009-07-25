// wsut.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "wsut.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\FilterSetting.h>
#include <com\comutility.h>
#include <softwareStatus.h>
#include <apputility\AppInstallValidate.h>
#include <apputility\apputility.h>
#include <app_constants.h>
#include<typeconvert.h>
#include <driver_const.h>
#include <comdef.h>
#include ".\logger_def.h"
#include "resource.h"
#include ".\log.h"


namespace {
bool checkInstalled();
void SetUninstallStatus();
bool CheckPoassword(LPCTSTR password) ;
void removeAutoRun();
BOOL LoadNTDriver(const TCHAR * lpszDriverName, TCHAR * lpszDriverPath) ;
int UnloadNTDriver(const TCHAR * szSvrName) ;
};

WSUT_API int		__stdcall		AuthorizateEveryone(const char * filepath) {
	Authorization();
	return 0;
}
WSUT_API int __stdcall  CheckProgram(const char * status) {
	//  �����Щ����������
	return 0;
}
WSUT_API int __stdcall  CheckStatus(const char * status) {
	AutoInitInScale _auto_scale__;

	if (true == CheckPoassword(status)) {
		return 0;
	} else {
		return -1;
	}
}
WSUT_API int __stdcall  CallUtility(const char * status) {
	AutoInitInScale _auto_scale__;

	// �������
	if (CheckStatus(status) != 0) {
		return -1;
	}

	SetUninstallStatus();

	// ���ù���
	AppUtility::UninstallService();
	AppUtility::UninstallSPI();

	// ǿ�н���service
	removeAutoRun();
	return 0;
}

// �鿴����Ƿ��Ѿ���װ
WSUT_API bool __stdcall  Installed() {
	return checkInstalled();
}

// ����Ѿ���װ��֪ͨ���ж�أ�����
// ��������а�װ
WSUT_API int __stdcall MakePrepareInstall() {
	// ����Ӧ�ó���Ϊж��ģʽ
	return 0;
}

WSUT_API int __stdcall GetInstallAppPath(char *buffer, const int length) {
	return 0;
}

WSUT_API int		__stdcall		InstallDriver(char * path) {
	LoadNTDriver(APPCONTROL_SERVICE, path);
	return 0;
}
WSUT_API int		__stdcall		UninstallDriver() {
	UnloadNTDriver(APPCONTROL_SERVICE);
	return 0;
}
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}


namespace {
bool CheckPoassword(LPCTSTR password) {
	AutoInitInScale auto_;
	try {
		VARIANT_BOOL bSucc;
		ISnowmanSetting *appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			LERR_<<"Create snowman FAILED with HRESULT value "<< hr;
			return false;
		}

		appSetting->CheckPwd(_bstr_t(password), &bSucc);
		SafeRelease(appSetting);
		return convert(bSucc);
	} catch (_com_error &e) {
		LERR_<<"_com_error exception with Description :  "<< e.Description();
		return false;
	}
}

void removeAutoRun() {
	TCHAR fullpath[MAX_PATH], apppath[MAX_PATH], installPath[MAX_PATH];
	GetModuleFileName(NULL, fullpath, MAX_PATH);
	GetFileNameDir(fullpath, installPath, MAX_PATH);
	_sntprintf(apppath, MAX_PATH, "%s\\%s", installPath, APPLICATION_MAINUI_EXE_FILE);
	RegisterAutoRun(apppath, FALSE);
}

void SetUninstallStatus() {
	AutoInitInScale auto_;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER,
			IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			LERR_<<"Create snowman FAILED with HRESULT value "<< hr;
			return ;
		}

		pSetting->setApplicationStatus(SNOWMAN_STATUS_UNINSTALL);
		pSetting->Release();
		pSetting = NULL;
	} catch (_com_error & e) {
		LERR_<<"_com_error exception with Description :  "<< e.Description();
	}
}

bool checkInstalled() {
	AutoInitInScale auto_;
	bool result = false;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER,
			IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			// ����ӿ���ʾΪû��ע�ᣬ ���˳���װ
			result =   false;
		} else {
			result = true;
		}
		
		pSetting->Release();
		pSetting = NULL;
	} catch (_com_error & e) {
		LERR_<<"_com_error exception with Description :  "<< e.Description();
	}

	return result;
}

int UnloadNTDriver(const TCHAR * szSvrName) 
{
	int rc = 0;
	SC_HANDLE hServiceMgr = NULL;
	SC_HANDLE hServiceDDK = NULL;
	SERVICE_STATUS SvrSta;

	hServiceMgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hServiceMgr == NULL) {
		LERR_<<"OpenSCManager() Failed with : " <<GetLastError();
		rc = 1;
		goto exit;
	} 

	hServiceDDK = OpenService(hServiceMgr, szSvrName, SERVICE_ALL_ACCESS);
	if (NULL == hServiceDDK) {
		LERR_<<"OpenService() Failed with error : " << GetLastError();
		rc = 1;
		goto exit;
	}

	if ( !ControlService(hServiceDDK, SERVICE_CONTROL_STOP, &SvrSta)) {
		LERR_<<"ControlService failed with error : " << GetLastError();
		rc = 1;
		goto exit;
	}

	if ( !DeleteService(hServiceDDK)) {
		LERR_<<"DeleteService failed with error : " << GetLastError();
		rc = 1;
		goto exit;
	}

exit:
	if (NULL != hServiceDDK) {
		CloseServiceHandle(hServiceDDK);
	}

	if (NULL != hServiceMgr) {
		CloseServiceHandle(hServiceMgr);
	}

	return rc;
}

BOOL LoadNTDriver(const TCHAR * lpszDriverName, TCHAR * lpszDriverPath) {
	int rc = 0;
	TCHAR szDriverImagePath[MAX_PATH];
	GetFullPathName(lpszDriverPath, MAX_PATH, szDriverImagePath, NULL);
	SC_HANDLE hSCM = NULL;
	SC_HANDLE hSerDDK = NULL;

	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL != hSCM) {
		LERR_<<("OpenSCM() Failed : %d"), GetLastError();
		rc = 1;
		goto exit;
	}

	hSerDDK = CreateService(hSCM, lpszDriverName, lpszDriverName, SERVICE_ALL_ACCESS, 
		SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, szDriverImagePath,
		NULL, NULL, NULL, NULL, NULL);

	if (NULL == hSerDDK) {
		const DWORD dwRtn = GetLastError();
		if (dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_EXISTS) {
			rc = 0;
			LERR_<<("CreateService failed ") << GetLastError();
			goto exit;
		}

		// ����Ѿ����ڣ����
		hSerDDK = OpenService(hSerDDK, lpszDriverName, SERVICE_ALL_ACCESS);
		if (NULL == hSerDDK) {
			LERR_<<("OpenService failed with error ") <<  GetLastError();
			rc = 1;
			goto exit;
		}
	}

	rc = StartService(hSerDDK, NULL, NULL);
	if (0 == rc) {
		const DWORD dwError = GetLastError();
		if (dwError == ERROR_SERVICE_ALREADY_RUNNING) {
			LERR_<<("The Service has been running..");
		} else if (dwError == ERROR_IO_PENDING) {
			LERR_<<("IO Pending");
		} else {
			LERR_<<("StartService failed ") << GetLastError();
			goto exit;
		}
	}

exit:
	if (NULL != hSerDDK) {
		CloseServiceHandle(hSerDDK);
	}

	if (NULL != hSCM) {
		CloseServiceHandle(hSerDDK);
	}

	return rc;
}

class LoggerInit {
public:
	LoggerInit() {
		using namespace boost::logging;
#ifdef DEBUG
		init_debug_logger(WSUT_DEBUG_FILE, false, true);
		init_app_logger(WSUT_LOGGER_FILE, false,true);
		g_log_level()->set_enabled(level::debug);
#else
		init_app_logger(WSUT_LOGGER_FILE);
		g_log_level()->set_enabled(level::warning);
#endif
	}
};
LoggerInit g_logger_init;
};