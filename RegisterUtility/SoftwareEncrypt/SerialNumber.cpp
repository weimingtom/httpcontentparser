#include "stdafx.h"
#include "serialNumber.h"
#include <app_constants.h>

namespace software_encrypt {
namespace {

std::string getSNFromRegistry() {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_READ,   &hKey);
	if (ERROR_SUCCESS != ret)
		return std::string("");

	TCHAR value[MAX_PATH] = {0};
	DWORD length = MAX_PATH;
	DWORD type = REG_SZ;
	LONG result = RegQueryValueEx (hKey, REG_SOFTWARE_PRODUCTSN, NULL, &type, (LPBYTE)value, &length);
	RegCloseKey(hKey);

	// 解析
	return std::string(value);
}

//================================
// 存储SN

void storeSNtoRegistry(const std::string &sn) {
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

	if (ERROR_SUCCESS == RegSetValueEx( hKey, REG_SOFTWARE_PRODUCTSN , 0, REG_SZ,
		(const BYTE*)(LPCSTR)sn.c_str(), (DWORD)sn.length())) {
			RegCloseKey(hKey);
	}
}
};

namespace internal_utility {
	std::string getSN() {
		return getSNFromRegistry();
	}

	void storeSN(const std::string &sn) {
		storeSNtoRegistry(sn);
	}
};
};