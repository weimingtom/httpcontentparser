#ifndef _SETTING_WEBHISTORY_RECORDER_SETTING_H__
#define _SETTING_WEBHISTORY_RECORDER_SETTING_H__

#include <settingitem.h>

class WebHistoryRecorderSetting  : public SettingItem  {
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

	void recordAllPages(const bool enable)		{ recordPage_ = enable;}
	void recordAllImage(const bool enable)	{ recordImage_ = enable;}
	void recordAllWebsite(const bool enable)	{ recordWebsite_ = enable;}


	void recordPornPages(const bool enable)	{ recordPornPage_ = enable;}
	void recordPornImage(const bool enable) { recordPornImage_ = enable;}
	void recordPornWebsite(const bool enable) { recordPornWebsite_ = enable;}
public:
	void defaultSetting();

	bool recordPage_;
	bool recordPornPage_;
	bool recordImage_;
	bool recordPornImage_;
	bool recordWebsite_;
	bool recordPornWebsite_;
};

#endif // _SETTING_WEBHISTORY_RECORDER_SETTING_H__
