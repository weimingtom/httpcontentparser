// AppLaunchFilter.cpp : CAppLaunchFilter ��ʵ��

#include "stdafx.h"
#include "AppLaunchFilter.h"
#include <apputility.h>
#include ".\global.h"

// CAppLaunchFilter
STDMETHODIMP CAppLaunchFilter::Execute(LPSHELLEXECUTEINFO  pei) {
	HRESULT hResult = S_FALSE;
	try {
		TCHAR driver[MAX_PATH], folder[MAX_PATH], name[MAX_PATH], ext[MAX_PATH], comfilename[MAX_PATH];
		TCHAR installpath[MAX_PATH];

		// ��ȡDLL·��
		GetModuleFileName(g_hInstance, comfilename, MAX_PATH);
		_splitpath(comfilename, driver, folder, name, ext);
		_snprintf(installpath, MAX_PATH, "%s%s", driver, folder);

		// ��������ڰ�װĿ¼�£� ��Ҫ���ֱ�ӷ���
		if (pei->lpFile == _tcsstr(pei->lpFile, installpath)) {
			throw int(0);
		}

		GetModuleFileName(NULL, installpath, MAX_PATH);
		// �Զ���ʼ��COM
		AutoInitInScale atuo_init_com_;
	
		IAppControl *appControl  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&appControl);
		if (FAILED(hr)) {
			return S_FALSE;
		}

		VARIANT_BOOL can_be_executed;
		_bstr_t bstrFilepath((const wchar_t*)pei->lpFile);
		appControl->checkApp(bstrFilepath, &can_be_executed);
		if (can_be_executed == VARIANT_FALSE) {
			// �����֤ʧ��
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

