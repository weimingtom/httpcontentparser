#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__

#include ".\BufferCallCOM.h"
#include <webcontenttype.h>
#include <utility\BufferCaller.h>




class WebRecordConfig;
class HTTPPacket;

#define BUFFER_CALL_CNT 80

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
	const TCHAR * genRandomName(TCHAR * filename, const int bufsize, const int content_type);
	const TCHAR * generateImageName(TCHAR *fullpath, const int bufsize, const int content_type);
	const TCHAR * generatePageName(TCHAR *fullpath, const int bufsize, const int content_type);

	// COM Buffer Callers
	BufferCaller<WebContentRecordCaller, BUFFER_CALL_CNT> record_caller_;
	BufferCaller<WebContentCheckCaller, BUFFER_CALL_CNT> check_caller_;

	WebContentRecordCaller recorder_;
	WebContentCheckCaller checker_;

private:
	// ��ȡ�����·��
	TCHAR * GetImageDirectory();
	TCHAR * GetPageDirectory();

	TCHAR imageDir[MAX_PATH];
	TCHAR pagesDir[MAX_PATH];
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__