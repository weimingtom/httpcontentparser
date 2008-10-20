#include "StdAfx.h"
#include ".\configitem.h"
#include <utility/strutility.h>
#include <tinyXML\tinyxml.h>
#include <vector>
#include <string>

ConfigItem::ConfigItem(const std::string &path,
		  const std::string &name) : item_root_(path), name_(name) {
}

TiXmlElement * ConfigItem::findItem(TiXmlElement * root) {
	using namespace std;
	using namespace strutility;

	vector<_tstring> strs;
	splitstring(item_root_.c_str(), "\\", &strs);

	return NULL;
}

// ��ȡ����Ӧ�ڵ�
int ConfigItem::readconfig(TiXmlElement * item_root) {
	// �ҵ����Ӧ�ĵ�
	return parseConfig(item_root);
}

TiXmlElement * ConfigItem::saveconfig(TiXmlElement * item_root) {
	return saveConfig(item_root);
}