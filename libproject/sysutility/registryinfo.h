#ifndef _SYSUTILITY_REGISTERINFO_H__
#define _SYSUTILITY_REGISTERINFO_H__


#define INTACT_VALIDATE_REGISTRY_ERROR		0
#define INTACT_VALIDATE_COM_ERROR			1
#define INTACT_VALIDATE_SPI_ERROR			2

// 以何种身份惊醒验证 如果是COM， 则不验证COM， 如果是SPI则不验证SPI
// 如果什么都不是就全部验证
#define VALIDATE_COM	  0x000000002
#define VALIDATE_SPI	  0x000000004
#define VLAIDATE_NONE	  0x000000000

class RegisterInfo {
public:
	RegisterInfo(void);
	~RegisterInfo(void);

	int repair(HMODULE hModule);		// 修复
	bool validateIntact(HMODULE hModule);
private:
	bool validateReigstrInstallPath(const TCHAR *path);
	bool repairRegistryInstallPath(const TCHAR * path);
	bool shouldRepairRegistry();

	// SPI
	void repairSPI(HMODULE hModule);
	void installSPI(HMODULE hModule);
	bool shouldRepairSPI();

	// COM Service
	bool serviceWorking(HMODULE hModule);
	void repairCOM(HMODULE hModule);
	bool shouldRepairCOM();

	void getErrorMessage(TCHAR * msg, const int len);
private:
	int type_;

	void setErrNo(int new_error);
	UINT errno_;
};

#endif  // _SYSUTILITY_REGISTERINFO_H__