#ifndef _SETTING_WEBHISTORY_RECORDER_SETTING_H__
#define _SETTING_WEBHISTORY_RECORDER_SETTING_H__

#include <settingitem.h>
#include <configitem.h>
#include <xmldefined.h>
#include <autoclean.h>

class WebHistoryRecorderSetting  : public SettingItem , public ConfigItem {
public:
	WebHistoryRecorderSetting(void);
	~WebHistoryRecorderSetting(void);

public:
	// properties
	bool recordAllPages() const	;
	bool recordAllImage() const;
	bool recordAllWebsite() const;

	bool recordPornPages() const;
	bool recordPornImage() const;
	bool recordPornWebsite() const;

	void recordAllPages(const bool enable)	{ setModified(true); recordPage_ = enable;}
	void recordAllImage(const bool enable)	{ setModified(true); recordImage_ = enable;}
	void recordAllWebsite(const bool enable)	{ setModified(true); recordWebsite_ = enable;}


	void recordPornPages(const bool enable)   { setModified(true); recordPornPage_ = enable;}
	void recordPornImage(const bool enable)   { setModified(true); recordPornImage_ = enable;}
	void recordPornWebsite(const bool enable) { setModified(true); recordPornWebsite_ = enable;}
public:
	void defaultSetting();

	bool recordPage_;
	bool recordPornPage_;
	bool recordImage_;
	bool recordPornImage_;
	bool recordWebsite_;
	bool recordPornWebsite_;

public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * root);
	
private:
	// ∂¡»°WebHistory
	int getWebHistoryRecorder(TiXmlElement *ele);
	int enableWebHistoryRecord(const TCHAR *enable);
	int setWebHistoryRecord(const TCHAR *type, const TCHAR *enable);
	int setWebHistoryLastCleanTiime(const TCHAR * lastclean);
	
	// ±£¥Ê
	TiXmlElement * saveWebHistory(TiXmlElement * app_root);

	// auto clean
	int setWebHistoryAutoCleanTimespan(const TCHAR *timespan);
	int setWebHistoryAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint);
	int setWebHistoryAutoClean(TiXmlElement * element);
	int enableWebHistoryAutoClean(const TCHAR *enable);
		
public:
	AutoClean*	getAutoclean() { return &webhistory_auto_clean_;}
private:
	AutoClean	webhistory_auto_clean_;
};

#endif // _SETTING_WEBHISTORY_RECORDER_SETTING_H__
