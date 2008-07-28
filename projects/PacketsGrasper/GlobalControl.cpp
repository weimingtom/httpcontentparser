#include "stdafx.h"
#include ".\globalcontrol.h"
#include <comdef.h>
#include <utility\HTTPPacket.h>
#include <com\filtersetting.h>
#include <com\filtersetting_i.c>

// class COMinititalize
// ����ʹCOM��һ��������Χ�ڽ����Զ�����
class COMinititalize {
public:
	COMinititalize() {CoInitialize(NULL);}
	~COMinititalize() {CoUninitialize();}
};


//===============================
// ��̬��Ա
GlobalControl * GlobalControl::pInstance_ = NULL;
GlobalControl * GlobalControl::getInstance() {
	static GlobalControl inst;
	return &inst;
}

//=================================
// ���켰��������
GlobalControl::GlobalControl(void) {
	update_ = false;
}

GlobalControl::~GlobalControl(void) {
}

// ��ʼ��
void GlobalControl::Update() {
	if (update_ == true) {
		return ;
	}

	update_ = true;
}

bool GlobalControl::checkHTTPHeader(HTTP_RESPONSE_HEADER *header) {
	try {
		IGlobalSetting *g_globalChecker;

		CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(CLSID_GlobalSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalSetting, (LPVOID*)&g_globalChecker);
		if (FAILED(hr)) {
			return false;
		}

		CoUninitialize();

	} catch (_com_error &e) {
		CoUninitialize();
	}
	return true;
}

bool GlobalControl::checkHTTPContent(HTTPPacket *packet) {
	try {
		IGlobalChecker *g_globalChecker;

		CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(CLSID_GlobalChecker, NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalChecker, (LPVOID*)&g_globalChecker);
		if (FAILED(hr)) {
			return false;
		}

		CoUninitialize();
	} catch (_com_error &e) {
		CoUninitialize();
	}
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
		CoUninitialize();
	}
	return true;
}