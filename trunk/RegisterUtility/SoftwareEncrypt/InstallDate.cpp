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

namespace software_encrypt {

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
		if (ft.dwHighDateTime >= 0x800000000) {
			return boost::posix_time::from_ftime<boost::posix_time::ptime>(ft);
		} else {
			return boost::posix_time::second_clock::local_time();
		}
	}
}
};

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
	TCHAR filename[MAX_PATH];

	GetModuleFileName(NULL, filename, MAX_PATH);
	return makeValidate(getFileCreateTime(filename));
}

// 4, 从windows下的一个文件查看安装时间
boost::posix_time::ptime getInstallDateFromWin() {
	TCHAR fullpath[MAX_PATH], windowDir[MAX_PATH];
	GetWindowsDirectory(windowDir, MAX_PATH);
	_sntprintf(fullpath, MAX_PATH, "%s%s", windowDir, WINDOWS_FILE_TO_STORE_INSTALLDATE);

	return makeValidate(getFileCreateTime(fullpath)); 
}

// 获取安装时间
boost::posix_time::ptime getInstallDataTime() {
	using namespace	boost::posix_time;
	// 获取三个安装时间


	ptime pWin = getInstallDateFromWin();
	ptime pFile  = getInstallDateFromFile();
	ptime pReg = getInstallDateFromRegistry();

	// 如果获取到的时间不合法怎么办
	/*try {
	using namespace std;
	cout<<"windows file :"<<to_iso_string(pWin)<<endl;
	cout<<"registry date: "<< to_iso_string(pReg)<<endl;
	cout<<"current file date: "<< to_iso_string(pFile)<<endl;
	} catch (boost::exception &e) {
	}*/

	// 新的时间小，还是老的时间小
	// 时间越久，时间越小
	return min(pWin, min(pReg, pFile));
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
		_sntprintf(fullpath, MAX_PATH, "%s%s", windowDir, WINDOWS_FILE_TO_STORE_INSTALLDATE);

		// 如果文件存在则直接设置创佳时间
		HANDLE hFile = CreateFile(fullpath, GENERIC_READ, FILE_SHARE_READ,  NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_HIDDEN,  NULL);
		if (INVALID_HANDLE_VALUE != hFile) {
			SetFileTime(hFile, &ft, NULL, NULL);

			// 给文件写入内容
			DWORD written =  _tcslen(WINDIR_INI_FILE_CONTENT);
			WriteFile(hFile, WINDIR_INI_FILE_CONTENT, written, &written, NULL);
		}
	} catch (...) {
	}
}

// 设置文件的创建时间
void setInstallDateFile(const FILETIME &ft) {
	try {
		TCHAR filename[MAX_PATH];
		GetModuleFileName(NULL, filename, MAX_PATH);

		HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ,  NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_HIDDEN,  NULL);
		if (INVALID_HANDLE_VALUE != hFile) {
			SetFileTime(hFile, &ft, NULL, NULL);
		}
	} catch(...) {
	}
}

// 设置注册表的创建时间
void setInstallDataOnRegistry(const FILETIME &ft) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_READ,   &hKey);
	if (ERROR_FILE_NOT_FOUND == ret) {
		// 如果没有键值， 则创建
		ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, REG_SOFTWARE_INSTALLDATE, &hKey);
		if (ret != ERROR_SUCCESS){
			return;
		}
	} else if (ERROR_SUCCESS != ret) {
		return;
	}

	// 设置时间
	std::string install_date = filetimeToString(ft);
	if (ERROR_SUCCESS == RegSetValueEx( hKey, REG_SOFTWARE_INSTALLDATE , 0, REG_SZ,
		(const BYTE*)(LPCSTR)install_date.c_str(), (DWORD)install_date.length())) {
			RegCloseKey(hKey);
		}
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

	setInstallDataOnRegistry(installFT);
	setInstallDateInWin(installFT);
	setInstallDateFile(installFT);
	return 0;
}

std::string getInstallData() {
	boost::posix_time::ptime installtime = getInstallDataTime();
	return boost::posix_time::to_iso_string(installtime);
}

};