#include "StdAfx.h"
#include ".\contentcheck.h"
#include ".\globalsetting.h"
#include <utility\HTTPPacket.h>
#include <zlib\zlib.h>

// 以下是各个checker
// 首先根据各种类型的checker进行检测是否需要检查
// 如果需要则进行检测否则之间返回对应的值
class ImageChecker : public ContentCheck {
public:
	ImageChecker(GlobalSetting *globalSetting);
	virtual bool check(HTTPPacket *packet);
private:
	bool checkImage();

	ImageChecker(){}
};

class HTMLChecker : public ContentCheck {
public:
	HTMLChecker(GlobalSetting *globalSetting);
	virtual bool check(HTTPPacket *packet);
protected:
	bool contentText(const char *buf, const int buf_len);

	typedef std::set<std::string> WORD_SET;
	WORD_SET black_words_;

private:
	HTMLChecker(){}
};

class UnknowChecker : public ContentCheck {
public:
	UnknowChecker(GlobalSetting *globalSetting);
	virtual bool check(HTTPPacket *packet);
private:
	UnknowChecker(){}
};


//==================================
// class ContentCheck
ContentCheck::ContentCheck(void) {
}

ContentCheck::~ContentCheck(void) {
}

ContentCheck * ContentCheck::getContentChecker(const HTTPPacket *packet, GlobalSetting *globalSetting) {
	switch (packet->getContentType()) {
		case HTTP_RESPONSE_HEADER::CONTYPE_GIF:
		case HTTP_RESPONSE_HEADER::CONTYPE_JPG:
		case HTTP_RESPONSE_HEADER::CONTYPE_PNG:
			{
				static ImageChecker checker(globalSetting);
				return &checker;
			}
		case HTTP_RESPONSE_HEADER::CONTYPE_HTML:
			{
				static HTMLChecker checker(globalSetting);
				return &checker;
			}
		default:
			{
				static UnknowChecker checker(globalSetting);
				return &checker;
			}
	}
}
//===============================
// class ImageChecker
ImageChecker::ImageChecker(GlobalSetting *globalSetting) {
	globalSetting_ = globalSetting;
}

bool ImageChecker::checkImage() {
	return true;
}

bool ImageChecker::check(HTTPPacket *packet) {
	if (globalSetting_->showImage() == false)
		return false;

	if (globalSetting_->imageNeedCheck(packet->getContentType())) {
		return checkImage();
	}
	return true;
}

//===============================
// class HTMLChecker
HTMLChecker::HTMLChecker() {
}

bool HTMLChecker::check(HTTPPacket *packet) {
	return true;
}

//===============================
// class UnknowChecker
UnknowChecker::UnknowChecker(GlobalSetting *globalSetting) {
	globalSetting_ = globalSetting;
}
bool UnknowChecker::check(HTTPPacket *packet) {
	return true;
}
