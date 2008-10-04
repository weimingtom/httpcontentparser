#ifndef _SETTING_SCREEN_SAVER_H__
#define _SETTING_SCREEN_SAVER_H__

#include <settingitem.h>
#include "calculagraph.h"

class ScreenSaver : public SettingItem {
public:
	ScreenSaver(void);
	~ScreenSaver(void);

	//=====
	int getTimeSpan() const; // seconds
	void setTimeSpan(const int seconds);


	bool shouldSave(); // ����Ӧ��Save����
private:
	void defaultSetting();

	Calculagraph calcugraph_;
};

#endif  // _SETTING_SCREEN_SAVER_H__
