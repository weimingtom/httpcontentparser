#ifndef _MAINUI_MODEL_H__
#define _MAINUI_MODEL_H__

#include <string>
// ����ģʽ���л�
class Services {
public:
	static bool isParentModel();
	static bool switchParentModel(LPCTSTR password);
	static void switchChildModel();
	static LONG getAppStatus();
	static bool autoSwithOnClose();

	// �Ƿ���ʾע����
	static bool showRegisterMenuItem();
	static bool registered();
	static int trialLeftDays();	
	static bool registerSN(const std::string &sn);
};

#endif  // _MAINUI_MODEL_H__