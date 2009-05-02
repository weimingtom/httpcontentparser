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
	// ����Ѿ�ע���򲻽����κβ���
	if (g_licenseInfo.registered()) {
		*bSucc = VARIANT_TRUE;
		return S_OK;
	}

	// ���Խ���ע��
	*bSucc = convert(g_licenseInfo.regApp(std::string((char*)_bstr_t(bstr))));
	if (VARIANT_TRUE == *bSucc) {
		// ���ע��ɹ�Ӧ�ò�ȡʲô����
	}
	return S_OK;
}