// AppLaunchFilter.cpp : CAppLaunchFilter ��ʵ��

#include "stdafx.h"
#include "AppLaunchFilter.h"
#include <DebugOutput.h>
#include ".\globalvariable.h"

// CAppLaunchFilter



STDMETHODIMP CAppLaunchFilter::Execute(LPSHELLEXECUTEINFO  pei) {
	if (checkApppath((TCHAR*)_bstr_t(pei->lpFile))) {
		return S_OK; 
	} else {
		return S_FALSE;
	}
}
