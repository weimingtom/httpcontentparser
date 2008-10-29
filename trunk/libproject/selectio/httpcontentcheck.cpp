#include "stdafx.h"
#include "httpcontentcheck.h"
#include ".\webrecordconfig.h"
#include <webcontenttype.h>
#include <utility/httppacket.h>
#include <utility/ZipUtility.h>
#include <utility/BufferOnStackHeap.h>
#include <sysutility.h>
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <assert.h>
#include <stdlib.h>
#include <io.h>
#include <memory>
#include <comdef.h>
#include <fstream>

#define IMAGE_LOW_LIMIT (1024 * 5)	//图像的下届是5K
#define	TEXT_LOW_LIMIT  (1024)		// 网页的下限是1K

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
// 是否是
int HTTPContentHander::handleContent(HTTPPacket *packet) {
	if (false == needHandle(packet)) {
		return CONTENT_CHECK_UNKNOWN;
	}

	char * data = NULL;
	try {
		// 分配缓冲区
		int sizeRead;
		data = new char[packet->getDataSize()];

		// 读入数据
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
		// 如果出现异常
		return CONTENT_CHECK_UNKNOWN;
	}
}

// 是否需要处理
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
	
	if (packet->getDataSize() > IMAGE_LOW_LIMIT) {
		// 生成文件名
		char fullpath[MAX_PATH];
		generateImageName(fullpath, MAX_PATH, packet->getContentType());
		packet->achieve_data(fullpath);

		// 增加到配置文件当中
		addToRepostory(fullpath, packet, check_result);
	}
	return -1;
}

// 可能需要解压缩保存
int HTTPContentHander::saveText(HTTPPacket * packet, const int check_result) {
	assert (isText(packet->getContentType()) == true);

	if (packet->getDataSize() > TEXT_LOW_LIMIT) {
		// 生成文件名
		char fullpath[MAX_PATH];
		generatePageName(fullpath, MAX_PATH, packet->getContentType());

		// 如果未压缩则直接保存
		if (HTTP_RESPONSE_HEADER::CONTENCODING_GZIP != packet->getHeader()->getContentEncoding()) {
			packet->achieve_data(fullpath);
		} else {
			// 否则需要解压缩保存
			savezip(packet, fullpath);
		}

		// 增加到配置文件当中
		addToRepostory(fullpath, packet, check_result);
	}
	return -1;
}

int HTTPContentHander::savezip(HTTPPacket *packet, const char *filename) {
	// 读取数据
	BufferOnStackHeap<1024 * 8> buffer_on_stack_or_heap;
	char * active_buffer = buffer_on_stack_or_heap.get_buffer();

	// 将数据读入缓冲区
	// 读取数据，并移动指针
	ProtocolPacket<HTTP_PACKET_SIZE> * data = packet->getData();
	data->read(active_buffer, packet->getDataSize());
	data->seek_read(0);

	// 解压缩
	ZipUtility<1024 * 36> zip;
	zip.uncompress((Bytef*)active_buffer, packet->getDataSize());

	// 保存在文件当中
	std::fstream f;
	f.open(filename, std::ios::out | std::ios::app | std::ios::binary);
	f.write((char*)zip.get_buffer(), zip.get_data_size());
	f.close();

	// 释放缓冲区
	return 0;
}

// 添加到配置文件当中
void HTTPContentHander::addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result) {
	//assert (NULL != record_config_);
	//record_config_->addItem(fullpath, check_result, packet->getContentType());
}

// 生成文件名的规则
const TCHAR * HTTPContentHander::genRandomName(TCHAR * filename, const int bufsize, const int content_type) {
	DWORD count = GetTickCount();
	srand((unsigned int)time(0));
	unsigned rd = rand();
	
	_sntprintf(filename, bufsize,  "%u-%u.%s", count, rd, getExt(content_type));
	return filename;
}

// 生成名字
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


// 产生一个网页的名称
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


// 获取安装目录路径
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