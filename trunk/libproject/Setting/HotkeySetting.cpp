#include "StdAfx.h"
#include ".\hotkeysetting.h"
#include <string>

HotkeySetting::HotkeySetting(const std::string &path,
	const std::string &name) : ConfigItem(path, name) {
}

HotkeySetting::~HotkeySetting(void) {
}

//===================================
// read config
int HotkeySetting::parseConfig(TiXmlElement * item_root) {
	return 0;
}
int HotkeySetting::saveConfig(TiXmlElement * root) {
	return 0;
}