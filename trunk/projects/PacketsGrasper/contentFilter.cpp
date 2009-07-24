#include "StdAfx.h"
#include ".\contentfilter.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <utility\protocolpacket.h>
#include <utility\HTTPPacket.h>
#include <comdef.h>
#include <zlib\zlib.h>
#include <assert.h>
#include <webcontenttype.h>

ContentFilter::ContentFilter(void) {
}

ContentFilter::~ContentFilter(void) {
}

bool ContentFilter::checkHTTPContent(HTTPPacket *packet) {
	// ��ȡ����
	ProtocolPacket<HTTP_PACKET_SIZE> * http_data = packet->getData();

	const int data_size = http_data->getTotalSize();
	char * data = new char[data_size];

	// �����ݶ�����
	int bytes_read = http_data->read(data, data_size);
	assert (data_size == bytes_read);

	if (packet->getContentType() == CONTYPE_HTML) {
		return checkText(packet->getContentType(), data, data_size);
	} else if (isImage(packet->getContentType())) {
		return checkImage(packet->getContentType(), data, data_size);
	}
	return true;
}

bool ContentFilter::needCheck(const int type) {
	return false;
}

// private member
bool ContentFilter::checkText(const int type, char * buf, const int len) {
	return false;
}

bool ContentFilter::checkImage(const int type, char * buf, const int len) {
	// ����ȷ���Ƿ���Ҫ���
	return false;
}