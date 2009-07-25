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
	virtual INT_PTR addBuffer(const char * buf, const INT_PTR len) = 0;
	virtual bool finished() const = 0;
	INT_PTR getExtractorTypeCode();

	// ����û��ָ�����ȵİ����������������ر����ӵģ�
	// ��ʱ����Ҫ���Ǵ���һ��0���ȵİ�
	bool transferTail() { return transfer_tail_;}
public:
	static HttpDataExtractor * Create(const HTTP_RESPONSE_HEADER *,
		ProtocolPacket<HTTP_PACKET_SIZE> *data);
protected:
	HttpDataExtractor() { transfer_tail_ = false;}

	bool transfer_tail_;
};

#endif  // _UTILITY_HTTPDATAEXTRACTOR_H__