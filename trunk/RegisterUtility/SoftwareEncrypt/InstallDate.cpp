#include "StdAfx.h"
#include ".\installdate.h"
#include <app_constants.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <utility\strutility.h>
#include <utility\timeutility.h>
#include <boost/scope_exit.hpp>
#include <boost/exception.hpp>
#include <apputility.h>
#include <DebugOutput.h>

#define __SOFTWAREENCRYPT_INSTALLDATE__(FMT) _DEBUG_STREAM_TRC_("[Family007][SoftwareEncrypt][InstallDate]"<<FMT )

namespace software_encrypt {

namespace {

const FILETIME FT_ZERO = {0};
FILETIME getFileCreateTime(const TCHAR * filename) {
	FILETIME ft = {0};
	HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ,  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,  NULL);
	if (INVALID_HANDLE_VALUE != hFile) {
		GetFileTime(hFile, &ft, NULL, NULL);
		CloseHandle(hFile);
	}
	return ft;
}

// 将FILETIME转化为时间形式
std::string filetimeToString(const FILETIME &ft) {
	TCHAR str[MAX_PATH];
	_sntprintf(str, MAX_PATH, "%u-%u", ft.dwHighDateTime,  ft.dwLowDateTime);
	return std::string(str);
}

// 将时间转换为FILETIME形式
FILETIME stringToFiletime(const std::string &str) {
	FILETIME ft = {0};

	std::vector<std::string> vec;
	strutility::splitstring(str.c_str(), "-", &vec);

	if (vec.size() != 2) {
		return ft;
	}

	ft.dwHighDateTime = static_cast<DWORD>(atoi(vec[0].c_str()));
	ft.dwLowDateTime = static_cast<DWORD>(atoi( vec[1].c_str()));
	return ft;
}

bool operator==(const FILETIME &f1, const FILETIME &f2) {
	return (f1.dwHighDateTime == f2.dwHighDateTime) && (f1.dwLowDateTime == f2.dwLowDateTime);
}

boost::posix_time::ptime makeValidate(const FILETIME &ft) {
	if (FT_ZERO == ft) {
		return boost::posix_time::second_clock::local_time();
	} else {
		// 检测是否是一个合理的FILETIME
		// 这只是一个测试，看是否出异常
		// 如果出现异常， 说明存在问题
		SYSTEMTIME st;
		if (0 == FileTimeToSystemTime(&ft, &st)) {
			return boost::posix_time::second_clock::local_time();
		} else {
			return boost::posix_time::from_ftime<boost::posix_time::ptime>(ft);
		}
	}
}

const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len) {
	TCHAR dir[MAX_PATH], driver[MAX_PATH];
	_tsplitpath(filename, driver, dir, NULL, NULL);
	_sntprintf(directory, len, TEXT("%s%s"), driver, dir);
	return directory;
}

TCHAR * GetFilePath(TCHAR * path, const int max_len) {
	TCHAR module[MAX_PATH], dir[MAX_PATH];
	GetModuleFileName(NULL, module, MAX_PATH);
	GetFileNameDir(module, dir, MAX_PATH);
	_sntprintf(path, max_len, "%s%s", dir, INSTALL_DIR_DATE_INDICATOR);
	return path;
}

};

namespace internal_utility {

//====================================
// 获取安装时间
//====================================
// 从注册表获取安装时间
boost::posix_time::ptime getInstallDateFromRegistry() {
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

boost::posix_time::ptime getInstallDateFromFile() {
	TCHAR path[MAX_PATH];
	GetFilePath(path, MAX_PATH);

	return makeValidate(getFileCreateTime(path));
}

// 4, 从windows下的一个文件查看安装时间
boost::posix_time::ptime getInstallDateFromWin() {
	TCHAR fullpath[MAX_PATH];
	GetFileRecordInstallDate(fullpath, MAX_PATH);
	return makeValidate(getFileCreateTime(fullpath)); 
}

//====================================
// 从之安装时间
//====================================

// 设置window文件夹下文件的创建时间
void setInstallDateInWin(const FILETIME &ft) {
	try {
		// 获取文件路径
		TCHAR fullpath[MAX_PATH], windowDir[MAX_PATH];
		GetWindowsDirectory(windowDir, MAX_PATH);
		_sntprintf(fullpath, MAX_PATH, "%s\\%s", windowDir, WINDOWS_FILE_TO_STORE_INSTALLDATE);

		// 如果文件存在则直接设置创佳时间
		HANDLE hFile = CreateFile(fullpath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,  NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN,  NULL);
		int a  = GetLastError();
		if (INVALID_HANDLE_VALUE != hFile) {
			SetFileTime(hFile, &ft, NULL, NULL);
			int a = GetLastError();
			// 给文件写入内容
			DWORD written =  _tcslen(WINDIR_INI_FILE_CONTENT);
			WriteFile(hFile, WINDIR_INI_FILE_CONTENT, written, &written, NULL);
			CloseHandle(hFile);
		}
	} catch (...) {
	}
}

// 设置文件的创建时间
void setInstallDateFile(const FILETIME &ft) {
	try {
		// 不能使用本省的文件，因为它将无法访问
		// 其他的使用什么文件呢？
		TCHAR filename[MAX_PATH];
		GetFilePath(filename, MAX_PATH);

		SYSTEMTIME st;
		FileTimeToSystemTime(&ft, &st);
		HANDLE hFile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ,  NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,  NULL);
		if (INVALID_HANDLE_VALUE != hFile) {
			BOOL bFalse = SetFileTime(hFile, &ft, NULL, NULL);
			CloseHandle(hFile);
			return;
		}
	} catch(...) {
	}
}

// 设置注册表的创建时间
void setInstallDataOnRegistry(const FILETIME &ft) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_WRITE,   &hKey);
	if (ERROR_FILE_NOT_FOUND == ret) {
		// 如果没有键值， 则创建
		ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR, &hKey);
		if (ret != ERROR_SUCCESS){
			return;
		}
	} else if (ERROR_SUCCESS != ret) {
		return;
	}

	// 设置时间
	std::string install_date = filetimeToString(ft);
	ret = RegSetValueEx( hKey, REG_SOFTWARE_INSTALLDATE , 0, REG_SZ, (const BYTE*)(LPCSTR)install_date.c_str(), (DWORD)install_date.length());
	if (ERROR_SUCCESS == ret) {
			RegCloseKey(hKey);
	}
}
};

// 获取安装时间
boost::posix_time::ptime getInstallDataTime() {
	using namespace	boost::posix_time;
	// 获取三个安装时间


	ptime pWin = internal_utility::getInstallDateFromWin();
	ptime pFile  = internal_utility::getInstallDateFromFile();
	ptime pReg = internal_utility::getInstallDateFromRegistry();

	// 新的时间小，还是老的时间小
	// 时间越久，时间越小
	return min(pWin, min(pReg, pFile));
}

//==========================================
//
// 获取安装时间的方式
// 1. 将安装时间保存在文件当中
// 2. 保存在注册表当中
// 3. 查看目录或者文件的创建时间
// 4. 在window目录下存放一个文件，产看该文件的创建时间

// 获取安装的天数
unsigned int  getInstalledDays() {
	boost::posix_time::ptime cur = boost::posix_time::second_clock::local_time();
	boost::posix_time::ptime installtime = getInstallDataTime();

	boost::posix_time::time_duration td = cur - installtime;
	// 如果是负数，说明存在错误
	if (td.is_negative()) {
		return INSTALL_DAYS_ERROR;
	} else {
		return static_cast<unsigned int>(td.hours() / 24);
	}
}
// 设置安装时间
int setInstall() {
	using namespace boost::posix_time;
	boost::posix_time::ptime installtime = getInstallDataTime();
	FILETIME installFT = timeutility::ft_from_tm(to_tm(installtime));

	internal_utility::setInstallDataOnRegistry(installFT);
	internal_utility::setInstallDateInWin(installFT);
	internal_utility::setInstallDateFile(installFT);
	return 0;
}

std::string getInstallData() {
	boost::posix_time::ptime installtime = getInstallDataTime();
	return boost::posix_time::to_iso_string(installtime);
}

};