#include "StdAfx.h"
#include ".\seachpacket.h"
#include ".\strutility.h"
#include <utility\strutility.h>
#include <utility\dns.h>
#include <assert.h>
#include <fstream>

#define SEARCH_COMMAND_GOOGLE		"/search"
#define SEARCH_COMMAND_YAHOO			"/search"
#define SEARCH_COMMAND_BAIDU			"/s"


#define SEARCHWORD_TITLE_GOOGLE		"q="
#define SEARCHWORD_TITLE_YAHOO		"p="
#define SEARCHWORD_TITLE_BAIDU		"wd="
#define SEARCHWORD_TAIL				"&"


SeachPacket::SeachPacket(void) {
	seach_engine_ = SEACH_ENGINE_UNKNOWN;
}

SeachPacket::~SeachPacket(void) {
}


// members
bool SeachPacket::is_google_seach(const char *oper) {
	 if (NULL != _tcsstr(oper, SEARCH_COMMAND_GOOGLE)) {
		return true;
	} else { 
		return false;
	}
}
bool SeachPacket::is_baidu_seach(const char *oper) {
	if (NULL != _tcsstr(oper, SEARCH_COMMAND_BAIDU)) {
		return true;
	} else {
		return false;
	}
}
bool SeachPacket::is_yahoo_seach(const char *oper) {
	if (NULL != _tcsstr(oper, SEARCH_COMMAND_YAHOO)) {
		return true;
	} else {
		return false;
	}
}

INT_PTR SeachPacket::parse_google(const char * oper) {
	if (false == is_google_seach(oper)) {
		return 0;
	}

	// ��ȡ������
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEARCHWORD_TITLE_GOOGLE, SEARCHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_GOOGLE;
	return (INT_PTR)strlen(seach_word);
}
INT_PTR SeachPacket::parse_baidu(const char * oper) {
	if (false == is_baidu_seach(oper)) {
		return 0;
	}

	// ��ȡ������
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEARCHWORD_TITLE_BAIDU, SEARCHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_BAIDU;
	return (INT_PTR)strlen(seach_word);
}
INT_PTR SeachPacket::parse_yahoo(const char * oper) {
	if (false == is_yahoo_seach(oper)) {
		return 0;
	}

	// ��ȡ������
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEARCHWORD_TITLE_YAHOO, SEARCHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_YAHOO;
	return (INT_PTR)strlen(seach_word);
}

//===============================================================
// ������

INT_PTR SeachPacket::parse(const char * oper, const char * host_name) {
	if (strlen(host_name) == 0) {
		return 0;
	}
	// oper ���� " HTTP/1.1" ����" HTTP/1.0"��β�� ������&�������еĿո� ;)
	// ���ո���" "��"&"����
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};
	strcpy(buffer, oper);
	char * pos = strstr(buffer, " ");
	if (NULL != pos) {
		pos[0] = '&';
	} else {
		return 0;
	}

	// ��������������������hostname, ȫ������ search.**.com
	// ��search.yahoo.com
	using namespace strutility;

	// ���host_name��http://��ͷ
	const char *http  = "http://";
	const INT_PTR http_len = static_cast<INT_PTR>(strlen(http));
	if (true == beginwith(host_name, http)) {
		host_name += http_len;
	}

	// ��ȡ������ַ
	if ( strutility::beginwith(host_name, "www.google")) {
		return parse_google(buffer);
	} else if ( strutility::beginwith(host_name, "search.yahoo")) {
		return parse_yahoo(buffer);
	} else if ( strutility::beginwith(host_name, "www.baidu")) {
		return parse_baidu(buffer);
	} else {
		// ��������⼸������
		return 0;
	}
}


INT_PTR SeachPacket::get_seach_word(char *buf, const INT_PTR size) {
	memset(buf, 0, size);
	strncpy(buf, seach_word, size);
	return (INT_PTR)strlen(buf);
}