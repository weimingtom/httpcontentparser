// GlobalChecker.cpp : CGlobalChecker ��ʵ��

#include "stdafx.h"
#include ".\globalchecker.h"
#include ".\globalvariable.h"
#include <string>
#include <comdef.h>
#include <globalSetting.h>
#include <com\actiondefine.h>
#include <utility\HTTPPacket.h>
// CGlobalChecker

namespace {
bool isImage(const int type) {
	if (type == HTTP_RESPONSE_HEADER::CONTYPE_GIF||
		type == HTTP_RESPONSE_HEADER::CONTYPE_JPG||
		type == HTTP_RESPONSE_HEADER::CONTYPE_PNG) {
		return true;
	} else {
		return false;
	}
}

bool isHTML(const int type) {
	return (type == HTTP_RESPONSE_HEADER::CONTYPE_HTML);
}
};
STDMETHODIMP CGlobalChecker::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = {
		&IID_IGlobalChecker
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// DNS�Ƿ�Ϸ��� ����������enabled����
STDMETHODIMP CGlobalChecker::checkDNS(BSTR dns, VARIANT_BOOL* enabled) {
	*enabled = global_setting_.checkDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}

// ע�⣺�˺���ֻ�ܶ�UTF8��������ݽ�����ȷ����
// ����ڵ�����֮ǰҪȷ�����������ʹ��UTF8����
STDMETHODIMP CGlobalChecker::checkContent(LONG type, CHAR data[], LONG len, VARIANT_BOOL* passed) {
	if (isHTML(type) == true) {
	} else {
	}

	return S_OK;
}

STDMETHODIMP CGlobalChecker::needCheck(LONG type, VARIANT_BOOL* needed) {
	//global_setting_
	return S_OK;
}

// ����ͼƬ�����������ܽϴ�
// �������ֻ��ͼƬ�Ĺ��������֤��ͼƬ�����֤��Packetgrasper����
// �������Ա���������ݵĴ���
STDMETHODIMP CGlobalChecker::checkImage(LONG type, LONG* action_code) {
	//�������Ҫ��ʾimageֱ�ӷ��أ�  ע��һЩСͼƬ����Ӧ�÷Ź���
	if (global_setting_.showImage() == false) {
		*action_code = ACTION_IMAGE_CHECK_DENY;
	}

	// �Ƿ�Ӧ�ü����Ӧ��ͼƬ
	if (global_setting_.imageNeedCheck(type)) {
		*action_code = ACTION_IMAGE_CHECK_PASS;
	} else {
		// �������Ҫ���
		*action_code = ACTION_IMAGE_CHECK_ENABLE;
	}
	return S_OK;
}
