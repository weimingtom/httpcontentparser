#ifndef _SETTING_WEBHISTORY_RECORDER_SETTING_H__
#define _SETTING_WEBHISTORY_RECORDER_SETTING_H__

class WebHistoryRecorderSetting {
public:
	WebHistoryRecorderSetting(void);
	~WebHistoryRecorderSetting(void);

public:
	// properties
	bool recordAllPages() const			{ return recordPage_;}
	bool recordPornPages() const		{ return recordPornPage_;}
	bool recordPornImage() const		{ return recordImage_;}
	bool recordAllImage() const			{ return recordPornImage_;}
	bool recordAllWebsite() const			{ return recordWebsite_;}
	bool recordPornWebsite() const		{ return recordPornWebsite_;}

	void recordAllPages(const bool enable)		{ recordPage_ = enable;}
	void recordPornPages(const bool enable)	{ recordPornPage_ = enable;}
	void recordPornImage(const bool enable) { recordImage_ = enable;}
	void recordAllImage(const bool enable)	{ recordPornImage_ = enable;}
	void recordAllWebsite(const bool enable)	{ recordWebsite_ = enable;}
	void recordPornWebsite(const bool enable) { recordPornWebsite_ = enable;}

	void initialize();
public:
	bool recordPage_;
	bool recordPornPage_;
	bool recordImage_;
	bool recordPornImage_;
	bool recordWebsite_;
	bool recordPornWebsite_;
};

#endif // _SETTING_WEBHISTORY_RECORDER_SETTING_H__
