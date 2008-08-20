#include "stdafx.h"
#include "checkurl.h"

#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <string>
#include <comdef.h>
using namespace std;

bool checkIP(const std::string &ipAddress) {
	try {
		CoInitialize(NULL);
		_VARIANT_BOOL passed;

		// create Instance
		IGlobalChecker *globalChecker = NULL;
		HRESULT hr = CoCreateInstance(CLSID_GlobalChecker, NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalChecker, (LPVOID*)&globalChecker);
		if (FAILED(hr)) {
			AfxMessageBox("初始化系统服务失败..");
			return FALSE;
		}

		VARIANT_BOOL enabled;
		globalChecker->checkIP(_bstr_t(ipAddress.c_str()), &enabled);
		globalChecker->Release();
		CoUninitialize();

		char buffer[1024];
		sprintf(buffer, "check ip %s %s", ipAddress.c_str(), enabled==true? "true" : "false");
		OutputDebugString(buffer);

		return enabled;
	} catch (_com_error &) {
		return false;
	}
}