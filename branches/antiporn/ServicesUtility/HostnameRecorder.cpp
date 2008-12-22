#include "StdAfx.h"
#include ".\hostnamerecorder.h"
#include <fstream>
#include <sysutility.h>
#include <comdef.h>
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>

HostnameRecorder::HostnameRecorder(void) {
	memset(install_path, 0, sizeof(install_path));
}

HostnameRecorder::~HostnameRecorder(void) {
}


void HostnameRecorder::add(std::string &hostname) {
	host_name.insert(hostname);
	if (host_name.size() > HOSTNAME_RECORD_BUFFER_SIZE) {
		flush();	
	}
}

void HostnameRecorder::getInstallPath() {
	try {
		if (_tcslen(install_path) == 0) {
			AutoInitInScale _auto_com_init;
			// 获取安装路径
			BSTR retVal;
			IAppSetting * appSetting = NULL;
			HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
			appSetting->GetInstallPath((BSTR*)&retVal);
			_bstr_t bstrpath(retVal);
			_tcsncpy(install_path, (TCHAR*)bstrpath, MAX_PATH);
		}
	} catch(...) {
		memset(install_path, 0, sizeof(install_path));
	}
}

void HostnameRecorder::flush() {
	try {
		using namespace std;
		// 获取文件名
		TCHAR filename[MAX_PATH] = {0};

		// 获取文件路径
		getInstallPath();
		GetWebSiteRecordPath(filename, MAX_PATH, install_path);

		fstream out;
		out.open(filename, std::ios::out | std::ios::app );

		// 写入文件
		HOSTNAME_SET::iterator iter = host_name.begin();
		for (; iter != host_name.end(); ++iter) {
			out.write(iter->c_str(), (std::streamsize)iter->length());
			out.write("\r\n", (std::streamsize)strlen("\r\n"));
		}
		out.close();
		host_name.clear();
	} catch (...) {
	}
}