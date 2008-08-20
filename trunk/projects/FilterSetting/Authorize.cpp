// Authorize.cpp : CAuthorize µÄÊµÏÖ

#include "stdafx.h"
#include "Authorize.h"


// CAuthorize

STDMETHODIMP CAuthorize::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAuthorize
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
