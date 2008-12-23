#ifndef _SETTING_CONTENT_CHECK_H__
#define _SETTING_CONTENT_CHECK_H__

class HTTPPacket;
class DNSSetting;

// 所有关于内容的checker都要通过他进行处理
// class ContentCheck会根据HTTPPacket的内容自动创建一个checker
// 对数据进行check

// 每一个checker应该能够得到全局的设置，并根据全局的设置进行检测
class ContentCheck {
public:
	static ContentCheck * getContentChecker(const HTTPPacket *packet, DNSSetting *globalSetting);
	~ContentCheck(void);

	// 检查包内容
	virtual bool check(HTTPPacket *packet) = 0;
protected:
	ContentCheck();
	DNSSetting *globalSetting_;
};

#endif  // _SETTING_CONTENT_CHECK_H__
