#include "StdAfx.h"
#include ".\seachpacket.h"
#include ".\strutility.h"
#include <utility\strutility.h>
#include <assert.h>
#include <fstream>

#define SEACH_COMAND_START				"/"
#define SEACH_COMMAND_GOOGLE		"search?"
#define SEACH_COMMAND_YAHOO			"search?"
#define SEACH_COMMAND_BAIDU			"s?"


#define SEACHWORD_TITLE_GOOGLE		"q="
#define SEACHWORD_TITLE_YAHOO		"p="
#define SEACHWORD_TITLE_BAIDU		"wd="
#define SEACHWORD_TAIL				"&"


SeachPacket::SeachPacket(void) {
	seach_engine_ = SEACH_ENGINE_UNKNOWN;
}

SeachPacket::~SeachPacket(void) {
}


// members
bool SeachPacket::is_google_seach(const char *oper) {
	if (strutility::beginwith(oper, SEACH_COMAND_START))
	{
		oper ++;
	}

	if (strutility::beginwith(oper, SEACH_COMMAND_GOOGLE)) {
		return true;
	} else { 
		return false;
	}
}
bool SeachPacket::is_baidu_seach(const char *oper) {
	if (strutility::beginwith(oper, SEACH_COMAND_START))
	{
		oper ++;
	}

	if (strutility::beginwith(oper, SEACH_COMMAND_BAIDU)) {
		return true;
	} else {
		return false;
	}
}
bool SeachPacket::is_yahoo_seach(const char *oper) {
	if (strutility::beginwith(oper, SEACH_COMAND_START))
	{
		oper ++;
	}

	if (strutility::beginwith(oper, SEACH_COMMAND_YAHOO)) {
		return true;
	} else {
		return false;
	}
}

int SeachPacket::parse_google(const char * oper) {
	if (false == is_google_seach(oper)) {
		return 0;
	}

	// ��ȡ������
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEACHWORD_TITLE_GOOGLE, SEACHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_GOOGLE;
	return (int)strlen(seach_word);
}
int SeachPacket::parse_baidu(const char * oper) {
	if (false == is_baidu_seach(oper)) {
		return 0;
	}

	// ��ȡ������
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEACHWORD_TITLE_BAIDU, SEACHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_BAIDU;
	return (int)strlen(seach_word);
}
int SeachPacket::parse_yahoo(const char * oper) {
	if (false == is_yahoo_seach(oper)) {
		return 0;
	}

	// ��ȡ������
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEACHWORD_TITLE_YAHOO, SEACHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_YAHOO;
	return (int)strlen(seach_word);
}

//===============================================================
// ������
int SeachPacket::parse(const char * oper, const char * host_name) {
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

	using namespace strutility;

	// ���host_name��http://��ͷ
	const char *http  = "http://";
	const int http_len = strlen(http);
	if (true == beginwith(host_name, http)) {
		host_name += http_len;
	}

	if (true == beginwith(host_name, "www.google")) {
		return parse_google(buffer);
	} else if (true == beginwith(host_name, "search.yahoo")) {
		return parse_yahoo(buffer);
	} else if (true == beginwith(host_name, "www.baidu")) {
		return parse_baidu(buffer);
	} else {
		// ��������⼸������
		return 0;
	}
}


int SeachPacket::get_seach_word(char *buf, const int size) {
	memset(buf, 0, size);
	strncpy(buf, seach_word, size);
	return (int)strlen(buf);
}