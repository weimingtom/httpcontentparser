#ifndef _SYSUTILITY_APPINSTALLVALIDATE_H__
#define _SYSUTILITY_APPINSTALLVALIDATE_H__


// �Ժ�����ݾ�����֤ �����COM�� ����֤COM�� �����SPI����֤SPI
// ���ʲô�����Ǿ�ȫ����֤
#define VALIDATE_COM	  0x000000002
#define VALIDATE_SPI	  0x000000004
#define VLAIDATE_NONE	  0x000000000

#define SUCCESS 0
#define F_COM_FILE_NOT_FOUND	1
#define F_REGISTRY_OPR_FAILED	2

namespace AppUtility {


// ���ฺ���ⰲװ���
// ���Ȿ���򻹻���ݳ����ʹ�����
// �磺�Ƿ�Ӧ��ע�ᣬ �Ƿ��Ѿ����ڣ������������θı䰲װ���

// ���ͨ���ֳ�3��
// ��һ�࣬ �Ѿ�ע�ᣬ��ôӦ����Զ���а�װ
// �ڶ��࣬  ж��		��ʱ����ִ���κΰ�װ����
// ������	�� ���ڣ�    �û�û��ע����ʹ�ó��ڣ���ʱ��ֻҪж���齨���ɣ���
// ע�⣬���������Ӧ��ͨ��COM Service��ȡ�� ����ֻҪ�򵥵ĸ��ݸ���
// ������в����Ϳ����ˣ�
class AppInstallValidate {
public:
	AppInstallValidate(int type, int status);
	~AppInstallValidate(void);

	int repair();		// �޸�
	int repair(HMODULE hModule);
	bool validateIntact();

	void getErrorMessage(TCHAR * msg, const int len);

	int uninstall();
private:
	bool validateReigstrInstallPath(const TCHAR *path);
	bool repairRegistryInstallPath(const TCHAR * path);
	bool shouldRepairRegistry();

	// SPI
	void repairSPI();
	void installSPI();
	bool shouldRepairSPI();

	// COM Service
	bool serviceWorking();
	void repairCOM();
	bool shouldRepairCOM();

	// install shell extension
	void repairShellExt();

	void getCurrentPath(HMODULE hModule);
private:
	int type_;
	int status_;			// ����Ӧ�ó����״̬

	bool shouldInstall();
	void setErrNo(int new_error);
	UINT errno_;

private:
	AppInstallValidate(void);
	friend class AppInstallValTest;
	
	TCHAR install_path[MAX_PATH];	// ��װ·��
};

UINT UninstallSPI();
UINT UninstallService();
UINT UninstallShellExt();

namespace internal_utility {
	UINT RegisterServices();
	UINT UnRegisterServices();
	UINT RegisterServices(TCHAR * install_path);
	UINT UnRegisterServices(TCHAR * install_path);
};

}; // namespace AppUtility
#endif  // _SYSUTILITY_APPINSTALLVALIDATE_H__