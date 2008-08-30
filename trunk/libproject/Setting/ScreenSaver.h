#ifndef _SETTING_SCREEN_SAVER_H__
#define _SETTING_SCREEN_SAVER_H__

#include "calculagraph.h"

class ScreenSaver {
public:
	ScreenSaver(void);
	~ScreenSaver(void);

	void initialize();

	//=====
	int getTimeSpan() const; // seconds
	void setTimeSpan(const int seconds);


	bool isEnabled() const ; // 是否可用
	void enableSave(const bool enabled);	// 是save可用
	bool shouldSave(); // 现在应该Save了吗？

private:
	Calculagraph calcugraph_;
	bool enabled_;
};

#endif  // _SETTING_SCREEN_SAVER_H__
