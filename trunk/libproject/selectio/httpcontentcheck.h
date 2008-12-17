#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__


#include <webcontenttype.h>
class WebRecordConfig;
class HTTPPacket;


class HTTPContentHander {
public:
	HTTPContentHander();
	~HTTPContentHander();

	// ��������
	int handleContent(HTTPPacket *packet);
private:
	// �Ƿ���Ҫ����
	bool needHandle(HTTPPacket *packet);
	// �������ֺ�ͼƬ
	int checkContent(HTTPPacket *packet);
	int saveContent(HTTPPacket *packet, const int check_result);

	int checkImage(HTTPPacket *packet);
	int checkText(HTTPPacket *packet);
	int saveImage(HTTPPacket *packet, const int check_result);
	int saveText(HTTPPacket * packet, const int check_result);

	int savezip(HTTPPacket *packet, const char *filename);

	// �����ǵ�·��д�뵽�����ļ�����
	void addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result);

private:
	TCHAR installpath_[MAX_PATH];
private:
	const TCHAR * genRandomName(TCHAR * filename, const int bufsize, const int content_type);
	const TCHAR * generateImageName(TCHAR *fullpath, const int bufsize, const int content_type);
	const TCHAR * generatePageName(TCHAR *fullpath, const int bufsize, const int content_type);
	const TCHAR * getInstallDir();
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__