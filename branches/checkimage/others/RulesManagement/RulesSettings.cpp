// RulesSettings.cpp : CRulesSettings µÄÊµÏÖ

#include "stdafx.h"
#include "RulesSettings.h"
#include ".\rulessettings.h"
#include "globaldata.h"

extern CGlobalData g_globalData;
// CRulesSettings

STDMETHODIMP CRulesSettings::InterfaceSupportsErrorInfo(REFIID riid) {
	static const IID* arr[] =  	{
		&IID_IRulesSettings
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRulesSettings::initialize(void) {
	return S_OK;
}

STDMETHODIMP CRulesSettings::addFiltederDNS(BSTR dns) {
	g_globalData.addDns(dns);
	return S_OK;
}


STDMETHODIMP CRulesSettings::removeFilteredDNS(BSTR dns) {
	g_globalData.removeDns(dns);
	return S_OK;
}

STDMETHODIMP CRulesSettings::enableIpCheck(VARIANT_BOOL enable) {
	g_globalData.setIPCheck(enable);
	return S_OK;
}
