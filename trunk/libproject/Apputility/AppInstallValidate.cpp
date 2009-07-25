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
	// ��ȡ��ǰ·��
	TCHAR currentProcess[MAX_PATH];
	GetModuleFileName(hModule, currentProcess, MAX_PATH);
	GetFileNameDir(currentProcess, install_path, MAX_PATH);
	assert (_tcslen(install_path) != 0);
}

int AppInstallValidate::uninstall() {
	// ɾ��SPI
	CXInstall	m_Install;
	m_Install.RemoveProvider();

	// ע��COM����
	internal_utility::UnRegisterServices();
	return 0;
}
int AppInstallValidate::repair(bool removefirst) {
	if (shouldInstall() == false) {
		return 0;
	}

	getCurrentPath(NULL);

	// ��װ·��ע�����
	if (!validateReigstrInstallPath(install_path)) {
		repairRegistryInstallPath(install_path);
		_DEBUG_STREAM_TRC_("[AppInstallValidate] ["<<__FUNCTION__<<"] Repair Registry Install Path");
	}

	// SPI
	repairSPI(removefirst);

	// COM ����
	//if (!serviceWorking()) {
	repairCOM(removefirst);
	//}
	return 0;
}


//===================================
// �޸�ע�����
bool AppInstallValidate::shouldRepairRegistry() {
	// ���û���SPIʱ�� ��װ·��һ�����ԡ���˲��������޸�
	// ��ʵֻҪ����dll��hModule�Ϳ��Ի�ȡ·��
	if (type_ == VALIDATE_SPI) {
		return false;
	} else {
		return true;
	}
}

// �޸�ע�����
bool AppInstallValidate::repairRegistryInstallPath(const TCHAR * path) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_WRITE,   &hKey);
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

// ��֤ע����еİ�װ·���Ƿ���ȷ
bool AppInstallValidate::validateReigstrInstallPath(const TCHAR *currentPath) {
	TCHAR tmp[MAX_PATH];
	_tcsncpy(tmp, currentPath, MAX_PATH);
	_tcslwr(tmp);

	// ��ȡ·��
	TCHAR pathInReg[MAX_PATH] = {0};
	GetInstallPathFromRegistry(pathInReg, MAX_PATH);
	_tcslwr(pathInReg);

	return (0 == _tcscmp(pathInReg, tmp));
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

void AppInstallValidate::repairSPI(bool removefirst) {
	if (false == shouldRepairSPI())
		return;

	CXInstall install;
	// �������ǿ��ж�غ���װ
	if (removefirst == true) {
		install.RemoveProvider();
		installSPI();
		return;
	} else {
		// ��һ�ַ�ʽ���û�а�װ�Ű�װ
		if (!install.IsInstalled()) {
			installSPI();
		}
	} 
}

// ��װSPI
void AppInstallValidate::installSPI() {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH);
	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, PACKETSGRASPER_DLL_NAME);

	// �ļ�������
	if (_taccess(fullpath, 0) == -1) {
		setErrNo(PACKETSFILTERED_FILE_NOT_FOUND);
		return;
	}

	CXInstall	m_Install;
	setErrNo(m_Install.InstallProvider(fullpath));
	_DEBUG_STREAM_TRC_("Repair SPI");
}

//=========================================
// COM����
// COM�����Ƿ�ע��
/*bool AppInstallValidate::serviceWorking() {
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
	// ֻҪ����COM��
	if (type_ == VALIDATE_COM)
		return false;
	else
		return true;
}


//===================================================
// ���õ�ǰ�����
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
		// ������
		return false;
	} else if (SNOWMAN_STATUS_UNINSTALL == status_) {
		// ж��
		// �϶���Ҫ���޸���
		return false;
	} else if (SNOWMAN_STATUS_UPDATE == status_) {
		// ����������Ҫ������
		// ������ʱ�������Ҫ��ж���ˣ���ʱ��
		// �Ͳ�Ҫ���޸���
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
		// ����ļ��������򷵻�FALSE
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
		// ����ļ��������򷵻�FALSE
		return F_COM_FILE_NOT_FOUND;
	}
}
};

};