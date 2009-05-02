// AppRegInfo.cpp : CAppRegInfo 的实现

#include "stdafx.h"
#include "AppRegInfo.h"
#include <app_constants.h>
#include <typeconvert.h>
#include ".\globalvariable.h"

// CAppRegInfo


//================================================
// 注册信息
STDMETHODIMP CAppRegInfo::get_InstallDays(LONG* pVal)
{
	*pVal  = g_licenseInfo.getInstallDays();
	return S_OK;
}

STDMETHODIMP CAppRegInfo::get_LeftDays(LONG* pVal)
{
	*pVal = REG_SOFTWARE_TRAIL_DAYES - g_licenseInfo.getInstallDays();
	return S_OK;
}

STDMETHODIMP CAppRegInfo::Registered(VARIANT_BOOL* registeded) {
	*registeded = convert(g_licenseInfo.registered());
	return S_OK;
}

STDMETHODIMP CAppRegInfo::Register(BSTR bstr, VARIANT_BOOL* bSucc)
{
	return S_OK;
}