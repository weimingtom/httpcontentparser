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
	g_configuration.getScreenSave()->enable(convert(enabled));
	return S_OK;
}

STDMETHODIMP CScreenSave::setTimeSpan(LONG seconds) {
	g_configuration.getScreenSave()->setTimeSpan(seconds);
	return S_OK;
}

STDMETHODIMP CScreenSave::isEnabled(VARIANT_BOOL* enabled) {
	*enabled = convert(g_configuration.getScreenSave()->isEnabled());
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
