// ScreenSave.cpp : CScreenSave 的实现

#include "stdafx.h"
#include ".\screensave.h"
#include "globalvariable.h"
#include <sysutility.h>
#include ".\utility.h"

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
	g_screenSaver.enableSave(convert(enabled));
	return S_OK;
}

STDMETHODIMP CScreenSave::setTimeSpan(LONG seconds) {
	g_screenSaver.setTimeSpan(seconds);
	return S_OK;
}

STDMETHODIMP CScreenSave::isEnabled(VARIANT_BOOL* enabled) {
	*enabled = g_screenSaver.isEnabled();
	return S_OK;
}

STDMETHODIMP CScreenSave::ClearCache(void) {
	ClearScreen(g_hInstance);
	return S_OK;
}

STDMETHODIMP CScreenSave::setAutoClearTimespan(LONG seconds)
{
	// TODO: 在此添加实现代码

	return S_OK;
}
