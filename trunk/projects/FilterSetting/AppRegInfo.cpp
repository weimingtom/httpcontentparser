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
	*pVal  = getInstallDays();
	return S_OK;
}

STDMETHODIMP CAppRegInfo::get_LeftDays(LONG* pVal)
{
	*pVal = REG_SOFTWARE_TRAIL_DAYES - getInstallDays();
	return S_OK;
}

STDMETHODIMP CAppRegInfo::Registered(VARIANT_BOOL* registeded) {
	*registeded = convert(registered());
	return S_OK;
}

STDMETHODIMP CAppRegInfo::Register(BSTR bstr, VARIANT_BOOL* bSucc)
{
	// 如果已经注册则不进行任何操作
	if (registered()) {
		*bSucc = VARIANT_TRUE;
		return S_OK;
	}

	// 尝试进行注册
	*bSucc = convert(tryRegister((char*)_bstr_t(bstr)));
	if (VARIANT_TRUE == *bSucc) {
		// 如果注册成功应该采取什么动作
		refreshAppstatus();
	}
	return S_OK;
}