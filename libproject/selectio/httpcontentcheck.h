#ifndef _SELECTIO_HTTPCONETENTCHECK_H__
#define _SELECTIO_HTTPCONETENTCHECK_H__


#include <webcontenttype.h>
#include ".\webrecordconfig.h"
class HTTPPacket;


class HTTPContentHander {
public:
	HTTPContentHander();
	~HTTPContentHander();

	// 处理内容
	int handleContent(HTTPPacket *packet);
private:
	// 是否需要处理
	int needHandle(HTTPPacket *packet);
	// 处理文字和图片
	int checkContent(HTTPPacket *packet);
	int saveContent(HTTPPacket *packet, const int check_result);

	int checkImage(HTTPPacket *packet);
	int checkText(HTTPPacket *packet);
	int saveImage(HTTPPacket *packet, const int check_result);
	int saveText(HTTPPacket * packet, const int check_result);

	// 将他们的路径写入到配置文件当中
	void addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result);

private:
	WebRecordConfig record_config_;
};


#endif  // _SELECTIO_HTTPCONETENTCHECK_H__