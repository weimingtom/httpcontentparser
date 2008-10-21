#include "StdAfx.h"
#include ".\httprequestpacket.h"
#include <utility\strutility.h>
#include <utility\dns.h>
#include <fstream>

namespace {

int ahieve_buffer(const TCHAR * filename, const char *buf, const int len) {
	if (len < 10) return 0;
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::app);
	file.write(buf, len);
	return 0;
}

int gen_filename(TCHAR *filename, const int buf_size) {
	_sntprintf(filename, buf_size, TEXT("c:\\%d.log"), GetTickCount());
	return 0;
}
};
//============================================
const char * HTTPRequestPacket::HTTP_REQUEST_HOST = "Host: ";
const char * HTTPRequestPacket::HTTP_REQUEST_REFERER = "Referer: ";
const char * HTTPRequestPacket::HTTP_REQUEST_USER_AGENT = "User-Agent: ";
const char * HTTPRequestPacket::HTTP_REQUEST_OPER_GET = "GET ";
const char * HTTPRequestPacket::HTTP_REQUEST_OPER_POST = "POST ";


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
	memset(oper_, 0, sizeof(oper_));
}

// 专门针对
int HTTPRequestPacket::parsePacket(WSABUF * wsabuf, const int count) {
	char buffer[HTTP_REQUEST_PACKET_MAX] = {0};
	int cur = 0;
	for (int i = 0; i < count ; ++i) {
		memcpy(&(buffer[cur]), wsabuf[i].buf, wsabuf[i].len);
		cur += wsabuf[i].len;
	}

	ahieve_buffer(TEXT("c:\\request.log"), buffer, cur);

	return parsePacket(buffer, cur);
}

int HTTPRequestPacket::getGET(char *buffer, const int len) {
	if (HTTP_REQUEST_OPETYPE_GET == getRequestType()) {
		strncpy(buffer, oper_, len);
		return strlen(buffer);
	}

	return 0;
}
int HTTPRequestPacket::parsePacket(char * buf, const int len) {
	using namespace strutility;

	const char * HTTP_REQUEST_NEW_LINE = "\r\n";
	const int  HTTP_REQUEST_NEW_LINE_LENGTH = strlen(HTTP_REQUEST_NEW_LINE);
	//reset buffer
	reset();

	int cnt = 0;
	const char *p = buf;
	const char *next = strnstr(p, HTTP_REQUEST_NEW_LINE, HTTP_REQUEST_ITEM_MAX_LENGTH);

	// 注意p-buf < len, 保证等整个处理完之后，及时退出
	while (next != NULL) {
		if (strstr(p, HTTP_REQUEST_HOST) == p) {
			// 主机地址只留DNS主名
			const int tab_length = strlen(HTTP_REQUEST_HOST);
			get_main_dns_name(host_, HTTP_REQUEST_ITEM_MAX_LENGTH, p + tab_length);
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_REFERER) == p) {
			const int tab_length = strlen(HTTP_REQUEST_REFERER);
			strncpy(referer_, p + tab_length, getWrittenCount(next - p - tab_length));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_GET) == p) {
			const int tab_length = strlen(HTTP_REQUEST_OPER_GET);
			strncpy(oper_, p + tab_length, getWrittenCount(next - p - tab_length));
			http_request_type_ = HTTP_REQUEST_OPETYPE_GET;
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_POST) == p) {
			const int tab_length = strlen(HTTP_REQUEST_OPER_POST);
			strncpy(oper_, p + tab_length, getWrittenCount(next - p - tab_length));
			http_request_type_ = HTTP_REQUEST_OPETYPE_POST;
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_USER_AGENT) == p) {
			const int tab_length = strlen(HTTP_REQUEST_USER_AGENT);
			strncpy(useagent_, p + tab_length, getWrittenCount(next-p-tab_length));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_POST) == p) {
			cnt++;
		} else {
		}
		
		next += HTTP_REQUEST_NEW_LINE_LENGTH; // 移动两个位置
		p = next;
		next = strnstr(p, HTTP_REQUEST_NEW_LINE, HTTP_REQUEST_ITEM_MAX_LENGTH);
	}

	return cnt;
}