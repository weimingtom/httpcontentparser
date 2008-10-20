#ifndef _SETTING_HOTKEYSETTING_H__
#define _SETTING_HOTKEYSETTING_H__

#include <configitem.h>
#include <string>

// ��ȡ�ȼ�������
class HotkeySetting : ConfigItem {
public:
	HotkeySetting(const std::string &path, const std::string &name);
	~HotkeySetting(void);

public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * root);
};

#endif  // _SETTING_HOTKEYSETTING_H__
