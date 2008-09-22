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

// �����ļ����Ĺ���
const TCHAR * genRandomName(TCHAR * filename, const int bufsize, const int content_type) {
	DWORD count = GetTickCount();
	srand((unsigned int)time(0));
	unsigned rd = rand();
	
	_sntprintf(filename, bufsize,  "%u-%u.%s", count, rd, getExt(content_type));
	return filename;
}

// ��������
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
// �Ƿ���
int HTTPContentHander::handleContent(HTTPPacket *packet) {
	if (false == needHandle(packet)) {
		return CONTENT_CHECK_UNKNOWN;
	}

	try {
		// ���仺����
		int sizeRead;
		char * data = new char[packet->getDataSize()];

		// ��������
		packet->read(data, packet->getDataSize(), sizeRead);

		const int check_result = checkContent(packet);
		saveContent(packet, check_result);

		return check_result;
	} catch (...) {
		// ��������쳣
		return CONTENT_CHECK_PORN;
	}
}

// �Ƿ���Ҫ����
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

// ��������ǲ���Porned�ģ�����Ƿ���true, ���򷵻�false

// �����������Ƿ��ڰ��������У������������������򷵻�false
// ����Ƿ�Ӧ�ü��ͼƬ���ݣ������Ӧ�ã���ֱ�ӷ���
// ���ͼƬ���ݣ�����ȡ��ɫͼƬ���ɽ���
int HTTPContentHander::checkImage(HTTPPacket *packet) {
	
	return CONTENT_CHECK_UNKNOWN;
}

int HTTPContentHander::checkText(HTTPPacket *packet) {
	return CONTENT_CHECK_UNKNOWN;
}


//=======================================================================
// ���𱣴�����
int HTTPContentHander::saveImage(HTTPPacket *packet, const int check_result) {
	assert (isImage(packet->getContentType()) == true);
	
	// �����ļ���
	char fullpath[MAX_PATH];
	generateImageName(fullpath, MAX_PATH, packet->getContentType());
	packet->achieve_data(fullpath);

	// ���ӵ������ļ�����
	addToRepostory(fullpath, packet, check_result);
	return -1;
}

// ������Ҫ��ѹ������
int HTTPContentHander::saveText(HTTPPacket * packet, const int check_result) {
	assert (isText(packet->getContentType()) == true);
	
	// �����ļ���
	char fullpath[MAX_PATH];
	generatePageName(fullpath, MAX_PATH, packet->getContentType());
	packet->achieve_data(fullpath);

	// ���ӵ������ļ�����
	addToRepostory(fullpath, packet, check_result);
	return -1;
}

// ��ӵ������ļ�����
void HTTPContentHander::addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result) {
	record_config_.addItem(fullpath, check_result, packet->getContentType());
}