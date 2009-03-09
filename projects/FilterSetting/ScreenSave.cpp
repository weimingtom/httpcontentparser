// ScreenSave.cpp : CScreenshotRecord µÄÊµÏÖ

#include "stdafx.h"
#include ".\screensave.h"
#include "globalvariable.h"
#include <apputility.h>
#include <typeconvert.h>

// CScreenshotRecord

STDMETHODIMP CScreenshotRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IScreenSave
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CScreenshotRecord::enableScreenSave(VARIANT_BOOL enabled) {
	g_configuration.getScreenshotSetting()->enable(convert(enabled));
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::setTimeSpan(LONG seconds) {
	g_configuration.getScreenshotSetting()->setTimeSpan(seconds);
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::getTimeSpan(LONG* secs)
{
	*secs = g_configuration.getScreenshotSetting()->getTimeSpan();
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::isEnabled(VARIANT_BOOL* enabled) {
	*enabled = convert(g_configuration.getScreenshotSetting()->isEnabled());
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::ClearCache(void) {
	ClearScreen(g_hInstance);
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::getAutoClearSpan(LONG* days)
{
	*days = g_configuration.getScreenshotAutoClean()->getTimespan();
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::setAutoClearTimespan(LONG days)
{ 
	g_configuration.getScreenshotAutoClean()->setTimespan(days);
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::get_AutocleanEnabled(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getScreenshotAutoClean()->isEnabled());
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::put_AutocleanEnabled(VARIANT_BOOL newVal)
{
	g_configuration.getScreenshotAutoClean()->enable(convert(newVal));
	return S_OK;
}


STDMETHODIMP CScreenshotRecord::isSettingEnabled(VARIANT_BOOL* enabled)
{
	*enabled = convert(g_configuration.getScreenshotSetting()->isSettingEnabled());
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::enableAutoClear(VARIANT_BOOL enabled)
{
	g_configuration.getScreenshotAutoClean()->enable(convert(enabled));
	return S_OK;
}

STDMETHODIMP CScreenshotRecord::isAutoClearEnabled(VARIANT_BOOL* enabled)
{
	*enabled = convert(g_configuration.getScreenshotAutoClean()->isSettingEnabled());
	return S_OK;
}


