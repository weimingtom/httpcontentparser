#include "stdafx.h"
#include "CheckUtility.h"
#include "debug.h"

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
using namespace std;

// 检测规则
bool is_google_seach(const char *oper) {
	if (strstr(oper, "/search") == oper) {
		return true;
	} else { 
		return false;
	}
}
bool is_baidu_seach(const char *oper) {
	if (strstr(oper, "/s") == oper) {
		return true;
	} else {
		return false;
	}
}
bool is_yahoo_seach(const char *oper) {
	if (strstr(oper, "") == oper) {
		return true;
	} else {
		return false;
	}
}

int get_seach_word(char *seach_word, const int buf_size, const char * oper, const char *host_name) {
	using namespace strutility;
	if (NULL != strstr(TEXT("google.com"), host_name)) {
		return extract_string(seach_word, buf_size, oper, "&Q", "&", false);
	} else if (NULL != strstr(TEXT("yahoo.com"), host_name)) {
		return extract_string(seach_word, buf_size, oper, "&q=	", "&", false);
	} else if (NULL != strstr(TEXT("baidu.com"), host_name)) {
		return extract_string(seach_word, buf_size, oper, "&q=", "&", false);
	} else {
		return 0;
	}

	return strlen(seach_word);
}

// 判断是不是seach host
bool need_check_seach(const char * host_name, const char * oper) {
	if (NULL != strstr(TEXT("google.com"), host_name)) {
		return is_google_seach(oper);
	} else if (NULL != strstr(TEXT("yahoo.com"), host_name)) {
		return is_yahoo_seach(oper);
	} else if (NULL != strstr(TEXT("baidu.com"), host_name)) {
		return is_baidu_seach(oper);
	} else {
		// 如果不是这几个主机
		return false;
	}
}

bool checkDNS(const char * dns_name) {
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

// 检测HTTP
bool checkSeachRule(HTTPRequestPacket packet) {
	// 如果不是Search
	if (HTTPRequestPacket::HTTP_REQUEST_OPETYPE_GET != packet.getRequestType())
		return true;

	// 获取操作
	char host_name[HTTP_REQUEST_ITEM_MAX_LENGTH], 
		oper[HTTP_REQUEST_ITEM_MAX_LENGTH], 
		search_word[HTTP_REQUEST_ITEM_MAX_LENGTH];

	memset(host_name, 0, sizeof(host_name));
	memset(oper, 0, sizeof(oper));
	packet.getGET(oper, MAX_PATH);
	
	if (strlen(oper) == 0)
		return 0;

	SeachPacket seach_packet;
	seach_packet.parse(oper, host_name);
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

bool checkHTTPRequest(WSABUF *buf, const int count) {
	HTTPRequestPacket packet;
	int item_count = packet.parsePacket(buf, count);

	// 如果小于2，那么他就不是一个HTTP请求
	if (item_count < 2) {	
		return true;
	}
	
	
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};
	packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	
	// 如果DNS不可达
	if (false == checkDNS(buffer)) 
		return false;

	// check search rule
	return checkSeachRule(packet);
}

bool accessNetword() {
	static int cnt = 0;
	static bool accessable = false;

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
		accessable = convert(varbool_accessable);
	} catch (_com_error &) {
		return false;
	}

	return accessable;
}