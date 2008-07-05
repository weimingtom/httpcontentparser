// RulesSetting.cpp : CRulesSetting µÄÊµÏÖ

#include "stdafx.h"
#include "RulesSetting.h"
#include "globaldata.h"

extern CGlobalData g_globalData;
 
// CRulesSetting

STDMETHODIMP CRulesSetting::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRulesSetting
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

 
STDMETHODIMP CRulesSetting::initialize(void) {
	return S_OK;
}

STDMETHODIMP CRulesSetting::addFiltederDNS(BSTR dns) {
	g_globalData.addDns(dns);
	return S_OK;
} 


STDMETHODIMP CRulesSetting::removeFilteredDNS(BSTR dns) {
	g_globalData.removeDns(dns);
	return S_OK;
}

STDMETHODIMP CRulesSetting::enableIpCheck(VARIANT_BOOL enable) {
	g_globalData.setIPCheck(enable);
	return S_OK;
}