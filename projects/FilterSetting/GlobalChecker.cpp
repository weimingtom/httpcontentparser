// GlobalChecker.cpp : CGlobalChecker ��ʵ��

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
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}

STDMETHODIMP CGlobalChecker::addWhiteDNS(BSTR dns)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}

STDMETHODIMP CGlobalChecker::enableDNSCheck(VARIANT_BOOL enable)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}

STDMETHODIMP CGlobalChecker::removeBlackDNS(BSTR blackDNS)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}

STDMETHODIMP CGlobalChecker::removeWhiteDNS(BSTR whiteDNS)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}
