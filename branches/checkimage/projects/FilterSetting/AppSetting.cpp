// AppSetting.cpp : CAppSetting ��ʵ��

#include "stdafx.h"
#include ".\AppSetting.h"
#include ".\appsetting.h"
#include ".\servthread.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <typeconvert.h>
#include <sysutility.h>
#include <assert.h>
#include <comdef.h>


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
	BOOL bSucc = (int)ServThread::getInstance()->setHotKey(wVirtualKeyCode, wModifiers, type);
	*bSuccess = convert(bSucc);

	if (type == HOTKEY_LANUCH_MAINUI && FALSE == bSucc) {
		// ��������������ʧ��
		return S_OK;
	} else {
		g_configuration.getHotkey()->setHotkey(getHotkeyname(type), (unsigned)MAKELPARAM(wModifiers,wVirtualKeyCode));
	}

	*bSuccess = VARIANT_TRUE;
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

			// ���һ�ҪֹͣEyecare �ļ�����
			g_configuration.getEyecareSetting()->stopTimer();

			// ����TIMEOUT SWITCH ����
			g_configuration.getTimeoutSwitch()->startTimer();
		} else {
			// ��֤����ʧ��
			*bSucc = VARIANT_FALSE;
		}
	} else {
		// ����л�������ģʽ������Ҫ����
		SettingItem::setModel(SettingItem::MODE_CHILD);
		*bSucc = VARIANT_TRUE;

		if (true == g_configuration.getEyecareSetting()->isTimerStopped()) {
			g_configuration.getEyecareSetting()->restartTimer();
		}
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

STDMETHODIMP CAppSetting::setTimeoutValue(LONG seconds)
{
	g_configuration.getTimeoutSwitch()->setTimeoutValue(seconds);
	return S_OK;
}

STDMETHODIMP CAppSetting::get_TimeoutSwitchEnabled(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getTimeoutSwitch()->isEnabled());
	return S_OK;
}

STDMETHODIMP CAppSetting::put_TimeoutSwitchEnabled(VARIANT_BOOL newVal)
{
	g_configuration.getTimeoutSwitch()->enable(convert(newVal));
	bool a = convert(newVal);
	// �����ǰ������PARENT_MODE, ����
	if (SettingItem::MODE_PARENT == SettingItem::getModel()) {
		// �˺������Զ�ȷ�Ϲ����Ƿ����
		g_configuration.getTimeoutSwitch()->startTimer();
	}
	return S_OK;
}

// ��ȡ�����л�״̬��ʱ��
STDMETHODIMP CAppSetting::get_LefttimeToSwitch(LONG* pVal)
{
	*pVal = (LONG)g_configuration.getTimeoutSwitch()->getLeftTime();
	return S_OK;
}