#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__

class HTTPPacket;


class HTTPContentHander {
public:
	HTTPContentHander();
	~HTTPContentHander();

	// 处理内容
	bool checkContent(HTTPPacket *packet);
private:
	// 处理文字和图片
	bool checkImage(HTTPPacket *packet);
	bool checkText(HTTPPacket *packet);
	int saveImage(HTTPPacket *packet, const bool porn);
	int saveText(HTTPPacket * packet, const bool porn);
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__