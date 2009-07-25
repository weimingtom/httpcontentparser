#include "StdAfx.h"
#include ".\AppinstallValidate.h"
#include ".\xinstall.h"
#include ".\apputility.h"
#include <app_constants.h>
#include <process.h>
#include <stdlib.h>
#include <io.h>
#include <softwareStatus.h>
#include <DebugOutput.h>


namespace AppUtility {


UINT UninstallSPI() {
	CXInstall	m_Install;
	m_Install.RemoveProvider();
	return 0;
}
UINT UninstallService() {
	internal_utility::UnRegisterServices();
	return 0;
}


AppInstallValidate::AppInstallValidate(int type, int status) : type_(type), status_(status)
{
	memset(install_path, 0, sizeof(install_path));
	status_ = SNOWMAN_STATUS_TRIAL;
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

int AppInstallValidate::uninstall() {
	// 删除SPI
	CXInstall	m_Install;
	m_Install.RemoveProvider();

	// 注销COM服务
	internal_utility::UnRegisterServices();
	return 0;
}
int AppInstallValidate::repair(bool removefirst) {
	if (shouldInstall() == false) {
		return 0;
	}

	getCurrentPath(NULL);

	// 安装路径注册表项
	if (!validateReigstrInstallPath(install_path)) {
		repairRegistryInstallPath(install_path);
		_DEBUG_STREAM_TRC_("[AppInstallValidate] ["<<__FUNCTION__<<"] Repair Registry Install Path");
	}

	// SPI
	repairSPI(removefirst);

	// COM 服务
	//if (!serviceWorking()) {
	repairCOM(removefirst);
	//}
	return 0;
}


//===================================
// 修复注册表项
bool AppInstallValidate::shouldRepairRegistry() {
	// 当用户是SPI时， 安装路径一定不对。因此不能用来修复
	// 其实只要传入dll的hModule就可以获取路径
	if (type_ == VALIDATE_SPI) {
		return false;
	} else {
		return true;
	}
}

// 修复注册表项
bool AppInstallValidate::repairRegistryInstallPath(const TCHAR * path) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_WRITE,   &hKey);
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

	ret = RegSetValueEx( hKey, REG_SOFTWARE_INSTALLPATH , 0, REG_SZ, (const BYTE*)(LPCSTR)path, (DWORD)_tcslen(path));
	if (ERROR_SUCCESS == ret) {
		RegCloseKey(hKey);
		return true;
	} else {
		setErrNo(F_REGISTRY_OPR_FAILED);
		_DEBUG_STREAM_TRC_("["<<__FUNCTION__<<"] Failed On Registion Operation Errono : " << ret);
		return false;
	}
}

// 验证注册表中的安装路径是否正确
bool AppInstallValidate::validateReigstrInstallPath(const TCHAR *currentPath) {
	TCHAR tmp[MAX_PATH];
	_tcsncpy(tmp, currentPath, MAX_PATH);
	_tcslwr(tmp);

	// 获取路径
	TCHAR pathInReg[MAX_PATH] = {0};
	GetInstallPathFromRegistry(pathInReg, MAX_PATH);
	_tcslwr(pathInReg);

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

void AppInstallValidate::repairSPI(bool removefirst) {
	if (false == shouldRepairSPI())
		return;

	CXInstall install;
	// 如果必须强制卸载后，重装
	if (removefirst == true) {
		install.RemoveProvider();
		installSPI();
		return;
	} else {
		// 另一种方式如果没有安装才安装
		if (!install.IsInstalled()) {
			installSPI();
		}
	} 
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
	_DEBUG_STREAM_TRC_("Repair SPI");
}

//=========================================
// COM服务
// COM服务是否注册
/*bool AppInstallValidate::serviceWorking() {
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
}*/

void AppInstallValidate::repairCOM(bool removefirst) {
	if (!shouldRepairCOM())
		return;

	if (removefirst == TRUE) {
		setErrNo(internal_utility::UnRegisterServices());
	}
	setErrNo(internal_utility::RegisterServices());
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
			_sntprintf(msg, len, "File %s cannot be found. Please restainll the software.", PACKETSGRASPER_DLL_NAME );
			break;
		case F_COM_FILE_NOT_FOUND:
			_sntprintf(msg, len, "File  %s cannot be found. Please restainll the software.", SERVICE_FILENAME );
			break;
		case F_REGISTRY_OPR_FAILED:
			_tcsncpy(msg, "Fail to repair! Pleas try to reinstall.", len);
			
			break;
		default:
			msg[0] = '\0';
	}	
}

bool AppInstallValidate::shouldInstall() {
	if (SNOWMAN_STATUS_REGISTERED == status_) {
		return true;
	} else if (SNOWMAN_STATUS_TRIAL == status_) {
		return true;
	} else if (SNOWMAN_STATUS_OVERTIME == status_) {
		// 超期了
		return false;
	} else if (SNOWMAN_STATUS_UNINSTALL == status_) {
		// 卸载
		// 肯定不要再修复了
		return false;
	} else if (SNOWMAN_STATUS_UPDATE == status_) {
		// 如果重启后就要升级了
		// 在重启时程序可能要被卸载了，这时候
		// 就不要再修复了
		return false;
	} else {
		return false;
	}
}

namespace internal_utility {
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
		_sntprintf(cmd, MAX_PATH, "%s /regserver", fullpath);
		WinExec(cmd, SW_HIDE);
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
		WinExec(cmd, SW_HIDE);
		return PACKETSFILTERED_INSTALL_SUCC;
	} else {
		// 如果文件不存在则返回FALSE
		return F_COM_FILE_NOT_FOUND;
	}
}
};

};