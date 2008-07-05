#ifndef _UTILITY_HTTPCONTENTCHECKER_H__
#define _UTILITY_HTTPCONTENTCHECKER_H__

class HTTPPacket;
class HTTP_RESPONSE_HEADER;


// class HttpContentChecker
// ������ݸ�����HttpPacket����֤�����Ƿ���Ч
// ��֤�Ĵ�����ڱ��أ� �������COM������
class HttpContentChecker {
public:
	static HttpContentChecker * getChecker(const HTTP_RESPONSE_HEADER *);
	virtual bool checkHTTPContent(const HTTPPacket *packet) = 0;
};

#endif  // _UTILITY_HTTPCONTENTCHECKER_H__