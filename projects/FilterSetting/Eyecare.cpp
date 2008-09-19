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
	// g_configuration.getEyecareSetting()->setPassword(_bstr_t(password)); 
	return S_OK;
}

STDMETHODIMP CEyecare::setEyecareTime(LONG mintues) {
	g_configuration.getEyecareSetting()->setEyecareTime(mintues);
	return S_OK;
}

STDMETHODIMP CEyecare::setEnterTime(LONG mintues) {
	g_configuration.getEyecareSetting()->setEnterTime(mintues);
	return S_OK;
}

STDMETHODIMP CEyecare::getEyecareTime(LONG* second) {
	*second = g_configuration.getEyecareSetting()->getEyecareTime();
	return S_OK;
}

STDMETHODIMP CEyecare::getEnterTime(LONG* second) {
	*second = g_configuration.getEyecareSetting()->getEnterTime();
	return S_OK;
}

STDMETHODIMP CEyecare::getTimeLeft(LONG* second) {
	*second = g_configuration.getEyecareSetting()->getRemainTime();
	return S_OK;
}

STDMETHODIMP CEyecare::getState(LONG* state) {
	*state = g_configuration.getEyecareSetting()->getState();
	return S_OK;
}

STDMETHODIMP CEyecare::swithToEntertainment(BSTR password, VARIANT_BOOL *bSuccess) {
	*bSuccess = g_configuration.getEyecareSetting()->switchState((char*)_bstr_t(password));
	return S_OK;
}

STDMETHODIMP CEyecare::trySwitch(LONG* state) {
	*state = g_configuration.getEyecareSetting()->trySwitch();
	return S_OK;
}

STDMETHODIMP CEyecare::LockScreen(void) {
	g_configuration.getEyecareSetting()->ForceLockWnd();
	return S_OK;
}
