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
};

#endif  // _SETTING_SETTINGITEM_H__
