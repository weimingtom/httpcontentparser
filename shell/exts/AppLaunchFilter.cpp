// AppLaunchFilter.cpp : CAppLaunchFilter ��ʵ��

#include "stdafx.h"
#include "AppLaunchFilter.h"


// CAppLaunchFilter
STDMETHODIMP CAppLaunchFilter::Execute(LPSHELLEXECUTEINFO  pei) {
	try {
		// �Զ���ʼ��COM
		AutoInitInScale atuo_init_com_;
	
		IAppControl *appControl  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&appControl);
		if (FAILED(hr)) {
			// TODO:
			return S_FALSE;
		}

		// CHECK it;
		// appControl->

		if (NULL != appControl) {
			appControl->Release();
			appControl = NULL;
		}

	} catch (...) {
	}
	return S_FALSE;
}

