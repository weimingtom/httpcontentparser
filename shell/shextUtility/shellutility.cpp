#include "stdafx.h"
#include "shellutility.h"
#include <shell\exts_i.c>
#include <shell\exts.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <comdef.h>

#define INSTALL_ITEM_APP_CONTROL	TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellExecuteHooks\\")
#define INSTALL_ITEM_COPY_HOOK		TEXT("Directory\\Shellex\\CopyHookHandlers")

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

#define APP_CONTROL_CLSID TEXT("{B0C0589E-9692-44E0-B2F1-378BE31B61C1}")
#define COPY_HOOK_CLSID		TEXT("{16114555-8805-444D-BB1F-0D9BB3536A7B}")

namespace {
	bool szExistInSubKey(HKEY key, LPCTSTR pSubKey, LPCTSTR lpItemText);
	int addSzItemInSubKey(HKEY hKey, LPCTSTR pSubKey, LPCTSTR lpItemText);
	int delSzItemInSubKey(HKEY hKey, LPCTSTR pSubKey, LPCTSTR itemValue) ;
}

// 安装拷贝控制
bool isInstallCopyHook() {
	return szExistInSubKey(HKEY_CLASSES_ROOT, INSTALL_ITEM_COPY_HOOK, COPY_HOOK_CLSID);
}

bool installCopyHook() {
	return addSzItemInSubKey(HKEY_CLASSES_ROOT, INSTALL_ITEM_COPY_HOOK, COPY_HOOK_CLSID);
}

int uninstallCopyControl() {
	return delSzItemInSubKey(HKEY_CLASSES_ROOT, INSTALL_ITEM_COPY_HOOK, COPY_HOOK_CLSID);
}

// 安装应用程序控制
int installAppControl() {
	return addSzItemInSubKey(HKEY_LOCAL_MACHINE, INSTALL_ITEM_APP_CONTROL, APP_CONTROL_CLSID);
}
bool isInstallAppControl() {
	return szExistInSubKey(HKEY_LOCAL_MACHINE, INSTALL_ITEM_APP_CONTROL, APP_CONTROL_CLSID);
}
int uninstallAppControl() {
	return delSzItemInSubKey(HKEY_LOCAL_MACHINE, INSTALL_ITEM_APP_CONTROL, APP_CONTROL_CLSID);
}

namespace {
int delSzItemInSubKey(HKEY hKey, LPCTSTR pSubKey, LPCTSTR pssItem) {
	HKEY hKeyNew;
	LONG result = RegOpenKeyEx(hKey, pSubKey, 0,  KEY_WRITE, &hKeyNew);
	if (ERROR_FILE_NOT_FOUND == result) {
		return 0;
	} else if (ERROR_SUCCESS == result) {
		if (ERROR_SUCCESS ==   ::RegDeleteValue(hKeyNew, pssItem)) {
			return 0;
		} else {
			return -1;
		}
	}
	return -1;
}
int addSzItemInSubKey(HKEY hKey, LPCTSTR pSubKey, LPCTSTR lpItemText) {
	HKEY hKeyNew;
	LONG result = RegOpenKeyEx(hKey, pSubKey, 0,  KEY_WRITE, &hKeyNew);
	if (ERROR_SUCCESS != result) {
		// 如果不存在则创建
		if (ERROR_FILE_NOT_FOUND == result) {
			DWORD	dwDisposition;
			result = ::RegCreateKeyEx(hKey, pSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyNew, &dwDisposition) ;
			if (result != ERROR_SUCCESS) {
				return -1;
			}
			result = RegOpenKeyEx(hKey, pSubKey, 0,  KEY_WRITE, &hKeyNew);
			if (ERROR_SUCCESS != result) {
				return 1;
			}
		} else {
		return 1; 
		}
	}

	// 添加一个新项
	result = RegSetValueEx(hKeyNew, lpItemText , 0, REG_SZ, 	(const BYTE*)(LPCSTR)lpItemText, (DWORD)_tcslen(lpItemText));
	if (ERROR_SUCCESS == result) {
		RegCloseKey(hKeyNew);
		return 0;
	} else {
		int a = GetLastError();
		return 2;
	}
}
bool szExistInSubKey(HKEY topkey, LPCTSTR pSubKey, LPCTSTR lpItemText) {
			// get key
	HKEY hKey;
	if (ERROR_SUCCESS != RegOpenKeyEx(topkey, pSubKey, 0, KEY_READ,  &hKey)) {
		return false;
	}

	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys=0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	// Get the class name and the value count. 
	DWORD retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

	if (cValues) {
		TCHAR  achValue[MAX_VALUE_NAME]; 
		DWORD cchValue = MAX_VALUE_NAME; 

		for (int i=0, retCode = ERROR_SUCCESS; i < cValues; i++)  { 
			cchValue = MAX_VALUE_NAME; 
			achValue[0] = '\0'; 
			retCode = RegEnumValue(hKey, i, 
				achValue, 
				&cchValue, 
				NULL, 
				NULL,
				NULL,
				NULL);

			if (_tcscmp(achValue, lpItemText) == 0) {
				RegCloseKey(hKey);
				return true;
			}
		}

	}

	RegCloseKey(hKey);
	return false;
	}
}