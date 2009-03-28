#ifndef _SETTING_MISCSETTING_H__
#define _SETTING_MISCSETTING_H__

#include ".\configitem.h"

// 用于保存应用程序的一些设置
class MiscSetting : public ConfigItem {
public:
	MiscSetting(void);
	~MiscSetting(void);

	bool askMeAgain_SwitchChildren() const { return askMeAgain_SwitchChildren; }
	bool switchChildrenOnClose() const { switchChildrenOnClose_;}

	void askMeAgain_SwitchChildren(const bool askme) { askMeAgain_SwitchChildren_ = askme; } 
	void switchChildrenOnClose(const bool switched) { switchChildrenOnClose_ = switched; } 

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
