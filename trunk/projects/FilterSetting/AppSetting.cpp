// AppSetting.cpp : CAppSetting ��ʵ��

#include "stdafx.h"
#include ".\AppSetting.h"
#include ".\appsetting.h"
#include ".\servthread.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <assert.h>
#include <comdef.h>
#include <sysutility.h>

// CAppSetting

STDMETHODIMP CAppSetting::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAppSetting
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAppSetting::setHotkey(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type, VARIANT_BOOL* bSuccess) {
	*bSuccess = ServThread::getInstance()->setHotKey(wVirtualKeyCode, wModifiers, type);
	return S_OK;
}

// ��ȡ��װ·��
STDMETHODIMP CAppSetting::GetInstallPath(BSTR* installpath) {
	TCHAR path[MAX_PATH];
	::GetInstallPath(path, MAX_PATH, g_hInstance);
	*installpath = bstr_t(path);
	return S_OK;
}


STDMETHODIMP CAppSetting::switchModel(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc) {
	if (VARIANT_TRUE == bParent) {
		// �л����ҳ�ģʽ��Ҫ��֤����
		if (true == g_configuration.getAuthorize()->checkPassword((TCHAR*)_bstr_t(pwd), PASSWORD_SU)) {
			SettingItem::setModel(SettingItem::MODE_PARENT);
			*bSucc = VARIANT_TRUE;
		} else {
			// ��֤����ʧ��
			*bSucc = VARIANT_FALSE;
		}
	} else {
		// ����л�������ģʽ������Ҫ����
		SettingItem::setModel(SettingItem::MODE_CHILD);
		*bSucc = VARIANT_TRUE;
	}
	return S_OK;
}

// ��ǰģʽ�Ƿ��Ǽҳ�ģʽ
STDMETHODIMP CAppSetting::get_ParentModel(VARIANT_BOOL* pVal) {
	if (SettingItem::MODE_PARENT == SettingItem::getModel()) {
		*pVal = VARIANT_TRUE;
	} else {
		*pVal = VARIANT_FALSE;
	}
	return S_OK;
}
