#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__


#include <webcontenttype.h>
#include ".\webrecordconfig.h"
class HTTPPacket;


class HTTPContentHander {
public:
	HTTPContentHander();
	~HTTPContentHander();

	// ��������
	int handleContent(HTTPPacket *packet);
private:
	// �Ƿ���Ҫ����
	int needHandle(HTTPPacket *packet);
	// �������ֺ�ͼƬ
	int checkContent(HTTPPacket *packet);
	int saveContent(HTTPPacket *packet, const int check_result);

	int checkImage(HTTPPacket *packet);
	int checkText(HTTPPacket *packet);
	int saveImage(HTTPPacket *packet, const int check_result);
	int saveText(HTTPPacket * packet, const int check_result);

	// �����ǵ�·��д�뵽�����ļ�����
	void addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result);

private:
	WebRecordConfig record_config_;
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__