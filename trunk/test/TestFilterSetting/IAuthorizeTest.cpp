#include "StdAfx.h"
#include ".\iauthorizetest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <passwordtype.h>
#include <comdef.h>
#include <typeconvert.h>

IAuthorizeTest::IAuthorizeTest(void) {
}

IAuthorizeTest::~IAuthorizeTest(void) {
}


void IAuthorizeTest::testCheckPassword() {
	try {
		CoInitialize(NULL);
		_VARIANT_BOOL passed;

		// create Instance
		IAuthorize *authorize = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&authorize);
		if (FAILED(hr)) {
			CPPUNIT_ASSERT(false);
			return ;
		}
		
		VARIANT_BOOL corrected;
		_bstr_t last_password = "123";
		_bstr_t wrong_password = "8382";
		_bstr_t new_password = "234";
		authorize->checkPassword(last_password, &corrected);
		CPPUNIT_ASSERT(true == convert(corrected));

		authorize->checkPassword(wrong_password, &corrected);
		CPPUNIT_ASSERT(false == convert(corrected));

		authorize->checkPassword(new_password, &corrected);
		CPPUNIT_ASSERT(false == convert(corrected));


		authorize->changePassword(new_password, wrong_password, &corrected);
		CPPUNIT_ASSERT(false == convert(corrected));

		authorize->changePassword(new_password, last_password, &corrected);
		CPPUNIT_ASSERT(true == convert(corrected));
		
		authorize->Release();
		CoUninitialize();
	} catch (_com_error &) {
		return;
	}
}