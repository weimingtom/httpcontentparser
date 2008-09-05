#include "StdAfx.h"
#include ".\httprequestpacket.h"
#include <utility\strutility.h>

//============================================
const char * HTTPRequestPacket::HTTP_REQUEST_HOST = "Host: ";
const char * HTTPRequestPacket::HTTP_REQUEST_REFERER = "Referer: ";
const char * HTTPRequestPacket::HTTP_REQUEST_USER_AGENT = "User-Agent: ";
const char * HTTPRequestPacket::HTTP_REQUEST_OPER_GET = "GET";


//===============================================
HTTPRequestPacket::HTTPRequestPacket(void) {
}

HTTPRequestPacket::~HTTPRequestPacket(void) {
}

int HTTPRequestPacket::getHost(char *buffer, const int len) {
	strncpy(buffer, host_, getWrittenCount(len));
	return strlen(buffer);
}
int HTTPRequestPacket::getReferer(char *buffer, const int len) {
	strncpy(buffer, referer_, getWrittenCount(len));
	return strlen(buffer);
}
int HTTPRequestPacket::getUserAgent(char *buffer, const int len) {
	strncpy(buffer, useagent_, getWrittenCount(len));
	return strlen(buffer);
}

void HTTPRequestPacket::reset() {
	memset(host_, 0, sizeof(host_));
	memset(referer_, 0, sizeof(referer_));
	memset(useagent_, 0, sizeof(useagent_));
}

int HTTPRequestPacket::parsePacket(char * buf, const int len) {
	using namespace strutility;

	//reset buffer
	reset();

	int cnt = 0;
	char *p = buf;
	char *next = strnstr(p, "\r\n", HTTP_REQUEST_ITEM_MAX_LENGTH);


	// 注意p-buf < len, 保证等整个处理完之后，及时退出
	while (NULL != p && p - buf < len) {
		if (strstr(p, HTTP_REQUEST_HOST) == p) {
			const int tab_length = strlen(HTTP_REQUEST_HOST);
			strncpy(host_, p + tab_length, getWrittenCount(next-p-tab_length));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_REFERER) == p) {
			const int tab_length = strlen(HTTP_REQUEST_REFERER);
			strncpy(referer_, p + tab_length, getWrittenCount(next-p-tab_length));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_GET) == p) {
			//strncpy(host_, p, getWrittenCount(next-p));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_USER_AGENT) == p) {
			const int tab_length = strlen(HTTP_REQUEST_USER_AGENT);
			strncpy(useagent_, p + tab_length, getWrittenCount(next-p-tab_length));
			cnt++;
		} else {
		}
		
		next += 2; // 移动两个位置
		p = next;
		next = strnstr(p, "\r\n", HTTP_REQUEST_ITEM_MAX_LENGTH);
	}

	return cnt;
}