#include "StdAfx.h"
#include ".\AppinstallValidate.h"
#include ".\xinstall.h"
#include ".\apputility.h"
#include <app_constants.h>
#include <process.h>
#include <stdlib.h>
#include <io.h>





namespace {
	UINT RegisterServices(HMODULE hModule);
	UINT UnRegisterServices(HMODULE hModule);
	UINT RegisterServices(TCHAR * install_path);
	UINT UnRegisterServices(TCHAR * install_path);
};

AppInstallValidate::AppInstallValidate(int type) : type_(type)
{
}

AppInstallValidate::~AppInstallValidate(void)
{
}


int AppInstallValidate::repair(HMODULE hModule) {
	// ��ȡ��ǰ·��
	TCHAR currentPath[MAX_PATH], currentProcess[MAX_PATH];
	GetModuleFileName(hModule, currentProcess, MAX_PATH);
	GetFileNameDir(currentProcess, currentPath, MAX_PATH);

	// ��װ·��ע�����
	if (!validateReigstrInstallPath(currentPath))
		repairRegistryInstallPath(currentPath);

	// SPI
	repairSPI(hModule);

	// COM ����
	if (!serviceWorking(hModule)) {
		repairCOM(hModule);
	}
	return 0;
}

bool AppInstallValidate::shouldRepairRegistry() {
	// ���û���SPIʱ�� ��װ·��һ�����ԡ���˲��������޸�
	if (type_ == VALIDATE_SPI)
		return false;
	else
		return true;
}
// �޸�ע�����
bool AppInstallValidate::repairRegistryInstallPath(const TCHAR * path) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_READ,   &hKey);
	if (ERROR_FILE_NOT_FOUND == ret) {
		// ���û�м�ֵ�� �򴴽�
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

// ��֤ע����еİ�װ·���Ƿ���ȷ
bool AppInstallValidate::validateReigstrInstallPath(const TCHAR *currentPath) {
	// ��ȡ·��
	TCHAR pathInReg[MAX_PATH];
	GetInstallPathFromRegistry(pathInReg, MAX_PATH);
	_tcslwr(pathInReg);

	TCHAR tmp[MAX_PATH];
	_tcsncpy(tmp, currentPath, MAX_PATH);
	_tcslwr(tmp);

	return 0 == _tcscmp(pathInReg, tmp);
}

//==================================================
// �޸�SPI
bool AppInstallValidate::shouldRepairSPI() {
	// ֻ�е���֤������SPIʱ������Ҫ�޸�����
	if (type_ == VALIDATE_SPI)
		return false;
	else 
		return true;
}

void AppInstallValidate::repairSPI(HMODULE hModule) {
	if (false == shouldRepairSPI())
		return;

	// ����Ѿ���װ����ֱ�ӷ��سɹ�
	CXInstall install;
	if (install.IsInstalled())
		return;

	installSPI(hModule);
}

// ��װSPI
void AppInstallValidate::installSPI(HMODULE hModule) {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, PACKETSGRASPER_DLL_NAME);

	// �ļ�������
	if (_taccess(fullpath, 0) == -1) {
		setErrNo(PACKETSFILTERED_FILE_NOT_FOUND);
		return;
	}

	CXInstall	m_Install;
	setErrNo(m_Install.InstallProvider(fullpath));
}

//=========================================
// COM����
// COM�����Ƿ�ע��
bool AppInstallValidate::serviceWorking(HMODULE hModule) {
	if (!shouldRepairCOM())
		return true;

	// ��
	SC_HANDLE handle = OpenSCManager(NULL, NULL,
		SC_MANAGER_ALL_ACCESS);

	if(NULL == handle)
		return false;

	// ���û�ܴ򿪷���
	SC_HANDLE service_handle = OpenService(handle, SERVICE_FILENAME, SC_MANAGER_ALL_ACCESS);
	if (NULL == service_handle) {
		CloseServiceHandle(handle);
		return false;
	}

	// �������ʧ��
	if (!StartService(service_handle, 0, NULL))
		return false;


	CloseServiceHandle(service_handle);
	CloseServiceHandle(handle);
	return true;
}

void AppInstallValidate::repairCOM(HMODULE hModule) {
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

bool AppInstallValidate::shouldRepairCOM() {
	// ֻҪ����COM��
	if (type_ == VALIDATE_COM)
		return false;
	else
		return true;
}

// ���õ�ǰ�����
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
		// ����ļ��������򷵻�FALSE
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
		// ����ļ��������򷵻�FALSE
		return F_COM_FILE_NOT_FOUND;
	}
}


};