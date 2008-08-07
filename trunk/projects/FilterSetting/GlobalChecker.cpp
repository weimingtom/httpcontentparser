// GlobalChecker.cpp : CGlobalChecker 的实现

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

// DNS是否合法， 其结果保存在enabled当中
STDMETHODIMP CGlobalChecker::checkDNS(BSTR dns, VARIANT_BOOL* enabled) {
	*enabled = global_setting_.checkDNS(std::string((char*)_bstr_t(dns)));
	return S_OK;
}

// 注意：此函数只能对UTF8编码的数据进行正确处理
// 因此在调用它之前要确保传入的数据使用UTF8编码
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

// 由于图片的数据量可能较大
// 因此我们只对图片的规则进行验证，图片如何验证由Packetgrasper进行
// 这样可以避免大量数据的传输
STDMETHODIMP CGlobalChecker::checkImage(LONG type, LONG* action_code) {
	//如果不需要显示image直接返回，  注意一些小图片还是应该放过的
	if (global_setting_.showImage() == false) {
		*action_code = ACTION_IMAGE_CHECK_DENY;
	}

	// 是否应该检测相应的图片
	if (global_setting_.imageNeedCheck(type)) {
		*action_code = ACTION_IMAGE_CHECK_PASS;
	} else {
		// 如果不需要检测
		*action_code = ACTION_IMAGE_CHECK_ENABLE;
	}
	return S_OK;
}
