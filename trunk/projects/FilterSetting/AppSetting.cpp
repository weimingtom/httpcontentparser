// AppSetting.cpp : CAppSetting 的实现

#include "stdafx.h"
#include "AppSetting.h"
#include ".\appsetting.h"


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

STDMETHODIMP CAppSetting::setHotkey(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

STDMETHODIMP CAppSetting::setScreenSaverTimespan(LONG seconds)
{
	// TODO: 在此添加实现代码

	return S_OK;
}
