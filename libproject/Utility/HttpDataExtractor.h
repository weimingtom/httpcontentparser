#ifndef _UTILITY_HTTPDATAEXTRACTOR_H__
#define _UTILITY_HTTPDATAEXTRACTOR_H__

#include ".\HTTPPacket.h"
#include <utility\protocolpacket.h>


class HTTP_RESPONSE_HEADER;

//=========================================
// 以下两个类，不负责保存数据，只负责处理数据
// 在HTTP协议中存在两种多包情况
// 1. 使用 chunk
// 2. 使用 content-length
class HttpDataExtractor {
public:
	virtual int addBuffer(const char * buf, const int len) = 0;
	virtual bool finished() const = 0;
public:
	static HttpDataExtractor * Create(const HTTP_RESPONSE_HEADER *,
		ProtocolPacket<HTTP_PACKET_SIZE> *data);
};

#endif  // _UTILITY_HTTPDATAEXTRACTOR_H__