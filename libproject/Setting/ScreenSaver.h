#ifndef _SETTING_SCREEN_SAVER_H__
#define _SETTING_SCREEN_SAVER_H__

#include "calculagraph.h"

class ScreenSaver {
public:
	ScreenSaver(void);
	~ScreenSaver(void);

	//=====
	int getTimeSpan() const; // seconds
	void setTimeSpan(const int seconds);


	bool isEnabled() const ; // �Ƿ����
	void enable(const bool enabled);	// ��save����
	bool shouldSave(); // ����Ӧ��Save����

private:
	void defaultSetting();

	Calculagraph calcugraph_;
	bool enabled_;
};

#endif  // _SETTING_SCREEN_SAVER_H__
