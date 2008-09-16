#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__

class HTTPPacket;


class HTTPContentHander {
public:
	HTTPContentHander();
	~HTTPContentHander();

	// ��������
	bool checkContent(HTTPPacket *packet);
private:
	// �������ֺ�ͼƬ
	bool checkImage(HTTPPacket *packet);
	bool checkText(HTTPPacket *packet);
	int saveImage(HTTPPacket *packet, const bool porn);
	int saveText(HTTPPacket * packet, const bool porn);
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__