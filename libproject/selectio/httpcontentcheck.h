#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__

class HTTPPacket;

// �˰��������е�ͼƬ����
// ���ȼ����ͼƬ�Ƿ��ǻ�ɫͼƬ
// ��������û����ñ���ͼƬ����
class ImageHandler {
public:
	ImageHandler();
	~ImageHandler();

	// ����HTTPPacket ������
	void handle(HTTPPacket *packet);
private:
	
	// ����ͼƬ����
	void saveContent(HTTPPacket * packet);
};

// ��ͼƬ��ʣ� ������Ҫ������������
// �������û��趨������ҳ
class TextContentHander {
public:
	TextContentHander();
	~TextContentHander();

	int handle(HTTPPacket *packet);
private:
	bool isTextPacket(HTTPPacket *packet);
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__