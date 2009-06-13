// SnowmanSetting.cpp : CSnowmanSetting ��ʵ��

#include "stdafx.h"
#include "SnowmanSetting.h"
#include ".\globalvariable.h"
#include ".\ServThread.h"
#include <typeconvert.h>
#include <apputility.h>
#include <utility\strutility.h>
#include <utility\dns.h>
#include <searchengine_define.h>
#include <softwareStatus.h>
#include <comutil.h>
#include ".\snowmansetting.h"
#include ".\logger_def.h"

// CSnowmanSetting
STDMETHODIMP CSnowmanSetting::setHotkey(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type, VARIANT_BOOL* bSuccess) {
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
STDMETHODIMP CSnowmanSetting::GetInstallPath(BSTR* installpath) {
	TCHAR path[MAX_PATH];
	::GetInstallPath(path, MAX_PATH);
	*installpath = bstr_t(path);
	return S_OK;
}


STDMETHODIMP CSnowmanSetting::switchModel(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc) {

	if (VARIANT_TRUE == bParent) {
		// �л����ҳ�ģʽ��Ҫ��֤����
		if (true == g_configuration.getAuthorize()->checkPassword((TCHAR*)_bstr_t(pwd), PASSWORD_SU)) {
			SettingItem::setModel(SettingItem::MODE_PARENT);
			*bSucc = VARIANT_TRUE;

			// ���һ�ҪֹͣEyecare �ļ�����
			g_configuration.getEyecareSetting()->stopTimer();
			LOGGER_WRITE(FILTERSETTING_LOGGER, "succeed in swithing to parent model");
		} else {
			// ��֤����ʧ��
			*bSucc = VARIANT_FALSE;
			LOGGER_WRITE(FILTERSETTING_LOGGER, "failed in swithing to parent model");
		}
	} else {
		LOGGER_WRITE(FILTERSETTING_LOGGER, "Try to swith to children model");
		// ����л�������ģʽ������Ҫ����
		SettingItem::setModel(SettingItem::MODE_CHILD);
		*bSucc = VARIANT_TRUE;

		if (g_configuration.getEyecareSetting()->isEnabled() && g_configuration.getEyecareSetting()->isTimerStopped()) {
			g_configuration.getEyecareSetting()->restartTimer();
		}
	}
	return S_OK;
}

// ��ǰģʽ�Ƿ��Ǽҳ�ģʽ
STDMETHODIMP CSnowmanSetting::get_ParentModel(VARIANT_BOOL* pVal) {
	if (SettingItem::MODE_PARENT == SettingItem::getModel()) {
		*pVal = VARIANT_TRUE;
	} else {
		*pVal = VARIANT_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::setTimeoutValue(LONG seconds)
{
	g_configuration.getTimeoutSwitch()->setTimeoutValue(seconds);
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::get_TimeoutSwitchEnabled(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getTimeoutSwitch()->isEnabled());
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::put_TimeoutSwitchEnabled(VARIANT_BOOL newVal)
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
STDMETHODIMP CSnowmanSetting::get_LefttimeToSwitch(LONG* pVal)
{
	*pVal = (LONG)g_configuration.getTimeoutSwitch()->getLeftTime();
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::getImageFolder(BSTR* path)
{
	TCHAR buffer[MAX_PATH];
	GetImageDirectory(buffer, MAX_PATH);
	*path = (BSTR)_bstr_t(buffer);
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::getPagesFolder(BSTR* path)
{
	TCHAR buffer[MAX_PATH];
	GetPageDirectory(buffer, MAX_PATH);
	*path = (BSTR)_bstr_t(buffer);
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::getHotkey(LONG type, USHORT* wVirtualKeyCode, USHORT* wModifier)
{
	DWORD hotkey = g_configuration.getHotkey()->getHotkey(getHotkeyname(type));
	 *wVirtualKeyCode = HIWORD(hotkey);
	*wModifier = LOWORD(hotkey);
	return S_OK;
}

//====================
// �رնԻ������Ƿ��Զ�ת��ģʽ
STDMETHODIMP CSnowmanSetting::get_autoSwitchOnClose(VARIANT_BOOL* pVal) {
	*pVal = convert(g_configuration.getMiscSetting()->switchChildrenOnClose());
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::put_autoSwitchOnClose(VARIANT_BOOL newVal) {
	g_configuration.getMiscSetting()->switchChildrenOnClose(convert(newVal));
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::get_askMeAgain(VARIANT_BOOL* pVal) {
	*pVal = convert(g_configuration.getMiscSetting()->askMeAgain_SwitchChildren());
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::put_askMeAgain(VARIANT_BOOL newVal) {
	g_configuration.getMiscSetting()->askMeAgain_SwitchChildren(convert(newVal));
	return S_OK;
}


STDMETHODIMP CSnowmanSetting::getApplicationStatus(LONG* status)
{
	*status = getAppStatus();
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::setApplicationStatus(LONG status)
{
	if ( SNOWMAN_STATUS_UNINSTALL== status) {
		g_configuration.setUninstall(true);
	}
	return S_OK;
}

STDMETHODIMP CSnowmanSetting::CheckPwd(BSTR password, VARIANT_BOOL* bSucc)
{
	if (true == g_configuration.getAuthorize()->checkPassword((TCHAR*)_bstr_t(password), PASSWORD_SU)) {
			SettingItem::setModel(SettingItem::MODE_PARENT);
		*bSucc = VARIANT_TRUE;
	} else {
		*bSucc = VARIANT_FALSE;
	}
	return S_OK;
}
