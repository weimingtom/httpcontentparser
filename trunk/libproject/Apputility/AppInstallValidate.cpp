#include "StdAfx.h"
#include ".\AppinstallValidate.h"
#include ".\xinstall.h"
#include ".\apputility.h"
#include <app_constants.h>
#include <process.h>
#include <stdlib.h>
#include <io.h>





namespace {
	UINT RegisterServices();
	UINT UnRegisterServices();
	UINT RegisterServices(TCHAR * install_path);
	UINT UnRegisterServices(TCHAR * install_path);
};

AppInstallValidate::AppInstallValidate(int type) : type_(type)
{
	memset(install_path, 0, sizeof(install_path));
}

AppInstallValidate::~AppInstallValidate(void)
{
}


void AppInstallValidate::getCurrentPath(HMODULE hModule) {
	// 获取当前路径
	TCHAR currentProcess[MAX_PATH];
	GetModuleFileName(hModule, currentProcess, MAX_PATH);
	GetFileNameDir(currentProcess, install_path, MAX_PATH);
	assert (_tcslen(install_path) != 0);
}

int AppInstallValidate::repair(HMODULE hModule) {
	getCurrentPath(hModule);

	// 安装路径注册表项
	if (!validateReigstrInstallPath(install_path))
		repairRegistryInstallPath(install_path);

	// SPI
	repairSPI();

	// COM 服务
	if (!serviceWorking()) {
		repairCOM();
	}
	return 0;
}
int AppInstallValidate::repair() {
	return repair(NULL);
}

//===================================
// 修复注册表项
bool AppInstallValidate::shouldRepairRegistry() {
	// 当用户是SPI时， 安装路径一定不对。因此不能用来修复
	// 其实只要传入dll的hModule就可以获取路径
	return true;
}

// 修复注册表项
bool AppInstallValidate::repairRegistryInstallPath(const TCHAR * path) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_READ,   &hKey);
	if (ERROR_FILE_NOT_FOUND == ret) {
		// 如果没有键值， 则创建
		ret = ::RegCreateKey(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR, &hKey);
		if (ret != ERROR_SUCCESS){
			setErrNo(F_REGISTRY_OPR_FAILED);
			return false;
		}
	} else if (ERROR_SUCCESS != ret) {
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
bool AppInstallValidate::validateReigstrInstallPath(const TCHAR *currentPath) {
	// 获取路径
	TCHAR pathInReg[MAX_PATH];
	GetInstallPathFromRegistry(pathInReg, MAX_PATH);
	_tcslwr(pathInReg);

	TCHAR tmp[MAX_PATH];
	_tcsncpy(tmp, currentPath, MAX_PATH);
	_tcslwr(tmp);

	return (0 == _tcscmp(pathInReg, tmp));
}

//==================================================
// 修复SPI
bool AppInstallValidate::shouldRepairSPI() {
	// 只有当验证程序是SPI时，不需要修复此项
	if (type_ == VALIDATE_SPI)
		return false;
	else 
		return true;
}

void AppInstallValidate::repairSPI() {
	if (false == shouldRepairSPI())
		return;

	// 如果已经安装，则直接返回成功
	CXInstall install;
	if (install.IsInstalled())
		return;

	installSPI();
}

// 安装SPI
void AppInstallValidate::installSPI() {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH);

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
bool AppInstallValidate::serviceWorking() {
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

void AppInstallValidate::repairCOM() {
	if (type_ != VALIDATE_SPI) {
		setErrNo(UnRegisterServices());
		setErrNo(RegisterServices());
	} else {
		setErrNo(UnRegisterServices(install_path));
		setErrNo(RegisterServices(install_path));
	}
}

bool AppInstallValidate::shouldRepairCOM() {
	// 只要不是COM，
	if (type_ == VALIDATE_COM)
		return false;
	else
		return true;
}

//===================================================
// 设置当前错误号
void AppInstallValidate::setErrNo(int new_error) {
	if (new_error != 0)
		errno_ = new_error;
}

void AppInstallValidate::getErrorMessage(TCHAR * msg, const int len) {
	switch (errno_) {
		case PACKETSFILTERED_FILE_NOT_FOUND:
			_tcsncpy(msg, "Fail to repair! Pleas try to reinstall.", len);
			break;
		case F_COM_FILE_NOT_FOUND:
			_tcsncpy(msg, "Fail to repair! Pleas try to reinstall.", len);
			break;
		case F_REGISTRY_OPR_FAILED:
			_tcsncpy(msg, "Fail to repair! Pleas try to reinstall.", len);
			break;
		default:
			msg[0] = '\0';
	}	
}

namespace {
UINT RegisterServices() {
	TCHAR install_path[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH);
	return RegisterServices(install_path);
}
UINT UnRegisterServices() {
	TCHAR install_path[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH);
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