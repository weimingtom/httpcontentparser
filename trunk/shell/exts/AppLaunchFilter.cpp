// AppLaunchFilter.cpp : CAppLaunchFilter 的实现

#include "stdafx.h"
#include "AppLaunchFilter.h"
#include <apputility.h>


// CAppLaunchFilter
STDMETHODIMP CAppLaunchFilter::Execute(LPSHELLEXECUTEINFO  pei) {
	HRESULT hResult = S_FALSE;
	try {
		// 如果程序在安装目录下， 不要检测直接返回
		TCHAR installpath[MAX_PATH];
		GetInstallPath(installpath, MAX_PATH);
		if (pei->lpFile == _tcsstr(pei->lpFile, installpath)) {
			throw int(0);
		}
		// 自动初始化COM
		AutoInitInScale atuo_init_com_;
	
		IAppControl *appControl  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&appControl);
		if (FAILED(hr)) {
			// TODO:
			return S_FALSE;
		}

		VARIANT_BOOL can_be_executed;
		appControl->checkApp(_bstr_t(pei->lpFile), &can_be_executed);
		if (can_be_executed == VARIANT_FALSE) {
			// 如果验证失败
			hResult = S_OK;
		}

		if (NULL != appControl) {
			appControl->Release();
			appControl = NULL;
		}

	} catch (...) {
	}
	return hResult;
}

