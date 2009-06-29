// AppLaunchFilter.cpp : CAppLaunchFilter µÄÊµÏÖ

#include "stdafx.h"
#include "AppLaunchFilter.h"
#include <DebugOutput.h>
#include ".\globalvariable.h"

// CAppLaunchFilter



STDMETHODIMP CAppLaunchFilter::Execute(LPSHELLEXECUTEINFO  pei) {
	_DEBUG_STREAM_TRC_("[Family007 Services] CAppLaunchFilter::Execute : " <<	(TCHAR*)_bstr_t(pei->lpFile));
	if (checkApppath((TCHAR*)_bstr_t(pei->lpFile))) {
		return S_OK; 
	} else {
		return S_FALSE;
	}
}
