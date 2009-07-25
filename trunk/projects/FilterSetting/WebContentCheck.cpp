// WebContentCheck.cpp : CWebContentCheck µÄÊµÏÖ

#include "stdafx.h"
#include "WebContentCheck.h"
#include "globalvariable.h"
#include <typeconvert.h>
#include <webcontenttype.h>
#include ".\webcontentcheck.h"

// CWebContentCheck

STDMETHODIMP CWebContentCheck::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWebContentCheck
	};

	for (INT_PTR i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// CImageCheck
STDMETHODIMP CWebContentCheck::shouldCheck(LONG type, VARIANT_BOOL* check)
{
	bool needcheck = g_configuration.getContentCheckSetting()->needCheck(type);

	*check = convert(needcheck);
	return S_OK;
}

STDMETHODIMP CWebContentCheck::getCheckScope(LONG* minSize, LONG *maxSize)
{
	g_configuration.getContentCheckSetting()->getCheckedScope(minSize, maxSize);
	return S_OK;
}
STDMETHODIMP CWebContentCheck::setCheckScope(LONG min, LONG max)
{
	g_configuration.getContentCheckSetting()->setCheckScope(min, max);
	return S_OK;
}

STDMETHODIMP CWebContentCheck::enableCheck(VARIANT_BOOL enabled, LONG type)
{
	g_configuration.getContentCheckSetting()->enableCheck(type, convert(enabled));
	return S_OK;
}

STDMETHODIMP CWebContentCheck::shouldCheckBySize(LONG size, VARIANT_BOOL* check)
{
	bool checked = g_configuration.getContentCheckSetting()->needCheckBySize(size);
	*check = convert(checked);
	return S_OK;
}

STDMETHODIMP CWebContentCheck::get_ImageCheckTightness(LONG* pVal)
{
	*pVal = g_configuration.getContentCheckSetting()->getImageCheckTightness();
	return S_OK;
}

STDMETHODIMP CWebContentCheck::put_ImageCheckTightness(LONG newVal)
{
	assert (newVal >= 0 && newVal < 5);
	g_configuration.getContentCheckSetting()->setImageCheckTightness(newVal);
	return S_OK;
}
