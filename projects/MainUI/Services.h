#ifndef _MAINUI_MODEL_H__
#define _MAINUI_MODEL_H__

#include <string>
// ����ģʽ���л�
class Services {
public:
	static bool isParentModel();
	static bool switchParentModel(LPCTSTR password);
	static void switchChildModel();
	static UINT_PTR getAppStatus();
	static bool autoSwithOnClose();

	// �Ƿ���ʾע����
	static bool showRegisterMenuItem();
	static bool registered();
	static INT_PTR trialLeftDays();	
	static bool registerSN(const std::string &sn);
	
	// �Ƿ��ǵ�һ�δ򿪽ҽ���
	static bool firstOpen();
	static bool setPwdForFirstTime(LPCTSTR pwd);
	static bool setNewPwd(LPCTSTR newpwd, LPCTSTR oldpwd);
	static INT_PTR validatePwd(const CString &newpwd, const CString & secpwd);		// ������������֤
};

#endif  // _MAINUI_MODEL_H__