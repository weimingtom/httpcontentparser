// AppSetting.cpp : CAppSetting 的实现

#include "stdafx.h"
#include ".\AppSetting.h"
#include ".\appsetting.h"
#include ".\servthread.h"
#include ".\globalvariable.h"
#include <hotkey.h>
#include <assert.h>
#include <comdef.h>

namespace {
	const TCHAR* GetFileNameDir(TCHAR *filename, TCHAR *directory, const unsigned len) {
		TCHAR dir[MAX_PATH], driver[MAX_PATH];
		_tsplitpath(filename, driver, dir, NULL, NULL);
		_sntprintf(directory, len, TEXT("%s\\%s"), driver, dir);
		return directory;
	}
};

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

STDMETHODIMP CAppSetting::setScreenSaverTimespan(LONG seconds) {
	return S_OK;
}

STDMETHODIMP CAppSetting::GetInstallPath(BSTR* installpath) {
	// 获取当前路径
	TCHAR filename[MAX_PATH], path[MAX_PATH];
	GetModuleFileName(g_hInstance, filename, MAX_PATH);
	GetFileNameDir(filename, path, MAX_PATH);

	*installpath = bstr_t(path);
	return S_OK;
}
