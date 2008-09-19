// Eyecare.cpp : CEyecare µÄÊµÏÖ

#include "stdafx.h"
#include "Eyecare.h"
#include ".\eyecare.h"

#include "FilterSetting.h"
#include "globalvariable.h"

#include <eyecaresetting.h>
// CEyecare

CEyecare::CEyecare() {
}
STDMETHODIMP CEyecare::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEyecare
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CEyecare::setPassword(BSTR password) {
	// g_Eyecare_setting_.setPassword(_bstr_t(password)); 
	return S_OK;
}

STDMETHODIMP CEyecare::setEyecareTime(LONG mintues) {
	g_Eyecare_setting_.setEyecareTime(mintues);
	return S_OK;
}

STDMETHODIMP CEyecare::setEnterTime(LONG mintues) {
	g_Eyecare_setting_.setEnterTime(mintues);
	return S_OK;
}

STDMETHODIMP CEyecare::getEyecareTime(LONG* second) {
	*second = g_Eyecare_setting_.getEyecareTime();
	return S_OK;
}

STDMETHODIMP CEyecare::getEnterTime(LONG* second) {
	*second = g_Eyecare_setting_.getEnterTime();
	return S_OK;
}

STDMETHODIMP CEyecare::getTimeLeft(LONG* second) {
	*second = g_Eyecare_setting_.getRemainTime();
	return S_OK;
}

STDMETHODIMP CEyecare::getState(LONG* state) {
	*state = g_Eyecare_setting_.getState();
	return S_OK;
}

STDMETHODIMP CEyecare::swithToEntertainment(BSTR password, VARIANT_BOOL *bSuccess) {
	*bSuccess = g_Eyecare_setting_.switchState((char*)_bstr_t(password));
	return S_OK;
}

STDMETHODIMP CEyecare::trySwitch(LONG* state) {
	*state = g_Eyecare_setting_.trySwitch();
	return S_OK;
}

STDMETHODIMP CEyecare::LockScreen(void) {
	g_Eyecare_setting_.ForceLockWnd();
	return S_OK;
}
