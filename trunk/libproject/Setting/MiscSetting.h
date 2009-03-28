#ifndef _SETTING_MISCSETTING_H__
#define _SETTING_MISCSETTING_H__

#include <settingitem.h>
#include <configitem.h>

// 用于保存应用程序的一些设置
class MiscSetting : public ConfigItem, public SettingItem {
public:
	MiscSetting(void);
	~MiscSetting(void);

	bool askMeAgain_SwitchChildren() const { return askMeAgain_SwitchChildren; }
	bool switchChildrenOnClose() const {return  switchChildrenOnClose_;}

	void askMeAgain_SwitchChildren(const bool askme) { setModified(true); askMeAgain_SwitchChildren_ = askme; } 
	void switchChildrenOnClose(const bool switched) { setModified(true); switchChildrenOnClose_ = switched; } 

public:
	void defaultSetting();
private:
	bool askMeAgain_SwitchChildren_;
	bool switchChildrenOnClose_;
	// XML
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * root);
};

#endif  // _SETTING_MISCSETTING_H__
