#ifndef _MAINUI_MODEL_H__
#define _MAINUI_MODEL_H__

#include <string>
// 控制模式的切换
class Services {
public:
	static bool isParentModel();
	static bool switchParentModel(LPCTSTR password);
	static void switchChildModel();
	static UINT_PTR getAppStatus();
	static bool autoSwithOnClose();

	// 是否显示注册项
	static bool showRegisterMenuItem();
	static bool registered();
	static INT_PTR trialLeftDays();	
	static bool registerSN(const std::string &sn);
	
	// 是否是第一次打开揭界面
	static bool firstOpen();
	static bool setPwdForFirstTime(LPCTSTR pwd);
	static bool setNewPwd(LPCTSTR newpwd, LPCTSTR oldpwd);
	static INT_PTR validatePwd(const CString &newpwd, const CString & secpwd);		// 设置密码是验证
};

#endif  // _MAINUI_MODEL_H__