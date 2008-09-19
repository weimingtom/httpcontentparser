#include "stdafx.h"
#include "httpcontentcheck.h"
#include <webcontenttype.h>
#include <utility/httppacket.h>
#include <sysutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <assert.h>

/////////////////////////////////////////////
// class HTTPContentHander
HTTPContentHander::HTTPContentHander() {
}

HTTPContentHander::~HTTPContentHander() {
}

//===================================================================
// 是否是
bool HTTPContentHander::checkContent(HTTPPacket *packet) {
	if (isImage(packet->getContentType()) == true) {
		const bool porned = checkImage(packet);
		saveImage(packet, porned);
		return porned;
	} else if (isText(packet->getContentType()) == true) {
		const bool porned = checkText(packet);
		saveText(packet, porned);
		return porned;
	}

	return false;
}

//=====================================================================
// member functions

// 检测内容是不是Porned的，如果是返回true, 否则返回false

// 首先他会检查是否在白名单当中，如果不在则继续，否则返回false
// 检测是否应该检查图片内容，如果不应该，则直接返回
// 检查图片内容，并获取黄色图片的松紧度
bool HTTPContentHander::checkImage(HTTPPacket *packet) {
	return false;
}
bool HTTPContentHander::checkText(HTTPPacket *packet) {
	return false;
}


//=======================================================================
// 负责保存内容
int HTTPContentHander::saveImage(HTTPPacket *packet, const bool porn) {
	assert (isImage(packet->getContentType()) == true);

	// 获取目录
	char directory[MAX_PATH];
	if (true == porn) {
		GetPornImageDirectory(directory, MAX_PATH);
	} else {
		GetImageDirectory(directory, MAX_PATH);
	}
	
	// 生成文件名
	char filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, "%s\\%s", directory, ""/*packet->getHeader()->*/);
	packet->achieve_data(filename);
	return -1;
}

int HTTPContentHander::saveText(HTTPPacket * packet, const bool porn) {
	assert (isText(packet->getContentType()) == true);

		// 获取目录
	char directory[MAX_PATH];
	if (true == porn) {
		GetPornImageDirectory(directory, MAX_PATH);
	} else {
		GetImageDirectory(directory, MAX_PATH);
	}
	
	// 生成文件名
	char filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, "%s\\%s", directory, ""/*packet->getHeader()->*/);
	packet->achieve_data(filename);
	return -1;
}