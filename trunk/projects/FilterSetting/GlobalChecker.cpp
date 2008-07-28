// GlobalChecker.cpp : CGlobalChecker µÄÊµÏÖ

#include "stdafx.h"
#include ".\globalchecker.h"
#include ".\globalvariable.h"
#include <string>
#include <comdef.h>
#include <utility\HTTPPacket.h>
// CGlobalChecker

namespace {
bool isImage(const int type) {
	if (type == HTTP_RESPONSE_HEADER::CONTYPE_GIF||
		type == HTTP_RESPONSE_HEADER::CONTYPE_JPG||
		type == HTTP_RESPONSE_HEADER::CONTYPE_PNG) {
		return true;
	} else {
		return false;
	}
}

bool isHTML(const int type) {
	return (type == HTTP_RESPONSE_HEADER::CONTYPE_HTML);
}
};
STDMETHODIMP CGlobalChecker::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = {
		&IID_IGlobalChecker
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CGlobalChecker::checkDNS(BSTR dns, VARIANT_BOOL* enabled) {
	*enabled = global_setting_.checkDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}

STDMETHODIMP CGlobalChecker::checkContent(LONG type, CHAR data[], LONG len, VARIANT_BOOL* passed) {
	if (isHTML(type) == true) {
	} else {
	}

	return S_OK;
}

STDMETHODIMP CGlobalChecker::needCheck(LONG type, VARIANT_BOOL* needed) {
	//global_setting_
	return S_OK;
}


STDMETHODIMP CGlobalChecker::checkImage(LONG type, LONG* action_code) {
	if (global_setting_->showImage() == false) {
		*action_code = 1;
	} else if (global_setting_->)
	return S_OK;
}
