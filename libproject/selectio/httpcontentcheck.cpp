#include "stdafx.h"
#include "httpcontentcheck.h"
#include ".\webrecordconfig.h"
#include <webcontenttype.h>
#include <utility/httppacket.h>
#include <sysutility.h>
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <assert.h>
#include <stdlib.h>
#include <io.h>
#include <memory>
#include <comdef.h>

#define IMAGE_LOW_LIMIT (1024 * 5)	//ͼ����½���5K
#define	TEXT_LOW_LIMIT  (1024)		// ��ҳ��������1K

/////////////////////////////////////////////
// class HTTPContentHander
HTTPContentHander::HTTPContentHander() {
	memset(installpath_, 0, sizeof(installpath_));
	//record_config_ = NULL;
}

HTTPContentHander::~HTTPContentHander() {
	//if (NULL != record_config_) {
	//	delete record_config_;
	//	record_config_ = NULL;
	//}
}

//===================================================================
// �Ƿ���
int HTTPContentHander::handleContent(HTTPPacket *packet) {
	if (false == needHandle(packet)) {
		return CONTENT_CHECK_UNKNOWN;
	}

	char * data = NULL;
	try {
		// ���仺����
		int sizeRead;
		data = new char[packet->getDataSize()];

		// ��������
		packet->read(data, packet->getDataSize(), sizeRead);

		const int check_result = checkContent(packet);

		saveContent(packet, check_result);

		delete data;
		data = NULL;

		return check_result;
	} catch (...) {
		if (NULL == data) {
			delete data;
			data = NULL;
		}
		// ��������쳣
		return CONTENT_CHECK_UNKNOWN;
	}
}

// �Ƿ���Ҫ����
bool HTTPContentHander::needHandle(HTTPPacket *packet) {
	if (packet->getDataSize() == 0) {
		return false;
	}

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
	
	if (packet->getDataSize() > IMAGE_LOW_LIMIT) {
		// �����ļ���
		char fullpath[MAX_PATH];
		generateImageName(fullpath, MAX_PATH, packet->getContentType());
		packet->achieve_data(fullpath);

		// ���ӵ������ļ�����
		addToRepostory(fullpath, packet, check_result);
	}
	return -1;
}

// ������Ҫ��ѹ������
int HTTPContentHander::saveText(HTTPPacket * packet, const int check_result) {
	assert (isText(packet->getContentType()) == true);

	if (packet->getDataSize() > TEXT_LOW_LIMIT) {
		// �����ļ���
		char fullpath[MAX_PATH];
		generatePageName(fullpath, MAX_PATH, packet->getContentType());
		packet->achieve_data(fullpath);

		// ���ӵ������ļ�����
		addToRepostory(fullpath, packet, check_result);
	}
	return -1;
}

// ��ӵ������ļ�����
void HTTPContentHander::addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result) {
	//assert (NULL != record_config_);
	//record_config_->addItem(fullpath, check_result, packet->getContentType());
}

// �����ļ����Ĺ���
const TCHAR * HTTPContentHander::genRandomName(TCHAR * filename, const int bufsize, const int content_type) {
	DWORD count = GetTickCount();
	srand((unsigned int)time(0));
	unsigned rd = rand();
	
	_sntprintf(filename, bufsize,  "%u-%u.%s", count, rd, getExt(content_type));
	return filename;
}

// ��������
const TCHAR * HTTPContentHander::generateImageName(TCHAR *fullpath, const int bufsize, const int content_type) {
	getInstallDir();

	TCHAR filename[MAX_PATH], dir[MAX_PATH];
	while (1) {
		genRandomName(filename, MAX_PATH, content_type);
		GetImageDirectory(dir, MAX_PATH, installpath_);
		_sntprintf(fullpath, bufsize,  "%s%s", dir, filename);

		if (_taccess(fullpath, 0) == -1)
			break;
	}
	return fullpath;
}


// ����һ����ҳ������
const TCHAR * HTTPContentHander::generatePageName(TCHAR *fullpath, const int bufsize, const int content_type) {
	getInstallDir();
	
	TCHAR filename[MAX_PATH], dir[MAX_PATH];
	while (1) {
		genRandomName(filename, MAX_PATH, content_type);
		GetPageDirectory(dir, MAX_PATH, installpath_);
		_sntprintf(fullpath, bufsize,  "%s%s", dir, filename);

		if (_taccess(fullpath, 0) == -1)
			break;
	}
	return fullpath;
}


// ��ȡ��װĿ¼·��
const TCHAR * HTTPContentHander::getInstallDir() {
	if (0 != _tcslen(installpath_)) {
		return installpath_;
	}

	try {
		AutoInitInScale _auto_com_init;
		BSTR retVal;
		IAppSetting * appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
		appSetting->GetInstallPath((BSTR*)&retVal);

		_bstr_t install_path(retVal);
		//assert (NULL == record_config_);

		//TCHAR config_name[MAX_PATH];
		//GetRecordConfigfile(config_name, MAX_PATH, install_path);
		//record_config_ = new WebRecordConfig(config_name);
		
		_tcsncpy(installpath_, (TCHAR*)install_path, MAX_PATH);
	} catch (_com_error &) {
	}

	return installpath_;
}