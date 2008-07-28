// GlobalSetting.cpp : CGlobalSetting µÄÊµÏÖ

#include "stdafx.h"
#include "GlobalSetting.h"
#include ".\globalvariable.h"
#include <comdef.h>
#include <utility\HTTPPacket.h>
#include ".\globalsetting.h"

// CGlobalSetting

STDMETHODIMP CGlobalSetting::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGlobalSetting
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CGlobalSetting::addBlackDNS(BSTR dns) {
	global_setting_.addBlackDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}

STDMETHODIMP CGlobalSetting::addWhiteDNS(BSTR dns) {
	global_setting_.adllWhiteDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}


STDMETHODIMP CGlobalSetting::removeBlackDNS(BSTR blackDNS) {
	global_setting_.removeBlackDNS(std::string((char*)_bstr_t(blackDNS)));
	return S_OK;
}

STDMETHODIMP CGlobalSetting::removeWhiteDNS(BSTR whiteDNS) {
	global_setting_.removeWhiteDNS(std::string((char*)_bstr_t(whiteDNS)));
	return S_OK;
}

// check DNS
STDMETHODIMP CGlobalSetting::enableDNSCheck(VARIANT_BOOL enable) {
	global_setting_.enableDNSCheck(enable);
	return S_OK;
}



// Image show
STDMETHODIMP CGlobalSetting::enableImageCheck(int type, VARIANT_BOOL check) {
	global_setting_.enableImageCheck(type, check);
	return S_OK;
}

STDMETHODIMP CGlobalSetting::enableShowImage(VARIANT_BOOL show) {
	global_setting_.enableShowImage(show);
	return S_OK;
}
