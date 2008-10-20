#ifndef _SETTING_HOTKEYSETTING_H__
#define _SETTING_HOTKEYSETTING_H__

#include <configitem.h>
#include <string>
#include <map>


// 读取热键的设置
class HotkeySetting : public ConfigItem {
public:
	HotkeySetting();
	~HotkeySetting(void);

	unsigned getHotkey(const std::string &name);
	void setHotkey(const std::string &name, const unsigned hotkey);
protected:
	typedef std::map<std::string, unsigned> HOTKEY_MAP;
	HOTKEY_MAP hotkeys_;

	void defaultSetting();
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * root);
};

#endif  // _SETTING_HOTKEYSETTING_H__
