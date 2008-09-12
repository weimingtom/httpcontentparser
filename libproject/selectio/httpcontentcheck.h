#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__

class HTTPPacket;

// 此包负责所有的图片处理
// 首先检测是图片是否是黄色图片
// 而后根据用户设置保存图片内容
class ImageHandler {
public:
	ImageHandler();
	~ImageHandler();

	// 更具HTTPPacket 处理他
	void handle(HTTPPacket *packet);
private:
	
	// 保存图片内容
	void saveContent(HTTPPacket * packet);
};

// 与图片类词， 此类主要处理文字内容
// 并根据用户设定保存网页
class TextContentHander {
public:
	TextContentHander();
	~TextContentHander();

	int handle(HTTPPacket *packet);
private:
	bool isTextPacket(HTTPPacket *packet);
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__