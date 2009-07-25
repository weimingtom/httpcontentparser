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

// ��FILETIMEת��Ϊʱ����ʽ
std::string filetimeToString(const FILETIME &ft) {
	TCHAR str[MAX_PATH];
	_sntprintf(str, MAX_PATH, "%u-%u", ft.dwHighDateTime,  ft.dwLowDateTime);
	return std::string(str);
}

// ��ʱ��ת��ΪFILETIME��ʽ
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
		// ����Ƿ���һ�������FILETIME
		// ��ֻ��һ�����ԣ����Ƿ���쳣
		// ��������쳣�� ˵����������
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
// ��ȡ��װʱ��
//====================================
// ��ע����ȡ��װʱ��
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

	// ����
	return makeValidate(stringToFiletime(value));
}

boost::posix_time::ptime getInstallDateFromFile() {
	TCHAR path[MAX_PATH];
	GetFilePath(path, MAX_PATH);

	return makeValidate(getFileCreateTime(path));
}

// 4, ��windows�µ�һ���ļ��鿴��װʱ��
boost::posix_time::ptime getInstallDateFromWin() {
	TCHAR fullpath[MAX_PATH];
	GetFileRecordInstallDate(fullpath, MAX_PATH);
	return makeValidate(getFileCreateTime(fullpath)); 
}

//====================================
// ��֮��װʱ��
//====================================

// ����window�ļ������ļ��Ĵ���ʱ��
void setInstallDateInWin(const FILETIME &ft) {
	try {
		// ��ȡ�ļ�·��
		TCHAR fullpath[MAX_PATH], windowDir[MAX_PATH];
		GetWindowsDirectory(windowDir, MAX_PATH);
		_sntprintf(fullpath, MAX_PATH, "%s\\%s", windowDir, WINDOWS_FILE_TO_STORE_INSTALLDATE);

		// ����ļ�������ֱ�����ô���ʱ��
		HANDLE hFile = CreateFile(fullpath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,  NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN,  NULL);
		int a  = GetLastError();
		if (INVALID_HANDLE_VALUE != hFile) {
			SetFileTime(hFile, &ft, NULL, NULL);
			int a = GetLastError();
			// ���ļ�д������
			DWORD written =  _tcslen(WINDIR_INI_FILE_CONTENT);
			WriteFile(hFile, WINDIR_INI_FILE_CONTENT, written, &written, NULL);
			CloseHandle(hFile);
		}
	} catch (...) {
	}
}

// �����ļ��Ĵ���ʱ��
void setInstallDateFile(const FILETIME &ft) {
	try {
		// ����ʹ�ñ�ʡ���ļ�����Ϊ�����޷�����
		// ������ʹ��ʲô�ļ��أ�
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

// ����ע���Ĵ���ʱ��
void setInstallDataOnRegistry(const FILETIME &ft) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_WRITE,   &hKey);
	if (ERROR_FILE_NOT_FOUND == ret) {
		// ���û�м�ֵ�� �򴴽�
		ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR, &hKey);
		if (ret != ERROR_SUCCESS){
			return;
		}
	} else if (ERROR_SUCCESS != ret) {
		return;
	}

	// ����ʱ��
	std::string install_date = filetimeToString(ft);
	ret = RegSetValueEx( hKey, REG_SOFTWARE_INSTALLDATE , 0, REG_SZ, (const BYTE*)(LPCSTR)install_date.c_str(), (DWORD)install_date.length());
	if (ERROR_SUCCESS == ret) {
			RegCloseKey(hKey);
	}
}
};

// ��ȡ��װʱ��
boost::posix_time::ptime getInstallDataTime() {
	using namespace	boost::posix_time;
	// ��ȡ������װʱ��


	ptime pWin = internal_utility::getInstallDateFromWin();
	ptime pFile  = internal_utility::getInstallDateFromFile();
	ptime pReg = internal_utility::getInstallDateFromRegistry();

	// �µ�ʱ��С�������ϵ�ʱ��С
	// ʱ��Խ�ã�ʱ��ԽС
	return min(pWin, min(pReg, pFile));
}

//==========================================
//
// ��ȡ��װʱ��ķ�ʽ
// 1. ����װʱ�䱣�����ļ�����
// 2. ������ע�����
// 3. �鿴Ŀ¼�����ļ��Ĵ���ʱ��
// 4. ��windowĿ¼�´��һ���ļ����������ļ��Ĵ���ʱ��

// ��ȡ��װ������
unsigned int  getInstalledDays() {
	boost::posix_time::ptime cur = boost::posix_time::second_clock::local_time();
	boost::posix_time::ptime installtime = getInstallDataTime();

	boost::posix_time::time_duration td = cur - installtime;
	// ����Ǹ�����˵�����ڴ���
	if (td.is_negative()) {
		return INSTALL_DAYS_ERROR;
	} else {
		return static_cast<unsigned int>(td.hours() / 24);
	}
}
// ���ð�װʱ��
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