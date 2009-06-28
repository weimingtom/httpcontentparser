// AppLaunchFilter.cpp : CAppLaunchFilter 的实现

#include "stdafx.h"
#include "AppLaunchFilter.h"
#include <DebugOutput.h>
#include <apputility.h>
#include ".\global.h"

// CAppLaunchFilter
STDMETHODIMP CAppLaunchFilter::Execute(LPSHELLEXECUTEINFO  pei) {
	HRESULT hResult = S_FALSE;
	try {

		AutoInitInScale atuo_init_com_;
		IAppControl *appControl  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&appControl);
		if (FAILED(hr)) {
			_DEBUG_STREAM_TRC_("[Family007 ShellExt]  ["<<__FUNCTION__<<"] Appcontrol launch failed with RETURL : " << hr);
			return S_FALSE;
		}

		VARIANT_BOOL can_be_executed;
		_bstr_t bstrFilepath((const wchar_t*)pei->lpFile);
		appControl->checkApp(bstrFilepath, &can_be_executed);
		if (can_be_executed == VARIANT_FALSE) {
			// 如果验证失败
			hResult = S_OK;
		}

		if (NULL != appControl) {
			appControl->Release();
			appControl = NULL;
		}
		
	} catch (...) {
		_DEBUG_STREAM_TRC_("[Family007 ShellExt]  ["<<__FUNCTION__<<"] Unknown exception.");
		hResult = S_FALSE;
	}

	return hResult;
}

