#include "StdAfx.h"
#include ".\httpcontentchecker.h"
#include ".\HTTPPacket.h"
#include <assert.h>

// 注意，需要同步处理
// 检查完毕后需要重置packet的读指针

// 这是一个无用的check,他通常用于未知的种类内容的分析
// 他永远都返回成功
class NoneChecker : public HttpContentChecker {
	virtual bool checkHTTPContent(const HTTPPacket *packet) {
		return true;
	}
};

// 这个类主要用于分析图片内容
class ImageChecker : public HttpContentChecker {
	virtual bool checkHTTPContent(const HTTPPacket *packet) {
		return true;
	}
};

// 主要用于分析文本内容
class TextChecker : public HttpContentChecker {
	virtual bool checkHTTPContent(const HTTPPacket *packet) {
		return true;
	}
};


//========================================================
// 根据HEADER的内容创建Checker
HttpContentChecker * HttpContentChecker::getChecker(const HTTP_RESPONSE_HEADER * header) {
	int content_type =  header->getContentType();
	switch(content_type) {
		case HTTP_RESPONSE_HEADER::CONTYPE_GIF:
		case HTTP_RESPONSE_HEADER::CONTYPE_JPG:
		case HTTP_RESPONSE_HEADER::CONTYPE_PNG:
			{	// 图像
				static ImageChecker checker;
				return &checker;
			}
			break;
		case HTTP_RESPONSE_HEADER::CONTYPE_HTML:
			{	// 文字
				static TextChecker checker;
				return &checker;
			}
			break;
		default:
			{	// 未知内容
				static NoneChecker checker;
				return &checker;
			}
	}
}

