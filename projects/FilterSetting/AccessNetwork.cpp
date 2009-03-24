// AccessNetwork.cpp : CAccessNetwork 的实现

#include "stdafx.h"
#include ".\AccessNetwork.h"
#include ".\globalvariable.h"
#include <stdio.h>
#include <time.h>
#include <typeconvert.h>

// CAccessNetwork

STDMETHODIMP CAccessNetwork::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAccessNetwork
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAccessNetwork::accessNetwork(VARIANT_BOOL* bAccessable)
{
	// 获取当前时间
	time_t t;
	time(&t);
	struct tm * local= localtime(&t);
	bool accessable = g_configuration.getOnlineSetting()->getHour(local->tm_wday, local->tm_hour);
	*bAccessable = convert(accessable);
	return S_OK;
}

STDMETHODIMP CAccessNetwork::setBlockTime(LONG day, LONG hour)
{
	g_configuration.getOnlineSetting()->setHour(day, hour, false);
	return S_OK;
}

STDMETHODIMP CAccessNetwork::removeBlockTime(LONG day, LONG hour)
{
	g_configuration.getOnlineSetting()->setHour(day, hour, true);
	return S_OK;
}

STDMETHODIMP CAccessNetwork::SettingAccessNetwork(LONG day, LONG hour, VARIANT_BOOL* accessable)
{
	*accessable = g_configuration.getOnlineSetting()->getSettingHour(day, hour);
	return S_OK;
}

STDMETHODIMP CAccessNetwork::isSettingEnable(VARIANT_BOOL* enabled)
{
	*enabled = convert(g_configuration.getOnlineSetting()->isSettingEnabled());
	return S_OK;
}
