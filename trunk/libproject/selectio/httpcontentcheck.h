#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__


#include <webcontenttype.h>
class WebRecordConfig;
class HTTPPacket;


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
	TCHAR installpath_[MAX_PATH];
private:
	const TCHAR * genRandomName(TCHAR * filename, const int bufsize, const int content_type);
	const TCHAR * generateImageName(TCHAR *fullpath, const int bufsize, const int content_type);
	const TCHAR * generatePageName(TCHAR *fullpath, const int bufsize, const int content_type);
	const TCHAR * getInstallDir();
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__