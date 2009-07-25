#ifndef _SETTING_SCREEN_SAVER_H__
#define _SETTING_SCREEN_SAVER_H__

#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>
#include <setting\autoclean.h>
#include "calculagraph.h" 

class Screenshot : public SettingItem , public ConfigItem {
public:
	Screenshot(void);
	~Screenshot(void);

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
	virtual TiXmlElement * saveConfig(TiXmlElement * root);

private:
	// Screenshot
	int getScreenshot(TiXmlElement * ele);
	int enableScreenshot(const TCHAR *enable);
	int setScreenshotTimespan(const TCHAR *timespan);
	int setScreenshotAutoClean(TiXmlElement * ele);
	int enableScreenshotAutoClean(const TCHAR *enabled);
	int setScreenshotAutoCleanTimespan(const TCHAR *timespan);
	int setScreenshotAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint);
	int setScreenshotLastCleanTiime(const TCHAR * lastclean);

	// 保存Screen Save
	TiXmlElement * saveScreensave(TiXmlElement * root);

	// auto clean
public:
	AutoClean * getAutoClean() { return &auto_clean_; }
private:
	AutoClean	auto_clean_;
};

#endif  // _SETTING_SCREEN_SAVER_H__
