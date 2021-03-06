#ifndef _SYSUTILITY_APPINSTALLVALIDATE_H__
#define _SYSUTILITY_APPINSTALLVALIDATE_H__


// 以何种身份惊醒验证 如果是COM， 则不验证COM， 如果是SPI则不验证SPI
// 如果什么都不是就全部验证
#define VALIDATE_COM	  0x000000002
#define VALIDATE_SPI	  0x000000004
#define VLAIDATE_NONE	  0x000000000

#define SUCCESS 0
#define F_COM_FILE_NOT_FOUND	1
#define F_REGISTRY_OPR_FAILED	2

#include <apputility\ApputilityDLL.H>

namespace AppUtility {

// 此类负责检测安装情况
// 另外本程序还会根据程序的使用情况
// 如：是否应该注册， 是否已经超期，等情况决定如何改变安装组件

// 情况通常分成3类
// 第一类， 已经注册，那么应该永远进行安装
// 第二类，  卸载		这时候不再执行任何安装过程
// 第三类	， 超期，    用户没有注册且使用超期，这时候只要卸载组建即可（）
// 注意，这三种情况应该通过COM Service获取， 此类只要简单的根据各种
// 情况进行操作就可以了！
class APPUTILITYDLL_API AppInstallValidate {
public:
	AppInstallValidate(int type, int status);
	~AppInstallValidate(void);

	int repair(bool removefirst=false);		// 修复
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
	int status_;			// 保存应用程序的状态
	
	void setErrNo(int new_error);
	UINT errno_;

public:
    bool shouldRepairSPI();
    bool shouldInstall();
    bool shouldRepairRegistry();
    bool shouldRepairCOM();

private:
	AppInstallValidate(void);
	TCHAR install_path[MAX_PATH];	// 安装路径

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