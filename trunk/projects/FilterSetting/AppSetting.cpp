// AppSetting.cpp : CAppSetting 的实现

#include "stdafx.h"
#include ".\AppSetting.h"
#include ".\appsetting.h"
#include ".\servthread.h"
#include ".\globalvariable.h"
#include ".\registerinfo.h"
#include <apputility.h>
#include <app_constants.h>
#include <typeconvert.h>
#include <apputility.h>
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
		// 设置启动主界面失败
		return S_OK;
	} else {
		g_configuration.getHotkey()->setHotkey(getHotkeyname(type), (unsigned)MAKELPARAM(wModifiers,wVirtualKeyCode));
	}

	*bSuccess = VARIANT_TRUE;
	return S_OK;
}

// 获取安装路径
STDMETHODIMP CAppSetting::GetInstallPath(BSTR* installpath) {
	TCHAR path[MAX_PATH];
	::GetInstallPath(path, MAX_PATH);
	*installpath = bstr_t(path);
	return S_OK;
}


STDMETHODIMP CAppSetting::switchModel(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc) {
	if (VARIANT_TRUE == bParent) {
		// 切换到家长模式需要验证密码
		if (true == g_configuration.getAuthorize()->checkPassword((TCHAR*)_bstr_t(pwd), PASSWORD_SU)) {
			SettingItem::setModel(SettingItem::MODE_PARENT);
			*bSucc = VARIANT_TRUE;

			// 而且还要停止Eyecare 的计数器
			g_configuration.getEyecareSetting()->stopTimer();
		} else {
			// 验证密码失败
			*bSucc = VARIANT_FALSE;
		}
	} else {
		// 如果切换到孩子模式，则不需要密码
		SettingItem::setModel(SettingItem::MODE_CHILD);
		*bSucc = VARIANT_TRUE;

		if (g_configuration.getEyecareSetting()->isEnabled() && g_configuration.getEyecareSetting()->isTimerStopped()) {
			g_configuration.getEyecareSetting()->restartTimer();
		}
	}
	return S_OK;
}

// 当前模式是否是家长模式
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
	// 如果当前正处于PARENT_MODE, 则开启
	if (SettingItem::MODE_PARENT == SettingItem::getModel()) {
		// 此函数会自动确认功能是否可用
		g_configuration.getTimeoutSwitch()->startTimer();
	}
	return S_OK;
}

// 获取距离切换状态的时间
STDMETHODIMP CAppSetting::get_LefttimeToSwitch(LONG* pVal)
{
	*pVal = (LONG)g_configuration.getTimeoutSwitch()->getLeftTime();
	return S_OK;
}

STDMETHODIMP CAppSetting::Registered(VARIANT_BOOL* registeded)
{
	return S_OK;
}

STDMETHODIMP CAppSetting::Register(BSTR bstr, VARIANT_BOOL* bSucc)
{
	return S_OK;
}

STDMETHODIMP CAppSetting::getImageFolder(BSTR* path)
{
	TCHAR buffer[MAX_PATH];
	GetImageDirectory(buffer, MAX_PATH);
	*path = (BSTR)_bstr_t(buffer);
	return S_OK;
}

STDMETHODIMP CAppSetting::getPagesFolder(BSTR* path)
{
	TCHAR buffer[MAX_PATH];
	GetPageDirectory(buffer, MAX_PATH);
	*path = (BSTR)_bstr_t(buffer);
	return S_OK;
}

STDMETHODIMP CAppSetting::getHotkey(LONG type, USHORT* wVirtualKeyCode, USHORT* wModifier)
{
	DWORD hotkey = g_configuration.getHotkey()->getHotkey(getHotkeyname(type));
	 *wVirtualKeyCode = HIWORD(hotkey);
	*wModifier = LOWORD(hotkey);
	return S_OK;
}
