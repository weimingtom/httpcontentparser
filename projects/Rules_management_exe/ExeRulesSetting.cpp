// ExeRulesSetting.cpp : CExeRulesSetting µÄÊµÏÖ
 
#include "stdafx.h"
#include "ExeRulesSetting.h"
#include "globaldata.h"


extern CGlobalData g_globalData;
// CExeRulesSetting

 
STDMETHODIMP CExeRulesSetting::initialize(void) {
	return S_OK;
}

STDMETHODIMP CExeRulesSetting::addFiltederDNS(BSTR dns) {
	g_globalData.addDns(dns);
	return S_OK;
} 


STDMETHODIMP CExeRulesSetting::removeFilteredDNS(BSTR dns) {
	g_globalData.removeDns(dns);
	return S_OK;
}

STDMETHODIMP CExeRulesSetting::enableIpCheck(VARIANT_BOOL enable) {
	g_globalData.setIPCheck(enable);
	return S_OK;
}
