#ifndef _UTILITY_HTTPDATAEXTRACTOR_H__
#define _UTILITY_HTTPDATAEXTRACTOR_H__

#include ".\HTTPPacket.h"
#include <utility\protocolpacket.h>


class HTTP_RESPONSE_HEADER;

//=========================================
// ���������࣬�����𱣴����ݣ�ֻ����������
// ��HTTPЭ���д������ֶ�����
// 1. ʹ�� chunk
// 2. ʹ�� content-length
class HttpDataExtractor {
public:
	virtual int addBuffer(const char * buf, const int len) = 0;
	virtual bool finished() const = 0;
public:
	static HttpDataExtractor * Create(const HTTP_RESPONSE_HEADER *,
		ProtocolPacket<HTTP_PACKET_SIZE> *data);
};

#endif  // _UTILITY_HTTPDATAEXTRACTOR_H__