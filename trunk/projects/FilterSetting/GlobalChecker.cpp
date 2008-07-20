// GlobalChecker.cpp : CGlobalChecker 的实现

#include "stdafx.h"
#include "GlobalChecker.h"
#include ".\globalchecker.h"


// CGlobalChecker

STDMETHODIMP CGlobalChecker::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGlobalChecker
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CGlobalChecker::addBlackDNS(BSTR dns)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CGlobalChecker::addWhiteDNS(BSTR dns)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CGlobalChecker::enableDNSCheck(VARIANT_BOOL enable)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CGlobalChecker::removeBlackDNS(BSTR blackDNS)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CGlobalChecker::removeWhiteDNS(BSTR whiteDNS)
{
	// TODO: 在此添加实现代码

	return S_OK;
}
