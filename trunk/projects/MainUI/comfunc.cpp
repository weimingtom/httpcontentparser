#include "stdafx.h"
#include ".\globalvariable.h"
#include ".\confunc.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>

bool registered() {
	try {
		IAppSetting *pApp  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&pApp);
		if (FAILED(hr)) {
			return false;
		}

		VARIANT_BOOL bRegistered;
		pApp->Registered(&bRegistered);
		// pApp->Release();
		return convert(bRegistered);
	} catch (...) {
		return false;
	}
}
int trialLeftDays() {
	try {
		IAppSetting *pApp  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&pApp);
		if (FAILED(hr)) {
			return 1;
		}

		VARIANT_BOOL bRegistered;
		LONG leftDays;
		pApp->Registered(&bRegistered);

		if (bRegistered != VARIANT_TRUE) {
			pApp->get_LeftDays(&leftDays);
			return leftDays;
		} else {
			return -1;
		}
	} catch (...) {
		return 1;
	}
}

bool registerSN(const std::string &sn) {
	try {
		IAppSetting *pApp  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&pApp);
		if (FAILED(hr)) {
			return false;
		}

		VARIANT_BOOL bSucc;
		pApp->Register(_bstr_t(sn.c_str()), &bSucc);

		return convert(bSucc);
	} catch (...) {
		return false;
	}
}