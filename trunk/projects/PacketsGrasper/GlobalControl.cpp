#include "stdafx.h"
#include ".\globalcontrol.h"
#include <comdef.h>
#include <utility\HTTPPacket.h>
#include <com\filtersetting.h>
#include <com\filtersetting_i.c>

//===============================
// 静态成员
GlobalControl * GlobalControl::pInstance_ = NULL;
GlobalControl * GlobalControl::getInstance() {
	static GlobalControl inst;
	return &inst;
}

//=================================
// 构造及西沟函数
GlobalControl::GlobalControl(void) {
	update_ = false;
}

GlobalControl::~GlobalControl(void) {
}

// 初始化
void GlobalControl::Update() {
	if (update_ == true) {
		return ;
	}

	update_ = true;
}

bool GlobalControl::checkHTTPHeader(HTTP_RESPONSE_HEADER *header) {
	return true;
}

bool GlobalControl::checkHTTPContent(HTTPPacket *packet) {
	return true;
}

bool checkDNS(const std::string &dns_name) {
	try {
		IGlobalChecker *g_globalChecker;

		CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(CLSID_GlobalChecker, NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalChecker, (LPVOID*)&g_globalChecker);
		if (FAILED(hr)) {
			return false;
		}

		VARIANT_BOOL enable;
		g_globalChecker->checkDNS(_bstr_t(dns_name.c_str()), &enable);
		CoUninitialize();

		return enable;
	} catch (_com_error &e) {
	}
	return true;
}