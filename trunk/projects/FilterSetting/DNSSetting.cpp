// DNSSetting.cpp : CDNSSetting µÄÊµÏÖ

#include "stdafx.h"
#include "DNSSetting.h"
#include ".\globalvariable.h"

#include <comdef.h>
#include <utility\HTTPPacket.h>
#include ".\dnssetting.h"
#include <typeconvert.h>

// CDNSSetting

STDMETHODIMP CDNSSetting::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDNSSetting
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDNSSetting::addBlackDNS(BSTR dns) {
	g_dnssetting.addBlackDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}

STDMETHODIMP CDNSSetting::addWhiteDNS(BSTR dns) {
	g_dnssetting.addWhiteDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}


STDMETHODIMP CDNSSetting::removeBlackDNS(BSTR blackDNS) {
	g_dnssetting.removeBlackDNS(std::string((char*)_bstr_t(blackDNS)));
	return S_OK;
}

STDMETHODIMP CDNSSetting::removeWhiteDNS(BSTR whiteDNS) {
	g_dnssetting.removeWhiteDNS(std::string((char*)_bstr_t(whiteDNS)));
	return S_OK;
}

// check DNS
STDMETHODIMP CDNSSetting::enableWhiteDNSCheck(VARIANT_BOOL enable) {
	g_dnssetting.enableWhiteDNSCheck(convert(enable));
	return S_OK;
}

STDMETHODIMP CDNSSetting::enableBlackDNSCheck(VARIANT_BOOL enable) {
	g_dnssetting.enableBlackDNSCheck(convert(enable));
	return S_OK;
}
STDMETHODIMP CDNSSetting::checkDNS(BSTR dns_name, VARIANT_BOOL* passed)
{
	*passed = g_dnssetting.fuzzeCheckDNS((char*)_bstr_t(dns_name));
	return S_OK;
}
