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

	// 处理内容
	int handleContent(HTTPPacket *packet);
private:
	// 是否需要处理
	bool needHandle(HTTPPacket *packet);
	// 处理文字和图片
	int checkContent(HTTPPacket *packet);
	int saveContent(HTTPPacket *packet, const int check_result);

	int checkImage(HTTPPacket *packet);
	int checkText(HTTPPacket *packet);
	int saveImage(HTTPPacket *packet, const int check_result);
	int saveText(HTTPPacket * packet, const int check_result);

	int savezip(HTTPPacket *packet, const char *filename);

	// 将他们的路径写入到配置文件当中
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
	// 获取保存的路径
	TCHAR * GetImageDirectory();
	TCHAR * GetPageDirectory();

	TCHAR imageDir[MAX_PATH];
	TCHAR pagesDir[MAX_PATH];
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__