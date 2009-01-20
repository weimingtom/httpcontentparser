#include "stdafx.h"
#include ".\services.h"
#include ".\globalvariable.h"
#include <com\comutility.h>
#include <typeconvert.h>

bool Services::isParentModel() {
	AutoInitInScale auto_;
	try {
		IAppSetting * appSetting = NULL;
		// ��ȡϵͳ����
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, 
			NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);

		if (FAILED(hr)) {
			return false;
		}

		VARIANT_BOOL bParent;
		appSetting->get_ParentModel(&bParent);
		SafeRelease(appSetting);
		return convert(bParent);
	} catch (_com_error &) {
		return false;
	}
}
bool Services::switchParentModel(LPCTSTR password) {
	AutoInitInScale auto_;
	try {
		VARIANT_BOOL bSucc;
		IAppSetting *appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			return false;
		}

		appSetting->switchModel(VARIANT_TRUE, _bstr_t(password), &bSucc);
		SafeRelease(appSetting);
		return convert(bSucc);
	} catch (_com_error &) {
		return false;
	}
}

void Services::switchChildModel() {
	AutoInitInScale auto_;
	try {
		VARIANT_BOOL bSucc;
		IAppSetting *appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			return;
		}

		appSetting->switchModel(VARIANT_FALSE, _bstr_t(TEXT("")), &bSucc);
		SafeRelease(appSetting);
		return ;
	} catch (_com_error &) {
	}
}