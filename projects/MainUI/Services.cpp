#include "stdafx.h"
#include ".\services.h"
#include ".\globalvariable.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <softwareStatus.h>
#include <logger\logger.h>

// �����ڹر�ʱ���Ƿ�ת��Ϊ����ģʽ
bool Services::autoSwithOnClose() {
	// ����
	try {
		ISnowmanSetting *app = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			__LERR__("failed on create snowmansetting with HRESULT value : "<<hr);
			return false;
		}
		
		// �Ƿ���Ҫ�л���ģʽ
		VARIANT_BOOL val;
		hr = app->get_autoSwitchOnClose(&val);
		if (FAILED(hr)) {
			__LERR__("failed call function  SnowmanSetting get_autoSwitchOnClose () with HRESULT value : "<<hr);
			return false;
		} else {
			return convert(VARIANT_TRUE);
		}

	} catch (...) {
		__LERR__( "CATCH(...)");
		return false;
	}
}
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
			__LERR__( "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr);
			return SNOWMAN_STATUS_TRIAL;
		}
	} catch (...) {
		__LERR__("CATCH(...)");
	}

	return SNOWMAN_STATUS_TRIAL;
}

bool Services::isParentModel() {
	AutoInitInScale auto_;
	try {
		ISnowmanSetting * appSetting = NULL;
		// ��ȡϵͳ����
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, 
			NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);

		if (FAILED(hr)) {
			__LERR__( "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		VARIANT_BOOL bParent;
		appSetting->get_ParentModel(&bParent);
		SafeRelease(appSetting);
		return convert(bParent);
	} catch (_com_error & e) {
		__LERR__( "_com_error exception with description "<< e.Description());
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
			__LERR__( "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		appSetting->switchModel(VARIANT_TRUE, _bstr_t(password), &bSucc);
		SafeRelease(appSetting);
		return convert(bSucc);
	} catch (_com_error & e) {
		__LERR__( "_com_error exception with description "<< e.Description());
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
			__LERR__( "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr);
			return;
		}

		appSetting->switchModel(VARIANT_FALSE, _bstr_t(TEXT("")), &bSucc);
		SafeRelease(appSetting);
		return ;
	} catch (_com_error & e) {
		__LERR__( "_com_error exception with description "<< e.Description());
	}
}