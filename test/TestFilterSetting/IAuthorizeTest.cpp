#include "StdAfx.h"
#include ".\iauthorizetest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <passwordtype.h>
#include <comdef.h>
#include <typeconvert.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


void testCheckPassword() {
	try {
		CoInitialize(NULL);
		_VARIANT_BOOL passed;

		// create Instance
		IAuthorize *authorize = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&authorize);
		if (FAILED(hr)) {
			BOOST_ASSERT(false);
			return ;
		}
		
		VARIANT_BOOL corrected;
		_bstr_t last_password = DEFAULT_PASSWORD;
		_bstr_t wrong_password = "8382";
		_bstr_t new_password = "234";

		authorize->checkPassword(last_password, &corrected);
		BOOST_ASSERT(true == convert(corrected));

		authorize->checkPassword(wrong_password, &corrected);
		BOOST_ASSERT(false == convert(corrected));

		authorize->checkPassword(new_password, &corrected);
		BOOST_ASSERT(false == convert(corrected));


		authorize->changePassword(new_password, wrong_password, &corrected);
		BOOST_ASSERT(false == convert(corrected));

		authorize->changePassword(new_password, last_password, &corrected);
		BOOST_ASSERT(true == convert(corrected));

		// 改回默认密码，否则测试可能失败
		authorize->changePassword(_bstr_t(DEFAULT_PASSWORD), new_password, &corrected);
		BOOST_ASSERT(true == convert(corrected));
		
		authorize->Release();
		CoUninitialize();
	} catch (_com_error &) {
		return;
	}
}