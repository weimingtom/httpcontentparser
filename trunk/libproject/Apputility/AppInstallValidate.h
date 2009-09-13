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

#include <apputility\ApputilityDLL.H>

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
class APPUTILITYDLL_API AppInstallValidate {
public:
	AppInstallValidate(int type, int status);
	~AppInstallValidate(void);

	int repair(bool removefirst=false);		// �޸�
	bool validateIntact();

	void getErrorMessage(TCHAR * msg, const int len);

	int uninstall();

    int getErrorCode() const { return errno_;}
private:
	bool validateReigstrInstallPath(const TCHAR *path);
	bool repairRegistryInstallPath(const TCHAR * path);
	
	// SPI
	void repairSPI(bool removefirst);
	void installSPI();
	
	// COM Service
	//bool serviceWorking();
	void repairCOM(bool removefirst);

	// install shell extension
	void getCurrentPath(HMODULE hModule);
private:
	int type_;
	int status_;			// ����Ӧ�ó����״̬
	
	void setErrNo(int new_error);
	UINT errno_;

public:
    bool shouldRepairSPI();
    bool shouldInstall();
    bool shouldRepairRegistry();
    bool shouldRepairCOM();

private:
	AppInstallValidate(void);
	TCHAR install_path[MAX_PATH];	// ��װ·��

private:
    friend  void testShouldRepair();
    friend  void testRunInCOM();
    friend  void testRunInSPI();
    friend  void testRunInNone();
    friend  void testServieInstall();
};

APPUTILITYDLL_API UINT UninstallSPI();
APPUTILITYDLL_API UINT UninstallService();

namespace internal_utility {
	APPUTILITYDLL_API UINT RegisterServices();
	APPUTILITYDLL_API UINT UnRegisterServices();
	APPUTILITYDLL_API UINT RegisterServices(TCHAR * install_path);
	APPUTILITYDLL_API UINT UnRegisterServices(TCHAR * install_path);
};

}; // namespace AppUtility
#endif  // _SYSUTILITY_APPINSTALLVALIDATE_H__