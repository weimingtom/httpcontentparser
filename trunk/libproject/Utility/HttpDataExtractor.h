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
	virtual INT_PTR addBuffer(const char * buf, const INT_PTR len) = 0;
	virtual bool finished() const = 0;
	INT_PTR getExtractorTypeCode();

	// 对于没有指定长度的包，他可能是主动关闭连接的，
	// 这时候需要我们传送一个0长度的包
	bool transferTail() { return transfer_tail_;}
public:
	static HttpDataExtractor * Create(const HTTP_RESPONSE_HEADER *,
		ProtocolPacket<HTTP_PACKET_SIZE> *data);
protected:
	HttpDataExtractor() { transfer_tail_ = false;}

	bool transfer_tail_;
};

#endif  // _UTILITY_HTTPDATAEXTRACTOR_H__