// Authorize.cpp : CAuthorize 的实现

#include "stdafx.h"
#include "Authorize.h"
#include ".\authorize.h"
#include "globalvariable.h"
#include "passwordtype.h"

#include <typeconvert.h>
#include <comdef.h>
#include <string>
using namespace std;

// CAuthorize

STDMETHODIMP CAuthorize::InterfaceSupportsErrorInfo(REFIID riid) {
	static const IID* arr[] = {
		&IID_IAuthorize
	};

	for (INT_PTR i=0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


// 验证密码
STDMETHODIMP CAuthorize::checkPassword(BSTR password, VARIANT_BOOL* bSuccess) {
	*bSuccess = convert(g_configuration.getAuthorize()->checkPassword((char*)_bstr_t(password), PASSWORD_SU)); 
	return S_OK;
}

STDMETHODIMP CAuthorize::changePassword(BSTR password, BSTR oldPassword, VARIANT_BOOL* bSuccess)
{
	OutputDebugString(_T("change password ....."));
	*bSuccess = convert(g_configuration.getAuthorize()->setPassword((char*)_bstr_t(password),
		(char*)_bstr_t(oldPassword), PASSWORD_SU)); 
	return S_OK;
}

