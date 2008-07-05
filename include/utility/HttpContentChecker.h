#ifndef _UTILITY_HTTPCONTENTCHECKER_H__
#define _UTILITY_HTTPCONTENTCHECKER_H__

class HTTPPacket;
class HTTP_RESPONSE_HEADER;


// class HttpContentChecker
// 他会根据给定的HttpPacket来验证数据是否有效
// 验证的代码放在本地， 规则放在COM对象当中
class HttpContentChecker {
public:
	static HttpContentChecker * getChecker(const HTTP_RESPONSE_HEADER *);
	virtual bool checkHTTPContent(const HTTPPacket *packet) = 0;
};

#endif  // _UTILITY_HTTPCONTENTCHECKER_H__