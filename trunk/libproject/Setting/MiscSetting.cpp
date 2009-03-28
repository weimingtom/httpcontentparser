#include "StdAfx.h"
#include ".\miscsetting.h"
#include <xmldefined.h>

MiscSetting::MiscSetting(void) {
}

MiscSetting::~MiscSetting(void) {
}

// Ä¬ÈÏÉèÖÃ
void MiscSetting::defaultSetting() {
	askMeAgain_SwitchChildren_ = true;
	switchChildrenOnClose_ = false;
}

int MiscSetting::parseConfig(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_APPSET_SWITCHTOCHILD_ONCLOSE));
	askMeAgain_SwitchChildren(enabledFromString(ele->Attribute(CONFIG_CONST_ENABLE)));
	switchChildrenOnClose(enabledFromString(ele->Attribute(CONFIG_SWITCHTOCHILD_ONCLOSE_ASKMEAG)));
	return 0;
}

TiXmlElement *  MiscSetting::saveConfig(TiXmlElement * root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_APPSET_SWITCHTOCHILD_ONCLOSE);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(switchChildrenOnClose_));
	rule_root->SetAttribute(CONFIG_SWITCHTOCHILD_ONCLOSE_ASKMEAG, enabledFromBool(askMeAgain_SwitchChildren_));
	root->LinkEndChild(rule_root);
	return rule_root;

}