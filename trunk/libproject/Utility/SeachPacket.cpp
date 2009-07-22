#include "StdAfx.h"
#include ".\seachpacket.h"
#include ".\strutility.h"
#include <utility\strutility.h>
#include <utility\dns.h>
#include <assert.h>
#include <fstream>

#define SEARCH_COMMAND_GOOGLE		"/search?"
#define SEARCH_GOOGLE_SUGGESTION	"/complete/search?"
#define SEARCH_COMMAND_YAHOO			"/search?"
#define SEARCH_COMMAND_BAIDU			"/s?"


#define SEARCHWORD_TITLE_GOOGLE		"q="
#define SEARCHWORD_TITLE_YAHOO		"p="
#define SEARCHWORD_TITLE_BAIDU		"wd="
#define SEARCHWORD_TAIL				"&"

#define GOOGLE_SEARCH_ADDRESS	TEXT("search.google.com")
#define YAHOO_SEARCH_ADDRESS	TEXT("search.yahoo.com")
#define BAIDU_SEARCH_ADDRESS	TEXT("search.baidu.com")


SeachPacket::SeachPacket(void) {
	seach_engine_ = SEACH_ENGINE_UNKNOWN;
}

SeachPacket::~SeachPacket(void) {
}


// members
bool SeachPacket::is_google_seach(const char *oper) {
	// 首先判断是不是suggestion
	if (NULL != _tcsstr(oper, SEARCH_GOOGLE_SUGGESTION)) {
		return false;
	} else if (NULL != _tcsstr(oper, SEARCH_COMMAND_GOOGLE)) {
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

int SeachPacket::parse_google(const char * oper) {
	if (false == is_google_seach(oper)) {
		return 0;
	}

	// 获取搜索词
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEARCHWORD_TITLE_GOOGLE, SEARCHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_GOOGLE;
	return (int)strlen(seach_word);
}
int SeachPacket::parse_baidu(const char * oper) {
	if (false == is_baidu_seach(oper)) {
		return 0;
	}

	// 获取搜索词
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEARCHWORD_TITLE_BAIDU, SEARCHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_BAIDU;
	return (int)strlen(seach_word);
}
int SeachPacket::parse_yahoo(const char * oper) {
	if (false == is_yahoo_seach(oper)) {
		return 0;
	}

	// 获取搜索词
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEARCHWORD_TITLE_YAHOO, SEARCHWORD_TAIL, false) == 0) {
		return 0;
	}

	seach_engine_ = SEACH_ENGINE_YAHOO;
	return (int)strlen(seach_word);
}

//===============================================================
// 分析包

int SeachPacket::parse(const char * oper, const char * host_name) {
	if (strlen(host_name) == 0) {
		return 0;
	}
	// oper 都已 " HTTP/1.1" 或者" HTTP/1.0"结尾， 我们用&代替其中的空格 ;)
	// 将空格用" "用"&"代替
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};
	strcpy(buffer, oper);
	char * pos = strstr(buffer, " ");
	if (NULL != pos) {
		pos[0] = '&';
	} else {
		return 0;
	}

	// 对于主流的搜索引擎其hostname, 全部都是 search.**.com
	// 如search.yahoo.com
	if (0 == _tcsnicmp(host_name, GOOGLE_SEARCH_ADDRESS, strlen(GOOGLE_SEARCH_ADDRESS))) {
		return parse_google(buffer);
	} else if (0 == _tcsnicmp(host_name, YAHOO_SEARCH_ADDRESS, _tcslen(YAHOO_SEARCH_ADDRESS))) {
		return parse_yahoo(buffer);
	} else if (0 == _tcsnicmp(host_name, BAIDU_SEARCH_ADDRESS, _tcslen(BAIDU_SEARCH_ADDRESS))) {
		return parse_baidu(buffer);
	} else {
		// 如果不是这几个主机
		return 0;
	}
}


int SeachPacket::get_seach_word(char *buf, const int size) {
	memset(buf, 0, size);
	strncpy(buf, seach_word, size);
	return (int)strlen(buf);
}