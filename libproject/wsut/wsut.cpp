// wsut.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "wsut.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\FilterSetting.h>
#include <com\comutility.h>
#include <softwareStatus.h>
#include <AppInstallValidate.h>
#include <app_constants.h>
#include<typeconvert.h>
#include <apputility.h>
#include <comdef.h>
#include <logger_name.h>
#include "resource.h"

namespace {
class LoggerInit {
public:
	LoggerInit() {
		initLogger(WSUT_LOGGER_FILE);
	}
};

LoggerInit g_logger_init;

void SetUninstallStatus() {
	AutoInitInScale auto_;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER,
			IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			LOGGER_WRITE_COM_FAILED(WSUT_LOGGER_ERROR, "Create snowman", hr);
			return ;
		}

		pSetting->setApplicationStatus(SNOWMAN_STATUS_UNINSTALL);
		pSetting->Release();
		pSetting = NULL;
	} catch (_com_error & e) {
		LOGGER_WRITE_COM_DESCRIPTION(WSUT_LOGGER_ERROR, e.Description());
	}
}


bool CheckPoassword(LPCTSTR password) {
	AutoInitInScale auto_;
	try {
		VARIANT_BOOL bSucc;
		ISnowmanSetting *appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			LOGGER_WRITE_COM_FAILED(WSUT_LOGGER_ERROR, "Create snowman", hr);
			return false;
		}

		appSetting->CheckPwd(_bstr_t(password), &bSucc);
		SafeRelease(appSetting);
		return convert(bSucc);
	} catch (_com_error &e) {
		LOGGER_WRITE_COM_DESCRIPTION(WSUT_LOGGER_ERROR, e.Description());
		return false;
	}
}

};


WSUT_API __stdcall int CheckProgram(const char * status) {
	//  检测那些程序在运行
	return 0;
}
WSUT_API __stdcall int CheckStatus(const char * status) {
	AutoInitInScale _auto_scale__;

	if (true == CheckPoassword(status)) {
		return 0;
	} else {
		return -1;
	}
}
WSUT_API __stdcall int CallUtility(const char * status) {
	AutoInitInScale _auto_scale__;

	// 检测密码
	if (CheckStatus(status) != 0) {
		return -1;
	}

	SetUninstallStatus();

	// 调用过程
	AppUtility::UninstallShellExt();
	AppUtility::UninstallService();
	AppUtility::UninstallSPI();

	// 强行结束service
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
