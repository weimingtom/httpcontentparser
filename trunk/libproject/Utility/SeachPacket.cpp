#include "StdAfx.h"
#include ".\seachpacket.h"
#include <utility\strutility.h>
#include <assert.h>

#define SEACH_COMMAND_GOOGLE		"/search?"
#define SEACH_COMMAND_YAHOO			"/search?"
#define SEACH_COMMAND_BAIDU			"/s?"


#define SEACHWORD_TITLE_GOOGLE		"&q="
#define SEACHWORD_TITLE_YAHOO		"q="
#define SEACHWORD_TITLE_BAIDU		"&wd="
#define SEACHWORD_TAIL				"&"


SeachPacket::SeachPacket(void) {
	seach_engine_ = SEACH_ENGINE_UNKNOWN;
}

SeachPacket::~SeachPacket(void) {
}


// members
bool SeachPacket::is_google_seach(const char *oper) {
	if (strstr(oper, SEACH_COMMAND_GOOGLE) == oper) {
		return true;
	} else { 
		return false;
	}
}
bool SeachPacket::is_baidu_seach(const char *oper) {
	if (strstr(oper, SEACH_COMMAND_BAIDU) == oper) {
		return true;
	} else {
		return false;
	}
}
bool SeachPacket::is_yahoo_seach(const char *oper) {
	if (strstr(oper, SEACH_COMMAND_YAHOO) == oper) {
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

	// 获取搜索词
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

	// 获取搜索词
	if (strutility::extract_string(seach_word, MAX_PATH, oper, SEACHWORD_TITLE_YAHOO, SEACHWORD_TAIL, false) == 0) {
		return 0;
	}


	seach_engine_ = SEACH_ENGINE_YAHOO;
	return (int)strlen(seach_word);
}

//===============================================================
// 分析包
int SeachPacket::parse(const char * oper, const char * host_name) {
	// oper 都已 " HTTP/1.1" 或者" HTTP/1.0"结尾， 我们用&代替其中的空格 ;)
	// 将空格用" "用"&"代替
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH] = {0};
	strcpy(buffer, oper);
	char * pos = strstr(buffer, " ");
	if (NULL != pos) {
		pos[0] = '&';
	} else {
		assert(false);
		return 0;
	}

	if (NULL != strstr(TEXT("google.com"), host_name)) {
		return parse_google(buffer);
	} else if (NULL != strstr(TEXT("yahoo.com"), host_name)) {
		return parse_yahoo(buffer);
	} else if (NULL != strstr(TEXT("baidu.com"), host_name)) {
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