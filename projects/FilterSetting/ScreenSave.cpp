// ScreenSave.cpp : CScreenSave µÄÊµÏÖ

#include "stdafx.h"
#include ".\screensave.h"
#include "globalvariable.h"
#include <sysutility.h>
#include <typeconvert.h>

// CScreenSave

STDMETHODIMP CScreenSave::InterfaceSupportsErrorInfo(REFIID riid)
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

STDMETHODIMP CScreenSave::enableScreenSave(VARIANT_BOOL enabled) {
	g_configuration.getScreenshotSetting()->enable(convert(enabled));
	return S_OK;
}

STDMETHODIMP CScreenSave::setTimeSpan(LONG seconds) {
	g_configuration.getScreenshotSetting()->setTimeSpan(seconds);
	return S_OK;
}

STDMETHODIMP CScreenSave::isEnabled(VARIANT_BOOL* enabled) {
	*enabled = convert(g_configuration.getScreenshotSetting()->isEnabled());
	return S_OK;
}

STDMETHODIMP CScreenSave::ClearCache(void) {
	ClearScreen(g_hInstance);
	return S_OK;
}

STDMETHODIMP CScreenSave::setAutoClearTimespan(LONG seconds)
{ 
	return S_OK;
}

STDMETHODIMP CScreenSave::get_AutocleanEnabled(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getScreenshotAutoClean()->isEnabled());
	return S_OK;
}

STDMETHODIMP CScreenSave::put_AutocleanEnabled(VARIANT_BOOL newVal)
{
	g_configuration.getScreenshotAutoClean()->enable(convert(newVal));
	return S_OK;
}
