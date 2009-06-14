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

int HTTPRequestPacket::getMainHostName(char *buffer, const int len) {
	strncpy(buffer, main_host_, getWrittenCount(len));
	return static_cast<int>(strlen(buffer));
}
int HTTPRequestPacket::getHost(char *buffer, const int len) {
	strncpy(buffer, host_, getWrittenCount(len));
	return static_cast<int>(strlen(buffer));
}
int HTTPRequestPacket::getReferer(char *buffer, const int len) {
	strncpy(buffer, referer_, getWrittenCount(len));
	return static_cast<int>(strlen(buffer));
}
int HTTPRequestPacket::getUserAgent(char *buffer, const int len) {
	strncpy(buffer, useagent_, getWrittenCount(len));
	return static_cast<int>(strlen(buffer));
}

void HTTPRequestPacket::reset() {
	memset(host_, 0, sizeof(host_));
	memset(referer_, 0, sizeof(referer_));
	memset(useagent_, 0, sizeof(useagent_));
	memset(oper_, 0, sizeof(oper_));
}

// ר�����
int HTTPRequestPacket::parsePacket(WSABUF * wsabuf, const int count) {
	char buffer[HTTP_REQUEST_PACKET_MAX] = {0};
	int cur = 0;
	for (int i = 0; i < count ; ++i) {
		memcpy(&(buffer[cur]), wsabuf[i].buf, wsabuf[i].len);
		cur += wsabuf[i].len;
	}

	return parsePacket(buffer, cur);
}

int HTTPRequestPacket::getGET(char *buffer, const int len) {
	if (HTTP_REQUEST_OPETYPE_GET == getRequestType()) {
		strncpy(buffer, oper_, len);
		return static_cast<int>(strlen(buffer));
	}

	return 0;
}
int HTTPRequestPacket::parsePacket(char * buf, const int len) {
	using namespace strutility;

	const char * HTTP_REQUEST_NEW_LINE = "\r\n";
	const int  HTTP_REQUEST_NEW_LINE_LENGTH = static_cast<int>(strlen(HTTP_REQUEST_NEW_LINE));
	//reset buffer 
	reset();

	int cnt = 0;
	const char *p = buf;
	const char *next = strnstr(p, HTTP_REQUEST_NEW_LINE, HTTP_REQUEST_ITEM_MAX_LENGTH);

	// ע��p-buf < len, ��֤������������֮�󣬼�ʱ�˳�
	while (next != NULL) {
		if (strstr(p, HTTP_REQUEST_HOST) == p) {
			// ������ַֻ��DNS����
			const int tab_length = static_cast<int>(strlen(HTTP_REQUEST_HOST));
			strncpy(host_, p + tab_length, getWrittenCount(next - p - tab_length));
			get_main_dns_name(main_host_, HTTP_REQUEST_ITEM_MAX_LENGTH, host_);
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_REFERER) == p) {
			const int tab_length = static_cast<int>(strlen(HTTP_REQUEST_REFERER));
			strncpy(referer_, p + tab_length, getWrittenCount(next - p - tab_length));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_GET) == p) {
			const int tab_length = static_cast<int>(strlen(HTTP_REQUEST_OPER_GET));
			strncpy(oper_, p + tab_length, getWrittenCount(next - p - tab_length));
			http_request_type_ = HTTP_REQUEST_OPETYPE_GET;
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_POST) == p) {
			const int tab_length = static_cast<int>(strlen(HTTP_REQUEST_OPER_POST));
			strncpy(oper_, p + tab_length, getWrittenCount(next - p - tab_length));
			http_request_type_ = HTTP_REQUEST_OPETYPE_POST;
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_USER_AGENT) == p) {
			const int tab_length = static_cast<int>(strlen(HTTP_REQUEST_USER_AGENT));
			strncpy(useagent_, p + tab_length, getWrittenCount(next-p-tab_length));
			cnt++;
		} else if (strstr(p, HTTP_REQUEST_OPER_POST) == p) {
			cnt++;
		} else {
		}
		
		next += HTTP_REQUEST_NEW_LINE_LENGTH; // �ƶ�����λ��
		p = next;
		next = strnstr(p, HTTP_REQUEST_NEW_LINE, HTTP_REQUEST_ITEM_MAX_LENGTH);
	}

	return cnt;
}

// ע������ֵΪ http://www.google.com/support/accounts/?hl=zh-CN
// GET /support/accounts/?hl=zh-CN HTTP/1.1
// Host: www.google.com
// ���û��򿪵���һ����ַʱ�� ����Ӧ���ֺ�׺��
#define REQUEST_FILE_FORMAT_PNG			".png"
#define REQUEST_FILE_FORMAT_GIF				".gif"
#define REQUEST_FILE_FORMAT_JPG				".jpg"
#define REQUEST_FILE_FORMAT_BMP			".bmp"
#define REQUEST_FILE_FORMAT_CSS				".css"
#define REQUEST_FILE_FORMAT_JS				".js"
#define REQUEST_FILE_FORMAT_SWF			".swf"

bool HTTPRequestPacket::openPage() {
	// ������������GET���ͣ� �����в�����.js, .gif, .jpg, .css, .bmp, .png, .swf�Ϳ�����Ϊ�򿪵���һ����ҳ
	// ��ҳ�ĺ�׺������ʲô��û�У� Ҳ������ 'html', 'php', 'asp', 'aspx'�ȣ��Ƚ϶�
	// ��֮��ַ���ڿ��ܳ��ֵĺ�׺����
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