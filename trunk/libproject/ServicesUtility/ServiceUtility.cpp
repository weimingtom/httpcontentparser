#include "stdafx.h"
#include "./serviceUtility.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\comutility.h>
#include <utility\httprequestpacket.h>
#include <utility\debugmessage.h>
#include <utility\strutility.h>
#include <utility\seachpacket.h>
#include <utility\dns.h>
#include <typeconvert.h>
#include <string>
#include <vector>
#include <comdef.h>
using namespace std;

namespace {
	void getSearchKeyword(char * keyword, char * hostname);
};

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

void extractSearchWord(const char * searchword, std::vector<std::string> * vecWords) {
	assert  (NULL != vecWords);
	if (NULL == vecWords)
		return;

	// ��ȡ�����ʻ�
	// ����ʹ��+���ֽ�
	std::vector<std::string> subwords;
	std::vector<std::string> keword;
	const char * specified_chars = "+";
	strutility::splitstring(searchword, specified_chars, vecWords);
}


bool checkSearchWord(const char * searchword, const char * hostname) {
	// �͵����������м��
	try {
		AutoInitInScale _auto_com_init;
		ISearchRule *seach_rule;
		HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
		if (FAILED(hr)) {
			return FALSE;
		}

		VARIANT_BOOL passed;
		seach_rule->check(_bstr_t(searchword), _bstr_t(hostname), &passed);
		SafeRelease(seach_rule);

		return convert(passed);
	} catch (_com_error&) {
		return false;
	}
}

bool checkSeachRule(HTTPRequestPacket* packet) {
	assert (NULL != packet);
	// �������Search
	// ���HTTP
	if (HTTPRequestPacket::HTTP_REQUEST_OPETYPE_GET != packet->getRequestType())
		return true;

	// ��ȡ����(������������)
	char host_name[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0},
		oper[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0}, 
		search_word[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};

	packet->getGET(oper, MAX_PATH);
	packet->getHost(host_name, HTTP_REQUEST_ITEM_MAX_LENGTH);
	
	if (strlen(host_name) == 0)
		return true;
	if (strlen(oper) == 0)
		return true;

	// ��ȡ�����ʻ�
	SeachPacket seach_packet;
	int result = seach_packet.parse(oper, host_name);
	if (0 == result) {
		return true;
	}
	seach_packet.get_seach_word(search_word, HTTP_REQUEST_ITEM_MAX_LENGTH);
	
	// ��ȡ�����ʻ�
	// ��������ʱ�����ܳ��ֶ�������ˣ���Щ�ʻ����ʹ�ÿո�Ͽ��ȵ�
	using namespace std;
	vector<string> vecKeywords;
	extractSearchWord(search_word, &vecKeywords);
	vector<string>::iterator iter = vecKeywords.begin();
	for (; iter != vecKeywords.end(); ++iter) {
		// ������κ�һ���ʻ��Ǻڴʣ��򷵻�
		if (false == checkSearchWord(search_word, host_name)) {
			return false;
		}
	}

	return true; 
}

bool checkHTTPRequest(HTTPRequestPacket * packet) {
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};
	packet->getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	
	// ���������IP��DNS��ַ����
	// ���DNS���ɴ�
	if (!isContainsIP(buffer)) {
		if (false == checkDNS(buffer)) 
			return false;
	} else {
	}

	// check search rule
	return checkSeachRule(packet);
}

bool accessNetword() {
	try {
		AutoInitInScale _auto_com_init;

		// ��ʼ��
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