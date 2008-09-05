#ifndef _UTILITY_HTTP_REQUEST_PACKET_H__
#define _UTILITY_HTTP_REQUEST_PACKET_H__

#define HTTP_REQUEST_ITEM_MAX_LENGTH 1024

// 解析HTTP请求的头部
class HTTPRequestPacket {
public:
	HTTPRequestPacket(void);
	~HTTPRequestPacket(void);
public:
	int parsePacket(const char * buf, const int len);

	int getHost(char *buffer, const int len);
	int getReferer(char *buffer, const int len);
	int getUserAgent(char *buffer, const int len);
private:
	char host_[HTTP_REQUEST_ITEM_MAX_LENGTH];
	char referer_[HTTP_REQUEST_ITEM_MAX_LENGTH];
	char useagent_[HTTP_REQUEST_ITEM_MAX_LENGTH];

	// 返回长度
	int getWrittenCount(int length) const {
		return (HTTP_REQUEST_ITEM_MAX_LENGTH > length) ? length : HTTP_REQUEST_ITEM_MAX_LENGTH;
	}
	const static char * HTTP_REQUEST_HOST;
	const static char * HTTP_REQUEST_REFERER;
	const static char * HTTP_REQUEST_OPER_GET;
	const static char * HTTP_REQUEST_USER_AGENT;		// 代表浏览器
};

#endif  // _UTILITY_HTTP_REQUEST_PACKET_H__