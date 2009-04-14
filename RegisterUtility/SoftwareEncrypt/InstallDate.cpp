#include "StdAfx.h"
#include ".\installdate.h"
#include <app_constants.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

namespace {
	const FILETIME FT_ZERO = {0};
	FILETIME getFileCreateTime(const TCHAR * filename) {
		FILETIME ft = {0};
		HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ,  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,  NULL);
		if (INVALID_HANDLE_VALUE != hFile) {
			GetFileTime(hFile, &ft, NULL, NULL);
		}
		return ft;
	}

	// 将FILETIME转化为时间形式
	std::string filetimeToString(const FILETIME &ft) {
		TCHAR str[MAX_PATH], buffer[MAX_PATH];
		_sntprintf(str, MAX_PATH, "%s-%s", _ltoa(ft.dwHighDateTime, buffer, 10),  _ltoa(ft.dwLowDateTime, buffer, 10));
		return std::string(str);
	}

	// 将时间转换为FILETIME形式
	FILETIME stringToFiletime(const std::string &str) {
		FILETIME ft = {0};
		int index = str.find('-');

		// 如果找不到， 说明是一个错误的格式
		if (index == -1) {
			return ft;
		}

		TCHAR buffer[MAX_PATH] = {0};
		_tcsncpy(buffer, str.c_str(), index+1);
		ft.dwHighDateTime = static_cast<DWORD>(atoi(buffer));

		memset(buffer, 0, sizeof(buffer));
		_tcsncpy(buffer, str.c_str()+index+1, str.length() - index -1);
		ft.dwLowDateTime = static_cast<DWORD>(atoi(buffer));

		return ft;
	}

	bool operator==(const FILETIME &f1, const FILETIME &f2) {
		return (f1.dwHighDateTime == f2.dwHighDateTime) && (f1.dwLowDateTime == f2.dwLowDateTime);
	}

	boost::posix_time::ptime makeValidate(const FILETIME &ft) {
		if (FT_ZERO == ft) {
			return boost::posix_time::second_clock::local_time();
		} else {
			return boost::posix_time::from_ftime<boost::posix_time::ptime>(ft);
		}
	}
};

// 获取安装时间的方式
// 1. 将安装时间保存在文件当中
// 2. 保存在注册表当中
// 3. 查看目录或者文件的创建时间
// 4. 在window目录下存放一个文件，产看该文件的创建时间
InstallDate::InstallDate(void) {
}

InstallDate::~InstallDate(void) {
}

// 设置安装时间
int InstallDate::setInstall() {
	return 0;
}

// 从注册表获取安装时间
boost::posix_time::ptime InstallDate::getInstallDateFromRegistry() {
	FILETIME ft = {0};
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_READ,   &hKey);
	if (ERROR_SUCCESS != ret)
		return makeValidate(FT_ZERO);

	TCHAR value[MAX_PATH] = {0};
	DWORD length = MAX_PATH;
	DWORD type = REG_SZ;
	LONG result = RegQueryValueEx (hKey, REG_SOFTWARE_INSTALLDATE, NULL, &type, (LPBYTE)value, &length);
	RegCloseKey(hKey);

	// 解析
	return makeValidate(stringToFiletime(value));
}

boost::posix_time::ptime InstallDate::getInstallDateFromFile() {
	TCHAR filename[MAX_PATH];
	
	GetModuleFileName(NULL, filename, MAX_PATH);
	return makeValidate(getFileCreateTime(filename));
}

// 4, 从windows下的一个文件查看安装时间
boost::posix_time::ptime InstallDate::getInstallDateFromWin() {
	TCHAR fullpath[MAX_PATH], windowDir[MAX_PATH];
	GetWindowsDirectory(windowDir, MAX_PATH);
	_sntprintf(fullpath, MAX_PATH, "%s%s", windowDir, WINDOWS_FILE_TO_STORE_INSTALLDATE);

	return makeValidate(getFileCreateTime(fullpath)); 
}

// 获取安装时间
boost::posix_time::ptime InstallDate::getInstallDataTime() {
	using namespace	boost::posix_time;
	// 获取三个安装时间

	ptime pWin = getInstallDateFromWin();
	ptime pReg = getInstallDateFromRegistry();
	ptime pFile  = getInstallDateFromFile();


	return min(pWin, min(pReg, pFile));
}