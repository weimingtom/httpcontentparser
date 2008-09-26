#include "stdafx.h"
#include "CheckUtility.h"
#include "debug.h"

#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <utility\httprequestpacket.h>
#include <utility\debugmessage.h>
#include <typeconvert.h>
#include <string>
#include <comdef.h>
using namespace std;

#define DEFINE_FILE "c:\\dump.log"

bool checkDNS(const char * dns_name) {
	try {
		CoInitialize(NULL);
		_VARIANT_BOOL passed;

		// create Instance
		IDNSSetting *dnsSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnsSetting);
		if (FAILED(hr)) {
			AfxMessageBox("��ʼ��ϵͳ����ʧ��..");
			return FALSE;
		}

		VARIANT_BOOL enabled;
		dnsSetting->checkDNS(_bstr_t(dns_name), &enabled);
		dnsSetting->Release();
		CoUninitialize(); 

		return convert(enabled);
	} catch (_com_error &) {
		return false;
	}
}

bool checkHTTPRequest(WSABUF *buf, const int count) {
	DumpBuf(buf, count, DEFINE_FILE);
	OutputDebugString("checkHTTPRequest");

	HTTPRequestPacket packet;
	int item_count = packet.parsePacket(buf, count);

	// ���С��2����ô���Ͳ���һ��HTTP����
	if (item_count < 2) {	
		return true;
	}
	
	
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};
	packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	
	
	ODS2(" === HOST : ", buffer);
	return checkDNS(buffer);
}