#include "stdafx.h"
#include "COMutility.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <logger\logger.h>
#include <logger\loggerlevel.h>
#include <sstream>
#include <comdef.h>
#include <winlockdll.h>
#include <EyecareSetting.h>

BOOL ValidatePassword(LPCTSTR password) {
	try {
		__AUTO_FUNCTION_SCOPE_TRACE__;
		VARIANT_BOOL succeeded = FALSE;
		IAuthorize *authorize = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&authorize);
		if (FAILED(hr)) {
			__LERR__("Authorize FAILED with HRESULT : " << hr);
			return FALSE;
		}

		authorize->checkPassword(_bstr_t(password), &succeeded);
		authorize->Release();

		return convert(succeeded);
	} catch (_com_error &e) {
		__LERR__("exception with descripion : " <<e.Description());
		return FALSE;
	}
}

BOOL IsRunInEnterModel() {
	__AUTO_FUNCTION_SCOPE_TRACE__;

	try {
		IEyecare *pEyeCare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
		if (FAILED(hr)) {
			__LERR__("Eyecare FAILED with HRESULT : " << hr);
			return FALSE;
		}

		LONG state;
		pEyeCare->getState(&state);
	
		pEyeCare->Release();
		return state == EyecareSetting::ENTERT_TIME ? TRUE : FALSE;
	} catch (_com_error &e) {
		__LERR__("exception with descripion : " <<e.Description());
		return FALSE;
	}
}
BOOL IsRuninParentModel() {
	__AUTO_FUNCTION_SCOPE_TRACE__;

	try {
		VARIANT_BOOL parent_mode = VARIANT_FALSE;
		ISnowmanSetting *app = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			__LERR__("Setting FAILED with HRESULT : " << hr);
			return FALSE;
		}

		app->get_ParentModel(&parent_mode);

		return convert(parent_mode);
	} catch (_com_error &e) {
		__LERR__("exception with descripion : " <<e.Description());
		return FALSE;
	}
}

BOOL TRYEndEyecare(LPCTSTR password) {
	__AUTO_FUNCTION_SCOPE_TRACE__;

	try {
		VARIANT_BOOL succeeded = FALSE;
		IEyecare *eyecare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&eyecare);
		if (FAILED(hr)) {
			__LERR__("Eyecare FAILED with HRESULT : " << hr);
			return FALSE;
		}

		eyecare->endEyecare(_bstr_t(password), &succeeded);
		eyecare->Release();

		return convert(succeeded);
	} catch (_com_error &e) {
		__LERR__("exception with descripion : " <<e.Description());
		return FALSE;
	}
}

#define MAX_VALUE_EYECARE_LEFT_SECS   (60 * 60)

LONG GetEyecareLeftSeconds() {
	__AUTO_FUNCTION_SCOPE_TRACE__;
	try {
		IEyecare *pEyeCare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
		if (FAILED(hr)) {
			__LERR__("Failed on Create Eyecare with HRESULT value "<<std::hex<<hr);
		} else {
			LONG seconds;
			pEyeCare->getTimeLeft(&seconds);
			return seconds;
		}
	} catch (_com_error &e) {
		__LERR__("exception with descripion : " <<e.Description());
	}
	return MAX_VALUE_EYECARE_LEFT_SECS;
}