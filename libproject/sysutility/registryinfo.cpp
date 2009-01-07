#include "StdAfx.h"
#include ".\registryinfo.h"
#include ".\xinstall.h"
#include ".\sysutility.h"
#include <app_constants.h>
#include <sysutility.h>
#include <process.h>
#include <stdlib.h>
#include <io.h>


#define SUCCESS 0
#define F_COM_FILE_NOT_FOUND	1
#define F_REGISTRY_OPR_FAILED	2


namespace {
	UINT RegisterServices(HMODULE hModule);
	UINT UnRegisterServices(HMODULE hModule);
	UINT RegisterServices(TCHAR * install_path);
	UINT UnRegisterServices(TCHAR * install_path);
};

RegisterInfo::RegisterInfo(void)
{
}

RegisterInfo::~RegisterInfo(void)
{
}


int RegisterInfo::repair(HMODULE hModule) {
	// 获取当前路径
	TCHAR currentPath[MAX_PATH], currentProcess[MAX_PATH];
	GetModuleFileName(hModule, currentProcess, MAX_PATH);
	GetFileNameDir(currentProcess, currentPath, MAX_PATH);

	// 安装路径注册表项
	if (!validateReigstrInstallPath(currentPath))
		repairRegistryInstallPath(currentPath);

	// SPI
	repairSPI(hModule);

	// COM 服务
	if (!serviceWorking(hModule)) {
		repairCOM(hModule);
	}
	return 0;
}

bool RegisterInfo::shouldRepairRegistry() {
	// 当用户是SPI时， 安装路径一定不对。因此不能用来修复
	if (type_ == VALIDATE_SPI)
		return false;
	else
		return true;
}
// 修复注册表项
bool RegisterInfo::repairRegistryInstallPath(const TCHAR * path) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_READ,   &hKey);
	if (ERROR_SUCCESS != ret) {
		setErrNo(F_REGISTRY_OPR_FAILED);
		return false;
	}

	if (ERROR_SUCCESS == RegSetValueEx( hKey, REG_SOFTWARE_INSTALLPATH , 0, REG_SZ, (const BYTE*)(LPCSTR)path, (DWORD)_tcslen(path))) {
		RegCloseKey(hKey);
		return true;
	} else {
		setErrNo(F_REGISTRY_OPR_FAILED);
		return false;
	}
}

// 验证注册表中的安装路径是否正确
bool RegisterInfo::validateReigstrInstallPath(const TCHAR *currentPath) {
	// 获取路径
	TCHAR pathInReg[MAX_PATH];
	GetInstallPathFromRegistry(pathInReg, MAX_PATH);
	_tcslwr(pathInReg);

	TCHAR tmp[MAX_PATH];
	_tcsncpy(tmp, currentPath, MAX_PATH);
	_tcslwr(tmp);

	return 0 == _tcscmp(pathInReg, tmp);
}

//==================================================
// 修复SPI
bool RegisterInfo::shouldRepairSPI() {
	// 只有当验证程序是SPI时，不需要修复此项
	if (type_ == VALIDATE_SPI)
		return false;
	else 
		return true;
}

void RegisterInfo::repairSPI(HMODULE hModule) {
	if (false == shouldRepairSPI())
		return;

	// 如果已经安装，则直接返回成功
	CXInstall install;
	if (install.IsInstalled())
		return;

	installSPI(hModule);
}

// 安装SPI
void RegisterInfo::installSPI(HMODULE hModule) {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, PACKETSGRASPER_DLL_NAME);

	// 文件不存在
	if (_taccess(fullpath, 0) == -1) {
		setErrNo(PACKETSFILTERED_FILE_NOT_FOUND);
		return;
	}

	CXInstall	m_Install;
	setErrNo(m_Install.InstallProvider(fullpath));
}

//=========================================
// COM服务
// COM服务是否注册
bool RegisterInfo::serviceWorking(HMODULE hModule) {
	if (!shouldRepairCOM())
		return true;

	// 打开
	SC_HANDLE handle = OpenSCManager(NULL, NULL,
		SC_MANAGER_ALL_ACCESS);

	if(NULL == handle)
		return false;

	// 如果没能打开服务
	SC_HANDLE service_handle = OpenService(handle, SERVICE_FILENAME, SC_MANAGER_ALL_ACCESS);
	if (NULL == service_handle) {
		CloseServiceHandle(handle);
		return false;
	}

	// 如果启动失败
	if (!StartService(service_handle, 0, NULL))
		return false;


	CloseServiceHandle(service_handle);
	CloseServiceHandle(handle);
	return true;
}

void RegisterInfo::repairCOM(HMODULE hModule) {
	if (type_ != VALIDATE_SPI) {
		setErrNo(UnRegisterServices(hModule));
		setErrNo(RegisterServices(hModule));
	} else {
		TCHAR install_path[MAX_PATH];
		GetInstallPathFromRegistry(install_path, MAX_PATH);
		setErrNo(UnRegisterServices(install_path));
		setErrNo(RegisterServices(install_path));
	}
}

bool RegisterInfo::shouldRepairCOM() {
	// 只要不是COM，
	if (type_ == VALIDATE_COM)
		return false;
	else
		return true;
}

// 设置当前错误号
void RegisterInfo::setErrNo(int new_error) {
	if (new_error != 0)
		errno_ = new_error;
}

void RegisterInfo::getErrorMessage(TCHAR * msg, const int len) {
	switch (errno_) {
		case PACKETSFILTERED_FILE_NOT_FOUND:
			_tcsncpy(msg, "", len);
			break;
		case F_COM_FILE_NOT_FOUND:
			_tcsncpy(msg, "", len);
			break;
		case F_REGISTRY_OPR_FAILED:
			_tcsncpy(msg, "", len);
			break;
		default:
			msg[0] = '\0';
	}	
}

namespace {
UINT RegisterServices(HMODULE hModule) {
	TCHAR install_path[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);
	return RegisterServices(install_path);
}
UINT UnRegisterServices(HMODULE hModule) {
	TCHAR install_path[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);
	return UnRegisterServices(install_path);
}

UINT RegisterServices(TCHAR * install_path) {
	TCHAR fullpath[MAX_PATH], cmd[MAX_PATH];
	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, SERVICE_FILENAME);
	if (_taccess(fullpath, 0) != -1) {
		_sntprintf(cmd, MAX_PATH, "%s /service", fullpath);
		return PACKETSFILTERED_INSTALL_SUCC;
	} else {
		// 如果文件不存在则返回FALSE
		return F_COM_FILE_NOT_FOUND;
	}
}

UINT UnRegisterServices(TCHAR * install_path) {
	TCHAR fullpath[MAX_PATH], cmd[MAX_PATH];
	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, SERVICE_FILENAME);
	if (_taccess(fullpath, 0) != -1) {
		_sntprintf(cmd, MAX_PATH, "%s /unregserver", fullpath);
		return PACKETSFILTERED_INSTALL_SUCC;
	} else {
		// 如果文件不存在则返回FALSE
		return F_COM_FILE_NOT_FOUND;
	}
}


};