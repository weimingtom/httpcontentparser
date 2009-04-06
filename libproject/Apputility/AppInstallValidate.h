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

class AppInstallValidate {
public:
	AppInstallValidate(int type);
	~AppInstallValidate(void);

	int repair();		// �޸�
	int repair(HMODULE hModule);
	bool validateIntact();

	void getErrorMessage(TCHAR * msg, const int len);
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

	void setErrNo(int new_error);
	UINT errno_;

private:
	AppInstallValidate(void);
	friend class AppInstallValTest;
	
	TCHAR install_path[MAX_PATH];	// ��װ·��
};

#endif  // _SYSUTILITY_APPINSTALLVALIDATE_H__