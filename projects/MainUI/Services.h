#ifndef _MAINUI_MODEL_H__
#define _MAINUI_MODEL_H__

// 控制模式的切换
class Services {
public:
	static bool isParentModel();
	static bool switchParentModel(LPCTSTR password);
	static void switchChildModel();
	static LONG getAppStatus();
};

#endif  // _MAINUI_MODEL_H__