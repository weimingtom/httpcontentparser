#include "StdAfx.h"
#include ".\filtersettingtest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>

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
		dnssetting->checkDNS(_bstr_t(dns_name), &enabled);
		dnssetting->Release();
		CoUninitialize();

		return enabled;
	} catch (_com_error &) {
		return false;
	}
}

void FilterSettingTest::TestcheckDNS() {
	CoInitialize(NULL);
	IDNSSetting *dnssetting = NULL;
	HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnssetting);
	if (FAILED(hr)) {
		CPPUNIT_ASSERT(false);
	}

	dnssetting->enableBlackDNSCheck(true);
	dnssetting->enableWhiteDNSCheck(true);
	dnssetting->addBlackDNS(_bstr_t("sina.com"));
	bool passed  = checkDNS("news.sina.com");
	CPPUNIT_ASSERT(passed == false);

	dnssetting->enableBlackDNSCheck(true);
	dnssetting->enableWhiteDNSCheck(true);
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

	dnssetting->enableBlackDNSCheck(true);
	dnssetting->enableWhiteDNSCheck(true);
	dnssetting->addBlackDNS(_bstr_t("sina.com"));
	bool passed  = checkDNS("sina.com");
	CPPUNIT_ASSERT(passed == false);

	dnssetting->enableBlackDNSCheck(true);
	dnssetting->enableWhiteDNSCheck(true);
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