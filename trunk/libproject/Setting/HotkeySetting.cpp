#include "StdAfx.h"
#include ".\hotkeysetting.h"

#include <configitem.h>
#include <xmldefined.h>
#include <map>
#include <string>


HotkeySetting::HotkeySetting() {
}

HotkeySetting::~HotkeySetting(void) {
}

// Ä¬ÈÏÉèÖÃ
void HotkeySetting::defaultSetting() {
	hotkeys_.insert(std::make_pair(CONFIG_HOTKEY_LAUNCH, 0));
	hotkeys_.insert(std::make_pair(CONFIG_HOTKEY_SHOWUI, 0));
	hotkeys_.insert(std::make_pair(CONFIG_HOTKEY_SWITCHUSER, 0));
}

unsigned HotkeySetting::getHotkey(const std::string &name) {
	HOTKEY_MAP::iterator iter = hotkeys_.find(name);
	if (hotkeys_.end() == iter) {
		return 0;
	} else {
		return iter->second;
	}
}
void HotkeySetting::setHotkey(const std::string &name, const unsigned hotkey) {
	hotkeys_[name] = hotkey;
	setModified(true);
}

//===================================
// read config
int HotkeySetting::parseConfig(TiXmlElement * item_root) {
	char * p;
	TiXmlNode * node = item_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			setHotkey(ele->Attribute(CONFIG_CONST_NAME), _tcstoul(ele->Attribute(CONFIG_HOTKEY_PROP_KEY), &p, 10));
		}

		node = node->NextSibling();
	}
	return 0;
}

TiXmlElement *  HotkeySetting::saveConfig(TiXmlElement * app_root) {
	TCHAR buffer[1024];
	TiXmlElement * item_root = new TiXmlElement(CONFIG_ITEM_APPSET_HOTKEY);

	HOTKEY_MAP::iterator iter = hotkeys_.begin();
	for (; iter != hotkeys_.end(); ++iter) {
		_sntprintf(buffer, 1024, "%u", iter->second);
		TiXmlElement * hotkey = new TiXmlElement(CONFIG_APPSET_HOTKEY_ITEM);
		hotkey->SetAttribute(CONFIG_CONST_NAME,		iter->first);
		hotkey->SetAttribute(CONFIG_HOTKEY_PROP_KEY, buffer);

		item_root->LinkEndChild(hotkey);
	}
	app_root->LinkEndChild(item_root);
	return item_root;
}
