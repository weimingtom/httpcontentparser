#ifndef _SETTING_SETTINGITEM_H__
#define _SETTING_SETTINGITEM_H__

class SettingItem {
public:
	SettingItem(void);
	~SettingItem(void);

	enum {
		MODE_PARENT = 0,
		MODE_CHILD
	};
	
	virtual bool isEnabled() const;
	virtual void enable(const bool enable);
protected:
	bool enabled_;
	void defaultSetting();

//====================================
// øÿ÷∆ «∑Òœ‘ æ
public:
	static int getModel()  { return current_mode_;}
	static void setModel(const int mode);
private:
	static int current_mode_;

public:
	static bool isModified() {
		return modified_;
	}

public:
	bool isSettingEnabled() const { return enabled_;}
protected:
	static void setModified(const bool modified) {
		modified_ = modified;
	}
private:
	static bool modified_;

private:
	// for test
	friend class AutocleanTest;
	friend class AuthorizeTest;
	friend class ContentSettingTest;
	friend class DNSSettingTest;
	friend class EyecareTest;
	friend class WebHistoryRecordTest;
	friend class HotkeySettingTest;
	friend class OnlineHourSettingTest;
	friend class SearchRuleTest;
};

#endif  // _SETTING_SETTINGITEM_H__
