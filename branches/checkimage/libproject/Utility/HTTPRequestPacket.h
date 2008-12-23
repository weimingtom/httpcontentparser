#ifndef _UTILITY_HTTP_REQUEST_PACKET_H__
#define _UTILITY_HTTP_REQUEST_PACKET_H__

#define HTTP_REQUEST_ITEM_MAX_LENGTH 1024
#define HTTP_REQUEST_PACKET_MAX		 (1024 * 64)

// ֻ��Ҫʹ��char���ͣ�������TCHAR * ���ͣ���Ϊ����char�������
// ������������һ����ַ�����������紫�䲻��ʹ��Unicode
// ����HTTP�����ͷ��
class HTTPRequestPacket {
public:
	HTTPRequestPacket(void);
	~HTTPRequestPacket(void);
public:
	int parsePacket(char * buf, const int len);
	int parsePacket(WSABUF * buf, const int count);

	int getGET(char *buffer, const int len);
	int getHost(char *buffer, const int len);
	int getReferer(char *buffer, const int len);
	int getUserAgent(char *buffer, const int len);
	int getMainHostName(char *buffer, const int len);
	int getRequestType() { return http_request_type_;}
	
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

	// ���س���
	int getWrittenCount(int length) const {
		return (HTTP_REQUEST_ITEM_MAX_LENGTH > length) ? length : HTTP_REQUEST_ITEM_MAX_LENGTH;
	}

	const static char * HTTP_REQUEST_HOST;
	const static char * HTTP_REQUEST_REFERER;
	const static char * HTTP_REQUEST_OPER_GET;
	const static char * HTTP_REQUEST_OPER_POST;
	const static char * HTTP_REQUEST_USER_AGENT;		// ���������

	int http_request_type_;
};

#endif  // _UTILITY_HTTP_REQUEST_PACKET_H__