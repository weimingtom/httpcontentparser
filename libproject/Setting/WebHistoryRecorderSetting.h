#ifndef _SETTING_WEBHISTORY_RECORDER_SETTING_H__
#define _SETTING_WEBHISTORY_RECORDER_SETTING_H__

class WebHistoryRecorderSetting {
public:
	WebHistoryRecorderSetting(void);
	~WebHistoryRecorderSetting(void);

public:
	// properties
	bool recordAllPages() const	;
	bool recordPornPages() const;
	bool recordPornImage() const;
	bool recordAllImage() const;
	bool recordAllWebsite() const;
	bool recordPornWebsite() const;

	void recordAllPages(const bool enable)		{ recordPage_ = enable;}
	void recordPornPages(const bool enable)	{ recordPornPage_ = enable;}
	void recordPornImage(const bool enable) { recordImage_ = enable;}
	void recordAllImage(const bool enable)	{ recordPornImage_ = enable;}
	void recordAllWebsite(const bool enable)	{ recordWebsite_ = enable;}
	void recordPornWebsite(const bool enable) { recordPornWebsite_ = enable;}

	bool isEnable() const { return enabled_;}
	void enable(const bool enabled) { enabled_ = enabled; }
public:
	void defaultSetting();

	bool recordPage_;
	bool recordPornPage_;
	bool recordImage_;
	bool recordPornImage_;
	bool recordWebsite_;
	bool recordPornWebsite_;
	
	bool enabled_;
};

#endif // _SETTING_WEBHISTORY_RECORDER_SETTING_H__
