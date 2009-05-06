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


// 此类负责检测安装情况
// 另外本程序还会根据程序的使用情况
// 如：是否应该注册， 是否已经超期，等情况决定如何改变安装组件

// 情况通常分成3类
// 第一类， 已经注册，那么应该永远进行安装
// 第二类， 卸载			这时候不再执行任何安装过程
// 第三类	， 超期，    用户没有注册且使用超期，这时候只要卸载组建即可（）
// 注意，这三种情况应该通过COM Service获取， 此类只要简单的根据各种
// 情况进行操作就可以了！
class AppInstallValidate {
public:
	AppInstallValidate(int type);
	~AppInstallValidate(void);

	int repair();		// 修复
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
	int status_;			// 保存应用程序的状态

	bool shouldInstall();
	void setErrNo(int new_error);
	UINT errno_;

private:
	AppInstallValidate(void);
	friend class AppInstallValTest;
	
	TCHAR install_path[MAX_PATH];	// 安装路径
};

#endif  // _SYSUTILITY_APPINSTALLVALIDATE_H__