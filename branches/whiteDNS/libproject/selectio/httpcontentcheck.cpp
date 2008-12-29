#include "stdafx.h"
#include "httpcontentcheck.h"
#include ".\webrecordconfig.h"
#include <webcontenttype.h>
#include <utility/httppacket.h>
#include <utility/ZipUtility.h>
#include <utility/BufferOnStackHeap.h>
#include <antiporn/antiporndll.h>
#include <sysutility.h>
#include <assert.h>
#include <stdlib.h>
#include <io.h>
#include <memory>
#include <comdef.h>
#include <fstream>

#define IMAGE_LOW_LIMIT (1024 * 10)	//图像的下届是5K
#define	TEXT_LOW_LIMIT  (1024 * 2)		// 网页的下限是1K

/////////////////////////////////////////////
// class HTTPContentHander
HTTPContentHander::HTTPContentHander() {
	memset(installpath_, 0, sizeof(installpath_));
}

HTTPContentHander::~HTTPContentHander() {
}

//===================================================================
// 是否是
int HTTPContentHander::handleContent(HTTPPacket *packet) {
	if (false == needHandle(packet)) {
		OutputDebugString("handleContent needless");
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
	record_caller_.Call(recorder_);
	check_caller_.Call(checker_);

	if (isImage(packet->getContentType())  && recorder_.shouldRecord(check_result, packet->getContentType())) {
		return saveImage(packet, check_result);
	} else if (isText(packet->getContentType()) && recorder_.shouldRecord(check_result, packet->getContentType())) {
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
	if (packet->getDataSize() < 2048) {
		return CONTENT_CHECK_NORMAL;
	}
	if (false == checker_.shouldCheck(packet)) {
		return CONTENT_CHECK_UNKNOWN;
	}

	// 随机生成一个文件名
	GUID   m_guid;
	TCHAR filename[1024];
	if(SUCCEEDED(CoCreateGuid(&m_guid))) {
		_sntprintf(filename, 1024, ".\\%08X-%04X-%04x", m_guid.Data1, m_guid.Data2, m_guid.Data3);
	} else {
		return CONTENT_CHECK_UNKNOWN;
	}

	// 保存文件先
	packet->achieve_data(filename);

	// check Data
	PornDetectorBase* pPornDetector = NULL;
	if (!CreateObject(&pPornDetector)) {
		return CONTENT_CHECK_UNKNOWN;
	}

	double score;
	bool flag = pPornDetector->Detection(filename, &score);
	DeleteObject();

	if (score > 0.0f) {
		OutputDebugString("block---------------");
		return CONTENT_CHECK_PORN;
	} else {
		return CONTENT_CHECK_NORMAL;
	}

	//if (score < checker_.getImageVScore()) {
	//	return CONTENT_CHECK_PORN;
	//} else {
	//	return CONTENT_CHECK_NORMAL;
	//}
	// 删除文件
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
		TCHAR content_file_path[MAX_PATH];
		generateImageName(content_file_path, MAX_PATH, packet->getContentType());
		packet->achieve_data(content_file_path);

		// 增加到配置文件当中
		addToRepostory(content_file_path, packet, check_result);
	}
	return -1;
}

// 可能需要解压缩保存
int HTTPContentHander::saveText(HTTPPacket * packet, const int check_result) {
	assert (isText(packet->getContentType()) == true);

	if (packet->getDataSize() > TEXT_LOW_LIMIT) {
		// 生成文件名
		TCHAR content_file_path[MAX_PATH];
		generatePageName(content_file_path, MAX_PATH, packet->getContentType());

		// 如果未压缩则直接保存
		if (HTTP_RESPONSE_HEADER::CONTENCODING_GZIP != packet->getHeader()->getContentEncoding()) {
			packet->achieve_data(content_file_path);
		} else {
			// 否则需要解压缩保存
			savezip(packet, content_file_path);
		}

		// 增加到配置文件当中
		addToRepostory(content_file_path, packet, check_result);
	}
	return -1;
}

int HTTPContentHander::savezip(HTTPPacket *packet, const char *filename) {
	const int buf_size = 1024 * 16; 
	char buffer[buf_size];
	//  首先将文件保存到一个临时文件当中
	char tmp_file[MAX_PATH];
	sprintf(tmp_file, "%s.tmp", filename);
	packet->achieve_data(tmp_file);
	
	// 打开文件
	gzFile  gzfile = gzopen (tmp_file, "rb"	);
	if (Z_NULL == gzfile) {
		return -1;
	}
	
	// 保存在文件当中
	std::fstream f;
	f.open(filename, std::ios::out | std::ios::app | std::ios::binary);

	int length = 0;
	while (0 < (length = gzread (gzfile, buffer, buf_size))) {
		f.write(buffer, length);
	}

	f.close();

	// 释放缓冲区
	gzclose(gzfile);

	// 删除临时文件
	DeleteFile(tmp_file);
	return 0;
}

// 添加到配置文件当中
void HTTPContentHander::addToRepostory(const TCHAR *fullpath, HTTPPacket * packet, const int check_result) {
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
		_tcsncpy(installpath_, (TCHAR*)install_path, MAX_PATH);
	} catch (_com_error &) {
	}

	return installpath_;
}