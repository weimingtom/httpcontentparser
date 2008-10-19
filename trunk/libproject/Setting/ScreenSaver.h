#ifndef _SETTING_SCREEN_SAVER_H__
#define _SETTING_SCREEN_SAVER_H__

#include <settingitem.h>
#include <configitem.h>
#include <xmldefined.h>
#include <autoclean.h>
#include "calculagraph.h" 

class ScreenSaver : public SettingItem , public ConfigItem {
public:
	ScreenSaver(void);
	~ScreenSaver(void);

	//=====
	int getTimeSpan() const; // seconds
	void setTimeSpan(const int seconds);

	bool shouldSave(); // 现在应该Save了吗？
private:
	void defaultSetting();

	Calculagraph calcugraph_;

// XML file
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual int saveConfig(TiXmlElement * root);

private:
		// Screensaver
	int getScreensave(TiXmlElement * ele);
	int enableScreensave(const TCHAR *enable);
	int setScreensaveTimespan(const TCHAR *timespan);
	int setScreensaveAutoClean(TiXmlElement * ele);
	int enableScreenSaveAutoClean(const TCHAR *enabled);
	int setScreensaveAutoCleanTimespan(const TCHAR *timespan);
	int setScreensaveAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint);
	int setScreensaveLastCleanTiime(const TCHAR * lastclean);

	// 保存Screen Save
	int saveScreensave(TiXmlElement * root);

	// auto clean
public:
	AutoClean * getAutoClean() { return &auto_clean_; }
private:
	AutoClean	auto_clean_;
};

#endif  // _SETTING_SCREEN_SAVER_H__
