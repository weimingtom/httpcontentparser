#include "stdafx.h"
#include "httpcontentcheck.h"
#include <webcontenttype.h>
#include <utility/httppacket.h>
#include <sysutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <assert.h>
#include <stdlib.h>
#include <io.h>
#include <memory>

namespace {

// 生成文件名的规则
const TCHAR * genRandomName(TCHAR * filename, const int bufsize, const int content_type) {
	DWORD count = GetTickCount();
	srand((unsigned int)time(0));
	unsigned rd = rand();
	
	_sntprintf(filename, bufsize,  "%u-%u.%s", count, rd, getExt(content_type));
	return filename;
}

// 生成名字
const TCHAR * generateImageName(TCHAR *fullpath, const int bufsize, const int content_type) {
	TCHAR filename[MAX_PATH], dir[MAX_PATH];
	while (1) {
		genRandomName(filename, MAX_PATH, content_type);
		GetImageDirectory(dir, MAX_PATH);
		_sntprintf(fullpath, bufsize,  "%s%s", dir, filename);

		if (_taccess(fullpath, 0) == 0)
			break;
	}
	return fullpath;
}
const TCHAR * generatePageName(TCHAR *fullpath, const int bufsize, const int content_type) {
	TCHAR filename[MAX_PATH], dir[MAX_PATH];
	while (1) {
		genRandomName(filename, MAX_PATH, content_type);
		GetPageDirectory(dir, MAX_PATH);
		_sntprintf(fullpath, bufsize,  "%s%s", dir, filename);

		if (_taccess(fullpath, 0) == 0)
			break;
	}
	return fullpath;
}

};

/////////////////////////////////////////////
// class HTTPContentHander
HTTPContentHander::HTTPContentHander() {
}

HTTPContentHander::~HTTPContentHander() {
}

//===================================================================
// 是否是
int HTTPContentHander::handleContent(HTTPPacket *packet) {
	if (false == needHandle(packet)) {
		return CONTENT_CHECK_UNKNOWN;
	}

	try {
		// 分配缓冲区
		int sizeRead;
		char * data = new char[packet->getDataSize()];

		// 读入数据
		packet->read(data, packet->getDataSize(), sizeRead);

		const int check_result = checkContent(packet);
		saveContent(packet, check_result);

		return check_result;
	} catch (...) {
		// 如果出现异常
		return CONTENT_CHECK_PORN;
	}
}

// 是否需要处理
bool needHandle(HTTPPacket *packet) {
	if (isImage(packet->getContentType()) ||
		isText(packet->getContentType()) ) {
		return true;
	} else {
		return false;
	}
}

int HTTPContentHander::saveContent(HTTPPacket *packet, const int check_result) {
	if (isImage(packet->getContentType()) == true) {
		return saveImage(packet, check_result);
	} else if (isText(packet->getContentType()) == true) {
		return saveText(packet, check_result);
	}
	return check_result;
}

int HTTPContentHander::checkContent(HTTPPacket *packet) {
	if (isImage(packet->getContentType()) == true) {
		return checkImage(packet);;
	} else if (isText(packet->getContentType()) == true) {
		return checkText(packet);
	}

	return CONTENT_CHECK_UNKNOWN;
}
//=====================================================================
// member functions

// 检测内容是不是Porned的，如果是返回true, 否则返回false

// 首先他会检查是否在白名单当中，如果不在则继续，否则返回false
// 检测是否应该检查图片内容，如果不应该，则直接返回
// 检查图片内容，并获取黄色图片的松紧度
int HTTPContentHander::checkImage(HTTPPacket *packet) {
	
	return CONTENT_CHECK_UNKNOWN;
}

int HTTPContentHander::checkText(HTTPPacket *packet) {
	return CONTENT_CHECK_UNKNOWN;
}


//=======================================================================
// 负责保存内容
int HTTPContentHander::saveImage(HTTPPacket *packet, const int check_result) {
	assert (isImage(packet->getContentType()) == true);
	
	// 生成文件名
	char fullpath[MAX_PATH];
	generateImageName(fullpath, MAX_PATH, packet->getContentType());
	packet->achieve_data(fullpath);

	// 增加到配置文件当中
	addToRepostory(fullpath, packet, check_result);
	return -1;
}

// 可能需要解压缩保存
int HTTPContentHander::saveText(HTTPPacket * packet, const int check_result) {
	assert (isText(packet->getContentType()) == true);
	
	// 生成文件名
	char fullpath[MAX_PATH];
	generatePageName(fullpath, MAX_PATH, packet->getContentType());
	packet->achieve_data(fullpath);

	// 增加到配置文件当中
	addToRepostory(fullpath, packet, check_result);
	return -1;
}

// 添加到配置文件当中
void HTTPContentHander::addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result) {
	record_config_.addItem(fullpath, check_result, packet->getContentType());
}