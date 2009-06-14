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
#include ".\logger_def.h"
#include "resource.h"
#include ".\log.h"

namespace {
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
