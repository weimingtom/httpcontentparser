// GlobalChecker.cpp : CGlobalChecker µÄÊµÏÖ

#include "stdafx.h"
#include ".\globalchecker.h"
#include ".\globalvariable.h"
#include <string>
#include <comdef.h>
// CGlobalChecker

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

STDMETHODIMP CGlobalChecker::addBlackDNS(BSTR dns) {
	global_setting_.addBlackDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}

STDMETHODIMP CGlobalChecker::addWhiteDNS(BSTR dns) {
	global_setting_.adllWhiteDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}


STDMETHODIMP CGlobalChecker::removeBlackDNS(BSTR blackDNS) {
	global_setting_.removeBlackDNS(std::string((char*)_bstr_t(blackDNS)));
	return S_OK;
}

STDMETHODIMP CGlobalChecker::removeWhiteDNS(BSTR whiteDNS) {
	global_setting_.removeWhiteDNS(std::string((char*)_bstr_t(whiteDNS)));
	return S_OK;
}

// check DNS
STDMETHODIMP CGlobalChecker::enableDNSCheck(VARIANT_BOOL enable) {
	global_setting_.enableDNSCheck(enable);
	return S_OK;
}

STDMETHODIMP CGlobalChecker::checkDNS(BSTR dns, VARIANT_BOOL* enabled) {
	*enabled = global_setting_.checkDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}


// Image show
STDMETHODIMP CGlobalChecker::showImage(VARIANT_BOOL* showed) {
	*showed = global_setting_.showImage();
	return S_OK;
}


STDMETHODIMP CGlobalChecker::checkImage(int type, VARIANT_BOOL* checked) {
	*checked = global_setting_.imageNeedCheck(type);
	return S_OK;
}


STDMETHODIMP CGlobalChecker::enableImageCheck(int type, VARIANT_BOOL check) {
	global_setting_.enableImageCheck(type, check);
	return S_OK;
}

STDMETHODIMP CGlobalChecker::enableShowImage(VARIANT_BOOL show) {
	global_setting_.enableShowImage(show);
	return S_OK;
}

