// AppRegInfo.cpp : CAppRegInfo ��ʵ��

#include "stdafx.h"
#include "AppRegInfo.h"
#include <app_constants.h>
#include <typeconvert.h>
#include ".\globalvariable.h" 

// CAppRegInfo


//================================================
// ע����Ϣ
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
	// ����Ѿ�ע���򲻽����κβ���
	if (registered()) {
		*bSucc = VARIANT_TRUE;
		return S_OK;
	}

	// ���Խ���ע��
	*bSucc = convert(tryRegister((char*)_bstr_t(bstr)));
	if (VARIANT_TRUE == *bSucc) {
		// ���ע��ɹ�Ӧ�ò�ȡʲô����
		refreshAppstatus();
	}
	return S_OK;
}