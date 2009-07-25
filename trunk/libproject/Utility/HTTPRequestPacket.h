#ifndef _UTILITY_HTTP_REQUEST_PACKET_H__
#define _UTILITY_HTTP_REQUEST_PACKET_H__

#define HTTP_REQUEST_ITEM_MAX_LENGTH 1024
#define HTTP_REQUEST_PACKET_MAX		 (1024 * 64)

// 只需要使用char类型，而不是TCHAR * 类型，因为这里char代表的是
// 缓冲区而不是一般的字符串，因此网络传输不会使用Unicode
// 解析HTTP请求的头部
class HTTPRequestPacket {
public:
	HTTPRequestPacket(void);
	~HTTPRequestPacket(void);
public:
	INT_PTR parsePacket(char * buf, const INT_PTR len);
	INT_PTR parsePacket(WSABUF * buf, const INT_PTR count);

	INT_PTR getGET(char *buffer, const INT_PTR len);
	INT_PTR getHost(char *buffer, const INT_PTR len);
	INT_PTR getReferer(char *buffer, const INT_PTR len);
	INT_PTR getUserAgent(char *buffer, const INT_PTR len);
	INT_PTR getMainHostName(char *buffer, const INT_PTR len);
	INT_PTR getRequestType() { return http_request_type_;}

	bool openPage();
	enum {
		HTTP_REQUEST_OPETYPE_GET = 0,
		HTTP_REQUEST_OPETYPE_POST,
	};
private:
	void reset();

	char main_host_[HTTP_REQUEST_ITEM_MAX_LENGTH];
	char host_[HTTP_REQUEST_ITEM_MAX_LENGTH];
	char referer_[HTTP_REQUEST_ITEM_MAX_LENGTH];
	char useagent_[HTTP_REQUEST_ITEM_MAX_LENGTH];
	char oper_[HTTP_REQUEST_ITEM_MAX_LENGTH];

	// 返回长度
	INT_PTR getWrittenCount(INT_PTR length) const {
		return (HTTP_REQUEST_ITEM_MAX_LENGTH > length) ? length : HTTP_REQUEST_ITEM_MAX_LENGTH;
	}

	const static char * HTTP_REQUEST_HOST;
	const static char * HTTP_REQUEST_REFERER;
	const static char * HTTP_REQUEST_OPER_GET;
	const static char * HTTP_REQUEST_OPER_POST;
	const static char * HTTP_REQUEST_USER_AGENT;		// 代表浏览器

	INT_PTR http_request_type_;
};

#endif  // _UTILITY_HTTP_REQUEST_PACKET_H__