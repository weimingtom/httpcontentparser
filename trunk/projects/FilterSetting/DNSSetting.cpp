// DNSSetting.cpp : CDNSSetting 的实现

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
	g_configuration.getDNSSetting()->addBlackDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}

STDMETHODIMP CDNSSetting::addWhiteDNS(BSTR dns) {
	g_configuration.getDNSSetting()->addWhiteDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}


STDMETHODIMP CDNSSetting::removeBlackDNS(BSTR blackDNS) {
	g_configuration.getDNSSetting()->removeBlackDNS(std::string((char*)_bstr_t(blackDNS)));
	return S_OK;
}

STDMETHODIMP CDNSSetting::removeWhiteDNS(BSTR whiteDNS) {
	g_configuration.getDNSSetting()->removeWhiteDNS(std::string((char*)_bstr_t(whiteDNS)));
	return S_OK;
}

// check DNS
STDMETHODIMP CDNSSetting::enableWhiteDNSCheck(VARIANT_BOOL enable) {
	g_configuration.getDNSSetting()->enableWhiteDNSCheck(convert(enable));
	return S_OK;
}

STDMETHODIMP CDNSSetting::enableBlackDNSCheck(VARIANT_BOOL enable) {
	g_configuration.getDNSSetting()->enableBlackDNSCheck(convert(enable));
	return S_OK;
}
STDMETHODIMP CDNSSetting::checkDNS(BSTR dns_name, VARIANT_BOOL* passed) {
	*passed = convert(g_configuration.getDNSSetting()->checkDNS((char*)_bstr_t(dns_name)));
	return S_OK;
}

STDMETHODIMP CDNSSetting::justEnableWhiteDNS(VARIANT_BOOL enabled) {
	g_configuration.getDNSSetting()->justPassWhiteDNS(convert(enabled));
	return S_OK;
}

// 检测是否是白名单
STDMETHODIMP CDNSSetting::isWhiteDNS(BSTR dns, VARIANT_BOOL* White)
{
	return S_OK;
}
