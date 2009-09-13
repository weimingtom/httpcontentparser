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
	static void setAppStatus(const int status) { app_status_ = status;}
	static int getAppStatus() { return app_status_;}
private:
	static int current_mode_;
	static int  app_status_;
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
	friend void TestSeachRuleSetting();
	friend void testJustPassedWhiteDNS();
	friend void TestSetLeft();
	friend void TestTwoWrong();
	friend void testAutoclean();
	friend void TestCheckPassword();
	friend void TestOnlineHour();
	friend void TestTwoModel();
	friend void TestParentMode();
	friend class ProgramControl;
	friend class MiscSetting;
};

#endif  // _SETTING_SETTINGITEM_H__
