#include "StdAfx.h"
#include ".\httprequestpacket.h"
#include <utility\strutility.h>
#include <utility\dns.h>
#include <fstream>

namespace {

INT_PTR ahieve_buffer(const TCHAR * filename, const char *buf, const INT_PTR len) {
	if (len < 10) return 0;
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::app);
	file.write(buf, len);
	return 0;
}

INT_PTR gen_filename(TCHAR *filename, const INT_PTR buf_size) {
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

INT_PTR HTTPRequestPacket::getMainHostName(char *buffer, const INT_PTR len) {
	memset(buffer, 0, len);
	strncpy(buffer, main_host_, getWrittenCount(len-1));
	return static_cast<INT_PTR>(strlen(buffer));
}
INT_PTR HTTPRequestPacket::getHost(char *buffer, const INT_PTR len) {
	memset(buffer, 0, len);
	strncpy(buffer, host_, getWrittenCount(len-1));
	return static_cast<INT_PTR>(strlen(buffer));
}
INT_PTR HTTPRequestPacket::getReferer(char *buffer, const INT_PTR len) {
	memset(buffer, 0, len);
	strncpy(buffer, referer_, getWrittenCount(len-1));
	return static_cast<INT_PTR>(strlen(buffer));
}
INT_PTR HTTPRequestPacket::getUserAgent(char *buffer, const INT_PTR len) {
	memset(buffer, 0, len);
	strncpy(buffer, useagent_, getWrittenCount(len-1));
	return static_cast<INT_PTR>(strlen(buffer));
}

INT_PTR HTTPRequestPacket::getGET(char *buffer, const INT_PTR len) {
	memset(buffer, 0, len);
	if (HTTP_REQUEST_OPETYPE_GET == getRequestType()) {
		strncpy(buffer, oper_, len-1);
		return static_cast<INT_PTR>(strlen(buffer));
	}
	return 0;
}

void HTTPRequestPacket::reset() {
	memset(host_, 0, sizeof(host_));
	memset(referer_, 0, sizeof(referer_));
	memset(useagent_, 0, sizeof(useagent_));
	memset(oper_, 0, sizeof(oper_));
}

// 专门针对
INT_PTR HTTPRequestPacket::parsePacket(WSABUF * wsabuf, const INT_PTR count) {
	char buffer[HTTP_REQUEST_PACKET_MAX] = {0};
	INT_PTR cur = 0;
	for (INT_PTR i = 0; i < count ; ++i) {
		memcpy(&(buffer[cur]), wsabuf[i].buf, wsabuf[i].len);
		cur += wsabuf[i].len;
	}

	return parsePacket(buffer, cur);
}

INT_PTR HTTPRequestPacket::parsePacket(char * buf, const INT_PTR len) {
	using namespace strutility;

	const char * HTTP_REQUEST_NEW_LINE = "\r\n";
	const INT_PTR  HTTP_REQUEST_NEW_LINE_LENGTH = static_cast<INT_PTR>(strlen(HTTP_REQUEST_NEW_LINE));
	//reset buffer 
	reset();

	INT_PTR cnt = 0;
	const char *p = buf;
	const char *next = strnstr(p, HTTP_REQUEST_NEW_LINE, HTTP_REQUEST_ITEM_MAX_LENGTH);

	// 注意p-buf < len, 保证等整个处理完之后，及时退出
	while (next != NULL) {
		if (strstr(p, HTTP_REQUEST_HOST) == p) {
			// 主机地址只留DNS主名
			const INT_PTR tab_length = static_cast<INT_PTR>(strlen(HTTP_REQUEST_HOST));
			strncpy(host_, p + tab_length, getWrittenCount(next - p - tab_length));
			get_main_dns_name(main_host_, HTTP_REQUEST_ITEM_MAX_LENGTH, host_);
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_REFERER) == p) {
			const INT_PTR tab_length = static_cast<INT_PTR>(strlen(HTTP_REQUEST_REFERER));
			strncpy(referer_, p + tab_length, getWrittenCount(next - p - tab_length));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_GET) == p) {
			const INT_PTR tab_length = static_cast<INT_PTR>(strlen(HTTP_REQUEST_OPER_GET));
			strncpy(oper_, p + tab_length, getWrittenCount(next - p - tab_length));
			http_request_type_ = HTTP_REQUEST_OPETYPE_GET;
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_POST) == p) {
			const INT_PTR tab_length = static_cast<INT_PTR>(strlen(HTTP_REQUEST_OPER_POST));
			strncpy(oper_, p + tab_length, getWrittenCount(next - p - tab_length));
			http_request_type_ = HTTP_REQUEST_OPETYPE_POST;
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_USER_AGENT) == p) {
			const INT_PTR tab_length = static_cast<INT_PTR>(strlen(HTTP_REQUEST_USER_AGENT));
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

// 注意期望值为 http://www.google.com/support/accounts/?hl=zh-CN
// GET /support/accounts/?hl=zh-CN HTTP/1.1
// Host: www.google.com
// 当用户打开的是一个网址时， 他不应有又后缀，
#define REQUEST_FILE_FORMAT_PNG			".png"
#define REQUEST_FILE_FORMAT_GIF				".gif"
#define REQUEST_FILE_FORMAT_JPG				".jpg"
#define REQUEST_FILE_FORMAT_BMP			".bmp"
#define REQUEST_FILE_FORMAT_CSS				".css"
#define REQUEST_FILE_FORMAT_JS				".js"
#define REQUEST_FILE_FORMAT_SWF			".swf"

bool HTTPRequestPacket::openPage() {
	// 如果请求包含是GET类型， 切其中不包含.js, .gif, .jpg, .css, .bmp, .png, .swf就可以认为打开的是一个网页
	// 网页的后缀可能是什么都没有， 也可能是 'html', 'php', 'asp', 'aspx'等，比较多
	// 总之地址栏内可能出现的后缀都是
	if (HTTP_REQUEST_OPETYPE_GET != http_request_type_) {
		return false;
	}

	if (NULL != strstr(oper_, REQUEST_FILE_FORMAT_PNG)) {
		return false;
	} else if (NULL != strstr(oper_, REQUEST_FILE_FORMAT_GIF)) {
		return false;
	} else if (NULL != strstr(oper_, REQUEST_FILE_FORMAT_JPG)) {
		return false;
	} else if (NULL != strstr(oper_, REQUEST_FILE_FORMAT_BMP)) {
		return false;
	} else if (NULL != strstr(oper_, REQUEST_FILE_FORMAT_CSS)) {
		return false;
	} else if (NULL != strstr(oper_, REQUEST_FILE_FORMAT_JS)) {
		return false;
	} else if (NULL != strstr(oper_, REQUEST_FILE_FORMAT_SWF)) {
		return false;
	} else {
		return true;
	}
}