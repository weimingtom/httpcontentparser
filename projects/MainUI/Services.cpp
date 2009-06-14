#include "stdafx.h"
#include ".\services.h"
#include ".\globalvariable.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <softwareStatus.h>
#include ".\log.h"

LONG Services::getAppStatus() {
	AutoInitInScale auto_;
	try {
		LONG status;
		ISnowmanSetting *pRegInfo = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pRegInfo);
		if (SUCCEEDED(hr)) {
			pRegInfo->getApplicationStatus(&status);
			return status;
		} else {
			LERR_<< "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr;
			return SNOWMAN_STATUS_TRIAL;
		}
	} catch (...) {
		LERR_<<"CATCH(...)";
	}
}

bool Services::isParentModel() {
	AutoInitInScale auto_;
	try {
		ISnowmanSetting * appSetting = NULL;
		// 获取系统设置
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, 
			NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);

		if (FAILED(hr)) {
			LERR_<< "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr;
			return false;
		}

		VARIANT_BOOL bParent;
		appSetting->get_ParentModel(&bParent);
		SafeRelease(appSetting);
		return convert(bParent);
	} catch (_com_error & e) {
		LERR_<< "_com_error exception with description "<< e.Description();
		return false;
	}
}
bool Services::switchParentModel(LPCTSTR password) {
	AutoInitInScale auto_;
	try {
		VARIANT_BOOL bSucc;
		ISnowmanSetting *appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			LERR_<< "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr;
			return false;
		}

		appSetting->switchModel(VARIANT_TRUE, _bstr_t(password), &bSucc);
		SafeRelease(appSetting);
		return convert(bSucc);
	} catch (_com_error & e) {
		LERR_<< "_com_error exception with description "<< e.Description();
		return false;
	}
}

void Services::switchChildModel() {
	AutoInitInScale auto_;
	try {
		VARIANT_BOOL bSucc;
		ISnowmanSetting *appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			LERR_<< "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr;
			return;
		}

		appSetting->switchModel(VARIANT_FALSE, _bstr_t(TEXT("")), &bSucc);
		SafeRelease(appSetting);
		return ;
	} catch (_com_error & e) {
		LERR_<< "_com_error exception with description "<< e.Description();
	}
}