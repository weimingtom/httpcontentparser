// AppSetting.cpp : CAppSetting ��ʵ��

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
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}

STDMETHODIMP CAppSetting::setScreenSaverTimespan(LONG seconds)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}
