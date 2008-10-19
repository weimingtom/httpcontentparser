#ifndef _SETTING_CONFIGITEM_H__
#define _SETTING_CONFIGITEM_H__

#include <string>
#include <tinyXML\tinyxml.h>

// ���дӴ��൱�м̳е��඼���Դ�һ�������ж�ȡ������Ϣ
// ���磬���һ�����·��Ϊ "root/config/rules/rule" ��name ==ĳ��ֵ�������Ǿͽ��д���
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