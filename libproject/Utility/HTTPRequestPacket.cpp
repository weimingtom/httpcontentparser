#include "StdAfx.h"
#include ".\httprequestpacket.h"


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

int HTTPRequestPacket::parsePacket(const char * buf, const int len) {
	int cnt = 0;
	const char *p = buf;
	const char *next = strstr(p, "\r\n");
	while (NULL != p) {
		if (strstr(p, HTTP_REQUEST_HOST) == p) {
			strncpy(host_, p + strlen(HTTP_REQUEST_HOST), getWrittenCount(next-p));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_REFERER) == p) {
			strncpy(referer_, p + strlen(HTTP_REQUEST_REFERER), getWrittenCount(next-p));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_GET) == p) {
			//strncpy(host_, p, getWrittenCount(next-p));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_USER_AGENT) == p) {
			strncpy(useagent_, p + strlen(HTTP_REQUEST_USER_AGENT), getWrittenCount(next-p));
			cnt++;
		} else {
		}
		
		next += 2; // 移动两个位置
		p = next;
		next = strstr(p, "\r\n");
	}

	return cnt;
}