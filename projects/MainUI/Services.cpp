#include "stdafx.h"
#include ".\services.h"
#include ".\globalvariable.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <softwareStatus.h>
#include <logger\logger.h>

// 当窗口关闭时，是否转换为父亲模式
bool Services::autoSwithOnClose() {
	// 设置
	AutoInitInScale auto_;
	try {
		ISnowmanSetting *app = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			__LERR__("failed on create snowmansetting with HRESULT value : "<<hr);
			return false;
		}
		
		// 是否需要切换到模式
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
		// 获取系统设置
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

bool Services::showRegisterMenuItem() {
	if (getAppStatus() == SNOWMAN_STATUS_REGISTERED) {
		return false;
	} else {
		return true;
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

bool Services::registered() {
	try {
		IAppRegInfo *pAppReg  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppRegInfo, NULL, CLSCTX_LOCAL_SERVER, IID_IAppRegInfo, (LPVOID*)&pAppReg);
		if (FAILED(hr)) {
			__LERR__( "Create APPRegInfo with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		VARIANT_BOOL bRegistered;
		pAppReg->Registered(&bRegistered);
		pAppReg->Release();
		return convert(bRegistered);
	} catch(_com_error &e) {
		__LERR__( "registered called failed with exception ..."<< e.Description());
		return false;
	} catch (...) {
		__LERR__( "registered called failed with exception ...");
		return false;
	}
}
int Services::trialLeftDays() {
	try {
		IAppRegInfo *pAppReg  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppRegInfo, NULL, CLSCTX_LOCAL_SERVER, IID_IAppRegInfo, (LPVOID*)&pAppReg);
		if (FAILED(hr)) {
			__LERR__( "Create APPRegInfo with HRESULT vlaue "<<std::hex<<hr);
			return 1;
		}

		VARIANT_BOOL bRegistered;
		LONG leftDays;
		pAppReg->Registered(&bRegistered);

		// 如果没有注册则返回剩余天数，否则返回-1
		if (bRegistered != VARIANT_TRUE) {
			pAppReg->get_LeftDays(&leftDays);
			return leftDays;
		} else {
			return -1;
		}
	} catch(_com_error &e) {
		__LERR__( "registered called failed with exception ..."<< e.Description());
		return false;
	} catch (...) {
		__LERR__( "registered called failed with exception ...");
		return 1;
	}
}

bool Services::registerSN(const std::string &sn) {
	try {
		IAppRegInfo *pAppReg  = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppRegInfo, NULL, CLSCTX_LOCAL_SERVER, IID_IAppRegInfo, (LPVOID*)&pAppReg);
		if (FAILED(hr)) {
			__LERR__( "Create APPRegInfo with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		VARIANT_BOOL bSucc;
		pAppReg->Register(_bstr_t(sn.c_str()), &bSucc);

		return convert(bSucc);
	} catch(_com_error &e) {
		__LERR__( "registered called failed with exception ..."<< e.Description());
		return false;
	} catch (...) {
		__LERR__( "registered called failed with exception ...");
		return false;
	}
}