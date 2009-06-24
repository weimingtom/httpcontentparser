#include "stdafx.h"
#include ".\services.h"
#include ".\globalvariable.h"
#include ".\resource.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <softwareStatus.h>
#include <logger\logger.h>


#define PASSWORD_MIN_LENGTH 8

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
			return convert(val);
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
		if (FAILED(hr)) {
			__LERR__( "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr);
			return SNOWMAN_STATUS_TRIAL;
		} else {
			pRegInfo->getApplicationStatus(&status);
			return status;
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
	return  ! registered();
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

bool Services::setNewPwd(LPCTSTR newpwd, LPCTSTR oldpwd) {
	// 直接查看密码是不是默认密码
	AutoInitInScale auto_;
	try {
		IAuthorize *pAuthor = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&pAuthor);
		if (FAILED(hr)) {
			__LERR__( "Create Authorize with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		VARIANT_BOOL succ;
		hr = pAuthor->changePassword(_bstr_t(newpwd), _bstr_t(oldpwd),  &succ);
		if (FAILED(hr)) {
			__LERR__( "call setpwd failed with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		SafeRelease(pAuthor);
		return convert(succ);
	} catch (_com_error & e) {
		__LERR__( "_com_error exception with description "<< e.Description());
		return false;
	}
}
bool Services::setPwdForFirstTime(LPCTSTR newpwd) {
	return setNewPwd(newpwd, DEFAULT_INIT_PASSWORD);
}

bool Services::firstOpen() {
	// 直接查看密码是不是默认密码
	AutoInitInScale auto_;
	try {
		IAuthorize *pAuthor = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&pAuthor);
		if (FAILED(hr)) {
			__LERR__( "Create Authorize with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		VARIANT_BOOL succ;
		hr = pAuthor->checkPassword(_bstr_t(DEFAULT_INIT_PASSWORD),  &succ);
		if (FAILED(hr)) {
			__LERR__( "call check failed with HRESULT vlaue "<<std::hex<<hr);
			return false;
		}

		SafeRelease(pAuthor);
		return convert(succ);
	} catch (_com_error & e) {
		__LERR__( "_com_error exception with description "<< e.Description());
		return false;
	}
}

int Services::validatePwd(const CString &strNewPwd, const CString & strPwdConfirm){
	if (strNewPwd != strPwdConfirm) {
		return IDS_PWD_NOT_SAME_WITH_CONFIRM;
	} else if (strNewPwd.GetLength() < PASSWORD_MIN_LENGTH) {
		// 密码长度不能短于8位
		return IDS_PWD_NEW_PWD_TOO_SHORT;
	} else {
		return 0;
	}
}