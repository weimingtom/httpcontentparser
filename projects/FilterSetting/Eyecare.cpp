// Eyecare.cpp : CEyecare µÄÊµÏÖ

#include "stdafx.h"
#include "Eyecare.h"
#include ".\eyecare.h"


#include "FilterSetting.h"
#include "globalvariable.h"
#include <typeconvert.h>
#include <eyecaresetting.h>
// CEyecare

CEyecare::CEyecare() {
}

HRESULT CEyecare::FinalConstruct()
{
	if (SettingItem::getModel() == SettingItem::MODE_PARENT) {
		g_configuration.getEyecareSetting()->stopTimer();
	} else {
		if (g_configuration.getEyecareSetting()->isEnabled() && g_configuration.getEyecareSetting()->isTimerStopped()) {
			g_configuration.getEyecareSetting()->restartTimer();
		}
	}
	return S_OK;
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

STDMETHODIMP CEyecare::endEyecare(BSTR password, VARIANT_BOOL *bSuccess) {
	int old_state = g_configuration.getEyecareSetting()->getState();
	int state = g_configuration.getEyecareSetting()->switchState((char*)_bstr_t(password));
	*bSuccess = (state != old_state) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CEyecare::trySwitch(LONG* state) {
	*state = g_configuration.getEyecareSetting()->trySwitch();
	return S_OK;
}

STDMETHODIMP CEyecare::setTermMode(LONG mode) {
	assert(mode == EyecareSetting::EYECARE_TERMIN_ENTERSU || 
		mode == EyecareSetting::EYECARE_TERMIN_RESETTIMER);
	g_configuration.getEyecareSetting()->setTerimatedMode(mode);
	return S_OK;
}

STDMETHODIMP CEyecare::getTermMode(LONG* mode) {
	*mode = g_configuration.getEyecareSetting()->getTerminatedMode();
	return S_OK;
}

STDMETHODIMP CEyecare::enableEyecare(VARIANT_BOOL enabled) {
	g_configuration.getEyecareSetting()->enable(convert(enabled));
	return S_OK;
}

STDMETHODIMP CEyecare::isSettingEnabled(VARIANT_BOOL* enabled)
{
	*enabled = convert(g_configuration.getEyecareSetting()->isSettingEnabled());
	return S_OK;
}
