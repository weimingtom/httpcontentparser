#include "stdafx.h"
#include "./serviceUtility.h"

#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\comutility.h>
#include <utility\httprequestpacket.h>
#include <utility\debugmessage.h>
#include <utility\strutility.h>
#include <utility\seachpacket.h>
#include <typeconvert.h>
#include <string>
#include <comdef.h>
#include ".\hostnamerecorder.h"
using namespace std;

int	host_record_cnt = 0;
HostnameRecorder hostrecorder;

bool checkDNS(const char * dns_name) {

	// 每个三次记录一次
	if (3 == host_record_cnt) {
		host_record_cnt = 0;
		hostrecorder.add(std::string(dns_name));
	}

	host_record_cnt++;

	AutoInitInScale _auto_com_init;
	try {
		_VARIANT_BOOL passed;

		// create Instance
		IDNSSetting *dnsSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnsSetting);
		if (FAILED(hr)) {
			return FALSE;
		}

		VARIANT_BOOL enabled;
		dnsSetting->checkDNS(_bstr_t(dns_name), &enabled);
		SafeRelease(dnsSetting);

		return convert(enabled);
	} catch (_com_error &) {
		return false;
	}
}

bool checkSeachRule(HTTPRequestPacket* packet) {
	assert (NULL != packet);
	// 如果不是Search
	// 检测HTTP
	if (HTTPRequestPacket::HTTP_REQUEST_OPETYPE_GET != packet->getRequestType())
		return true;

	// 获取操作
	char host_name[HTTP_REQUEST_ITEM_MAX_LENGTH], 
		oper[HTTP_REQUEST_ITEM_MAX_LENGTH], 
		search_word[HTTP_REQUEST_ITEM_MAX_LENGTH];

	memset(host_name, 0, sizeof(host_name));
	memset(oper, 0, sizeof(oper));
	packet->getGET(oper, MAX_PATH);
	packet->getHost(host_name, HTTP_REQUEST_ITEM_MAX_LENGTH);
	
	if (strlen(host_name) == 0)
		return true;
	if (strlen(oper) == 0)
		return true;

	SeachPacket seach_packet;
	int result = seach_packet.parse(oper, host_name);
	if (0 == result) {
		return true;
	}

	seach_packet.get_seach_word(search_word, HTTP_REQUEST_ITEM_MAX_LENGTH);

	// 获取seach word

	// 送到服务器进行检测
	try {
		AutoInitInScale _auto_com_init;
		ISearchRule *seach_rule;
		HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
		if (FAILED(hr)) {
			return FALSE;
		}

		VARIANT_BOOL passed;
		seach_rule->check(_bstr_t(search_word), _bstr_t(host_name), &passed);
		SafeRelease(seach_rule);

		return convert(passed);
	} catch (_com_error&) {
		return false;
	}

	return true;
}

bool checkHTTPRequest(HTTPRequestPacket * packet) {
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};
	packet->getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	
	// 如果DNS不可达
	if (false == checkDNS(buffer)) 
		return false;

	// check search rule
	return checkSeachRule(packet);
}

bool accessNetword() {
	try {
		AutoInitInScale _auto_com_init;

		// 初始化
		IAccessNetwork *accessNetword = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER, IID_IAccessNetwork, (LPVOID*)&accessNetword);
		if (FAILED(hr)) {
			return FALSE;
		}

		VARIANT_BOOL varbool_accessable;
		accessNetword->accessNetwork(&varbool_accessable);
		return convert(varbool_accessable);
	} catch (_com_error &) {
		return false;
	}

}