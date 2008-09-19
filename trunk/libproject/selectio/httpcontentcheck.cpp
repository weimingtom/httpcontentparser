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
// �Ƿ���
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

// ��������ǲ���Porned�ģ�����Ƿ���true, ���򷵻�false

// �����������Ƿ��ڰ��������У������������������򷵻�false
// ����Ƿ�Ӧ�ü��ͼƬ���ݣ������Ӧ�ã���ֱ�ӷ���
// ���ͼƬ���ݣ�����ȡ��ɫͼƬ���ɽ���
bool HTTPContentHander::checkImage(HTTPPacket *packet) {
	return false;
}
bool HTTPContentHander::checkText(HTTPPacket *packet) {
	return false;
}


//=======================================================================
// ���𱣴�����
int HTTPContentHander::saveImage(HTTPPacket *packet, const bool porn) {
	assert (isImage(packet->getContentType()) == true);

	// ��ȡĿ¼
	char directory[MAX_PATH];
	if (true == porn) {
		GetPornImageDirectory(directory, MAX_PATH);
	} else {
		GetImageDirectory(directory, MAX_PATH);
	}
	
	// �����ļ���
	char filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, "%s\\%s", directory, ""/*packet->getHeader()->*/);
	packet->achieve_data(filename);
	return -1;
}

int HTTPContentHander::saveText(HTTPPacket * packet, const bool porn) {
	assert (isText(packet->getContentType()) == true);

		// ��ȡĿ¼
	char directory[MAX_PATH];
	if (true == porn) {
		GetPornImageDirectory(directory, MAX_PATH);
	} else {
		GetImageDirectory(directory, MAX_PATH);
	}
	
	// �����ļ���
	char filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, "%s\\%s", directory, ""/*packet->getHeader()->*/);
	packet->achieve_data(filename);
	return -1;
}