// DNSSetting.cpp : CDNSSetting 的实现

#include "stdafx.h"

#include ".\globalvariable.h"
#include ".\dnssetting.h"
#include <app_constants.h>
#include <utility\HTTPPacket.h>
#include <typeconvert.h>

#include <string>
#include <comdef.h>

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
	_bstr_t bstrDNS(dns_name);
	LPCTSTR lpstrDNS = (LPCTSTR)bstrDNS;
	if (NULL != _tcsstr(lpstrDNS, HOME_WEBSITES)) {
		*passed = VARIANT_TRUE;
	}
	// 保存到访问网站的列表当中
	if (SettingItem::MODE_PARENT != SettingItem::getModel()) {
		g_websitesUtil.addWebsite(std::string(lpstrDNS));
	}

	*passed = convert(g_configuration.getDNSSetting()->checkDNS(lpstrDNS));
	
	// 发送消息
	if (VARIANT_FALSE  == *passed) {
		const int dns_max_length = 64;	// 如果DNS大于这个长度将被截断
		const int msg_buffer_size = 512;
		TCHAR msg_buffer[msg_buffer_size];
		TCHAR dns[dns_max_length] = {0};
		_tcsncpy(dns, lpstrDNS, dns_max_length-1);
		_sntprintf(msg_buffer, msg_buffer_size, "The Webpage \"%s\" is not accessable!", dns);
		NotifyUser(msg_buffer);
	}

	return S_OK;
}

STDMETHODIMP CDNSSetting::justEnableWhiteDNS(VARIANT_BOOL enabled) {
	g_configuration.getDNSSetting()->justPassWhiteDNS(convert(enabled));
	return S_OK;
}

// 检测是否是白名单
STDMETHODIMP CDNSSetting::isWhiteDNS(BSTR dns, VARIANT_BOOL* White)
{
	*White = convert(g_configuration.getDNSSetting()->inWhiteList((char*)_bstr_t(dns)));
	return S_OK;
}
STDMETHODIMP CDNSSetting::getFirstWhiteDNS(BSTR* dns)
{
	std::string str = g_configuration.getDNSSetting()->getFirstWhiteDNS();
	*dns = (BSTR)_bstr_t(str.c_str());
	return S_OK;
}

STDMETHODIMP CDNSSetting::getNextWhiteDNS(BSTR cur, BSTR* next)
{
	std::string str = g_configuration.getDNSSetting()->getNextWhiteDNS((TCHAR*)_bstr_t(cur));
	*next = (BSTR)_bstr_t(str.c_str());
	return S_OK;
}

STDMETHODIMP CDNSSetting::getFirstBlackDNS(BSTR* dns)
{
	std::string str = g_configuration.getDNSSetting()->getFirstBlackDNS();
	*dns = (BSTR)_bstr_t(str.c_str());
	return S_OK;
}

STDMETHODIMP CDNSSetting::getNextBlackDNS(BSTR cur, BSTR* next)
{
	std::string str = g_configuration.getDNSSetting()->getNextBlackDNS((TCHAR*)_bstr_t(cur));
	*next = (BSTR)_bstr_t(str.c_str());
	return S_OK;
}

STDMETHODIMP CDNSSetting::isWhiteDNSSettingEnable(VARIANT_BOOL *enabled)
{
	*enabled = convert(g_configuration.getDNSSetting()->isWhiteDNSSettingEnable());
	return S_OK;
}

STDMETHODIMP CDNSSetting::isBlackDNSSettingEnable(VARIANT_BOOL* enabled)
{
	*enabled = convert(g_configuration.getDNSSetting()->isBlackDNSSettingEnable());
	return S_OK;
}

STDMETHODIMP CDNSSetting::isJustEnableWhiteDNS(VARIANT_BOOL* enabled)
{
	*enabled = convert(g_configuration.getDNSSetting()->justPassWhiteDNS());
	return S_OK;
}
