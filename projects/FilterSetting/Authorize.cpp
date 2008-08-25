// Authorize.cpp : CAuthorize ��ʵ��

#include "stdafx.h"
#include "Authorize.h"
#include ".\authorize.h"


// CAuthorize

STDMETHODIMP CAuthorize::InterfaceSupportsErrorInfo(REFIID riid) {
	static const IID* arr[] = {
		&IID_IAuthorize
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


// ��֤����
STDMETHODIMP CAuthorize::checkPassword(BSTR password, VARIANT_BOOL* bSuccess) {
	return S_OK;
}
