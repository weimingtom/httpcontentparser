#include "StdAfx.h"
#include ".\httpcontentchecker.h"
#include ".\HTTPPacket.h"
#include <assert.h>

// ע�⣬��Ҫͬ������
// �����Ϻ���Ҫ����packet�Ķ�ָ��

// ����һ�����õ�check,��ͨ������δ֪���������ݵķ���
// ����Զ�����سɹ�
class NoneChecker : public HttpContentChecker {
	virtual bool checkHTTPContent(const HTTPPacket *packet) {
		return true;
	}
};

// �������Ҫ���ڷ���ͼƬ����
class ImageChecker : public HttpContentChecker {
	virtual bool checkHTTPContent(const HTTPPacket *packet) {
		return true;
	}
};

// ��Ҫ���ڷ����ı�����
class TextChecker : public HttpContentChecker {
	virtual bool checkHTTPContent(const HTTPPacket *packet) {
		return true;
	}
};


//========================================================
// ����HEADER�����ݴ���Checker
HttpContentChecker * HttpContentChecker::getChecker(const HTTP_RESPONSE_HEADER * header) {
	int content_type =  header->getContentType();
	switch(content_type) {
		case HTTP_RESPONSE_HEADER::CONTYPE_GIF:
		case HTTP_RESPONSE_HEADER::CONTYPE_JPG:
		case HTTP_RESPONSE_HEADER::CONTYPE_PNG:
			{	// ͼ��
				static ImageChecker checker;
				return &checker;
			}
			break;
		case HTTP_RESPONSE_HEADER::CONTYPE_HTML:
			{	// ����
				static TextChecker checker;
				return &checker;
			}
			break;
		default:
			{	// δ֪����
				static NoneChecker checker;
				return &checker;
			}
	}
}

