#ifndef _MAINUI_MODEL_H__
#define _MAINUI_MODEL_H__

// ����ģʽ���л�
class Services {
public:
	static bool isParentModel();
	static bool switchParentModel(LPCTSTR password);
	static void switchChildModel();
};

#endif  // _MAINUI_MODEL_H__