// Eyecare.cpp : CEyecare µÄÊµÏÖ

#include "stdafx.h"
#include "Eyecare.h"
#include ".\eyecare.h"


// CEyecare

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

STDMETHODIMP CEyecare::setPassword(BSTR password)
{
	return S_OK;
}

STDMETHODIMP CEyecare::setRestTime(void)
{
	return S_OK;
}

STDMETHODIMP CEyecare::setEntertainmentTime(LONG mintues)
{
	return S_OK;
}


STDMETHODIMP CEyecare::getRestTime(LONG* mintues)
{
	return S_OK;
}

STDMETHODIMP CEyecare::getEntertainmentTime(LONG* minutes)
{
	return S_OK;
}

STDMETHODIMP CEyecare::getTimeLeft(LONG* minutes)
{
	return S_OK;
}

STDMETHODIMP CEyecare::getState(LONG* state)
{
	return S_OK;
}

STDMETHODIMP CEyecare::swithToEntertainment(BSTR password)
{
	return S_OK;
}
