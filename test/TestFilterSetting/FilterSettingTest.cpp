#include "StdAfx.h"
#include ".\filtersettingtest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>
#include <typeconvert.h>

bool checkDNS(const char *dns_name) {
	try {
		CoInitialize(NULL);
		_VARIANT_BOOL passed;

		// create Instance
		IDNSSetting *dnssetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnssetting);
		if (FAILED(hr)) {
			return FALSE;
		}

		VARIANT_BOOL enabled;
		dnssetting->justEnableWhiteDNS(VARIANT_FALSE);
		dnssetting->checkDNS(_bstr_t(dns_name), &enabled);
		dnssetting->Release();
		CoUninitialize();

		return convert(enabled);
	} catch (_com_error &) {
		return false;
	}
}

void FilterSettingTest::TestPassedWhiteDNS() {
	CoInitialize(NULL);
	IDNSSetting *dnssetting = NULL;
	HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnssetting);
	if (FAILED(hr)) {
		CPPUNIT_ASSERT(false);
	}

	VARIANT_BOOL passed;
	_bstr_t black_dns("sina.com");
	_bstr_t white_dns("google.com");
	_bstr_t none_relate("csdn.net");
	dnssetting->addBlackDNS(black_dns);
	dnssetting->addWhiteDNS(white_dns);

	dnssetting->enableBlackDNSCheck(VARIANT_TRUE);
	dnssetting->enableWhiteDNSCheck(VARIANT_TRUE);
	dnssetting->justEnableWhiteDNS(VARIANT_FALSE);
	
	dnssetting->checkDNS(black_dns, &passed);
	CPPUNIT_ASSERT(false == convert(passed));
	dnssetting->checkDNS(white_dns, &passed);
	CPPUNIT_ASSERT(true == convert(passed));
	dnssetting->checkDNS(none_relate, &passed);
	CPPUNIT_ASSERT(true == convert(passed));

	// 启用仅通过WHITE DNS
	dnssetting->enableBlackDNSCheck(VARIANT_TRUE);
	dnssetting->enableWhiteDNSCheck(VARIANT_TRUE);
	dnssetting->justEnableWhiteDNS(VARIANT_TRUE);
	
	dnssetting->checkDNS(black_dns, &passed);
	CPPUNIT_ASSERT(false == convert(passed));
	dnssetting->checkDNS(white_dns, &passed);
	CPPUNIT_ASSERT(true == convert(passed));
	dnssetting->checkDNS(none_relate, &passed);
	CPPUNIT_ASSERT(false == convert(passed));

	// 当关闭白名单时，JUST PASSED 也将关闭
	dnssetting->enableWhiteDNSCheck(VARIANT_FALSE);
	dnssetting->checkDNS(black_dns, &passed);
	CPPUNIT_ASSERT(false == convert(passed));
	dnssetting->checkDNS(white_dns, &passed);
	CPPUNIT_ASSERT(true == convert(passed));
	dnssetting->checkDNS(none_relate, &passed);
	CPPUNIT_ASSERT(true == convert(passed));


	CoUninitialize();
}
void FilterSettingTest::TestEnableWhiteAndPassWhite() {

}

void FilterSettingTest::TestcheckDNS() {
	CoInitialize(NULL);
	IDNSSetting *dnssetting = NULL;
	HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnssetting);
	if (FAILED(hr)) {
		CPPUNIT_ASSERT(false);
	}
	
	dnssetting->justEnableWhiteDNS(VARIANT_FALSE);
	dnssetting->enableBlackDNSCheck(VARIANT_TRUE);
	dnssetting->enableWhiteDNSCheck(VARIANT_TRUE);
	dnssetting->addBlackDNS(_bstr_t("sina.com"));
	bool passed  = checkDNS("news.sina.com");
	CPPUNIT_ASSERT(passed == false);

	dnssetting->enableBlackDNSCheck(VARIANT_TRUE);
	dnssetting->enableWhiteDNSCheck(VARIANT_TRUE);
	passed  = checkDNS("p1.sina.com");
	CPPUNIT_ASSERT(passed == false);

	dnssetting->Release();
	CoUninitialize();
}

void FilterSettingTest::TestaddBlackDNS() {
	CoInitialize(NULL);
	IDNSSetting *dnssetting = NULL;
	HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnssetting);
	if (FAILED(hr)) {
		CPPUNIT_ASSERT(false);
	}

	dnssetting->justEnableWhiteDNS(VARIANT_FALSE);
	dnssetting->enableBlackDNSCheck(VARIANT_TRUE);
	dnssetting->enableWhiteDNSCheck(VARIANT_TRUE);
	dnssetting->addBlackDNS(_bstr_t("sina.com"));
	bool passed  = checkDNS("sina.com");
	CPPUNIT_ASSERT(passed == false);

	dnssetting->enableBlackDNSCheck(VARIANT_TRUE);
	dnssetting->enableWhiteDNSCheck(VARIANT_TRUE);
	passed  = checkDNS("sina.com");
	CPPUNIT_ASSERT(passed == false);

	dnssetting->Release();
	CoUninitialize();
}


//==============================
// constructor and deconstructors
FilterSettingTest::FilterSettingTest(void) {
}

FilterSettingTest::~FilterSettingTest(void) {
}


//===========================
// virtual 
void FilterSettingTest::setUp() {
}
void FilterSettingTest::tearDown() {
}