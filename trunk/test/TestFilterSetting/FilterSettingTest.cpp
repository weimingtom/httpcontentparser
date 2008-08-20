#include "StdAfx.h"
#include ".\filtersettingtest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>

bool checkIP(const std::string &ipAddress) {
	try {
		CoInitialize(NULL);
		_VARIANT_BOOL passed;

		// create Instance
		IGlobalChecker *globalChecker = NULL;
		HRESULT hr = CoCreateInstance(CLSID_GlobalChecker, NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalChecker, (LPVOID*)&globalChecker);
		if (FAILED(hr)) {
			return FALSE;
		}

		VARIANT_BOOL enabled;
		globalChecker->checkIP(_bstr_t(ipAddress.c_str()), &enabled);
		globalChecker->Release();
		CoUninitialize();

		return enabled;
	} catch (_com_error &) {
		return false;
	}
}

void FilterSettingTest::addBlackDNS() {
	CoInitialize(NULL);
	IGlobalSetting *globalSetting = NULL;
	HRESULT hr = CoCreateInstance(CLSID_GlobalSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalSetting, (LPVOID*)&globalSetting);
	if (FAILED(hr)) {
		CPPUNIT_ASSERT(false);
	}

	globalSetting->enableDNSCheck(true);
	globalSetting->addBlackDNS(_bstr_t("www.sina.com"));
	bool passed  = checkIP("71.5.7.191");
	CPPUNIT_ASSERT(passed == false);

	globalSetting->enableDNSCheck(true);
	passed  = checkIP("71.5.7.191");
	CPPUNIT_ASSERT(passed == false);

	globalSetting->Release();
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