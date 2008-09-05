#include "StdAfx.h"
#include ".\filtersettingtest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>

bool checkDNS(const std::string &ipAddress) {
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
		dnssetting->checkDNS(_bstr_t(ipAddress.c_str()), &enabled);
		dnssetting->Release();
		CoUninitialize();

		return enabled;
	} catch (_com_error &) {
		return false;
	}
}

void FilterSettingTest::addBlackDNS() {
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