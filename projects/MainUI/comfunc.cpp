#include "stdafx.h"
#include ".\globalvariable.h"
#include ".\confunc.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>

bool registered() {
	try {
		IAppRegInfo *pAppReg  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppRegInfo, NULL, CLSCTX_LOCAL_SERVER, IID_IAppRegInfo, (LPVOID*)&pAppReg);
		if (FAILED(hr)) {
			return false;
		}

		VARIANT_BOOL bRegistered;
		pAppReg->Registered(&bRegistered);
		pAppReg->Release();
		return convert(bRegistered);
	} catch (...) {
		return false;
	}
}
int trialLeftDays() {
	try {
		IAppRegInfo *pAppReg  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppRegInfo, NULL, CLSCTX_LOCAL_SERVER, IID_IAppRegInfo, (LPVOID*)&pAppReg);
		if (FAILED(hr)) {
			return 1;
		}

		VARIANT_BOOL bRegistered;
		LONG leftDays;
		pAppReg->Registered(&bRegistered);

		if (bRegistered != VARIANT_TRUE) {
			pAppReg->get_LeftDays(&leftDays);
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
		IAppRegInfo *pAppReg  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppRegInfo, NULL, CLSCTX_LOCAL_SERVER, IID_IAppRegInfo, (LPVOID*)&pAppReg);
		if (FAILED(hr)) {
			return false;
		}

		VARIANT_BOOL bSucc;
		pAppReg->Register(_bstr_t(sn.c_str()), &bSucc);

		return convert(bSucc);
	} catch (...) {
		return false;
	}
}