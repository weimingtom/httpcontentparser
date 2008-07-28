#include "StdAfx.h"
#include ".\contentfilter.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\cominit.h>
#include <utility\protocolpacket.h>
#include <utility\HTTPPacket.h>
#include <comdef.h>
#include <zlib\zlib.h>
#include <assert.h>

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

	if (packet->getContentType() == HTTP_RESPONSE_HEADER::CONTYPE_HTML) {
		return checkText(packet->getContentType(), data, data_size);
	} else if (isImage(packet->getContentType())) {
		return checkImage(packet->getContentType(), data, data_size);
	}
	return true;
}

bool ContentFilter::needCheck(const int type) {
	try {
		AutoInitInScale com_init();
		IGlobalChecker * checker;
		HRESULT hr = CoCreateInstance(CLSID_GlobalChecker,
			NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalChecker, (LPVOID*)&checker);
		if (FAILED(hr)) {
			// �������ʧ�ܣ����еĳ�����Ҫ����飬 �������еİ�����������
			return true;
		}
		
		VARIANT_BOOL needed;
		hr = checker->needCheck(type, &needed);
		return needed;
	} catch (_com_error &e) {
		return false;
	}
	return false;
}

// private member
bool ContentFilter::checkText(const int type, char * buf, const int len) {
	try {
		AutoInitInScale com_init();
		IGlobalChecker * checker;
		HRESULT hr = CoCreateInstance(CLSID_GlobalChecker,
			NULL, CLSCTX_LOCAL_SERVER, IID_IGlobalChecker, (LPVOID*)&checker);
		if (FAILED(hr)) {
			// �������ʧ�ܣ����еĳ�����Ҫ����飬 �������еİ�����������
			return true;
		}
		
		VARIANT_BOOL needed;
		hr = checker->checkContent(type, buf, len, &needed);
		return needed;
	} catch (_com_error &e) {
		return false;
	}
	return false;
}

bool ContentFilter::checkImage(const int type, char * buf, const int len) {
	// ����ȷ���Ƿ���Ҫ���
	return false;
}

bool ContentFilter::isImage(const int type) const {
	if (type == HTTP_RESPONSE_HEADER::CONTYPE_GIF||
		type == HTTP_RESPONSE_HEADER::CONTYPE_JPG||
		type == HTTP_RESPONSE_HEADER::CONTYPE_PNG) {
		return true;
	} else {
		return false;
	}
}