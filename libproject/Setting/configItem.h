#ifndef _SETTING_CONFIGITEM_H__
#define _SETTING_CONFIGITEM_H__

#include <string>
#include <tinyXML\tinyxml.h>

// 所有从此类当中继承的类都可以从一个根节中读取配置信息
// 类如，如果一个类的路径为 "root/config/rules/rule" 切name ==某个值那我我们就进行处理
class ConfigItem {
public:
	int readconfig(TiXmlElement * item_root);
	int saveconfig(TiXmlElement * root);
protected:
	virtual int parseConfig(TiXmlElement * item_root) = 0;
	virtual int saveConfig(TiXmlElement * root) = 0;

	TiXmlElement * findItem(TiXmlElement * root);
protected:
	const std::string item_root_;
	const std::string name_;

	ConfigItem(const std::string &path, const std::string &name);
protected:
	ConfigItem() {}
};

#endif  // _SETTING_CONFIGITEM_H__