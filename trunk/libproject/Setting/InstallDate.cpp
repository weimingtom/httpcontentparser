#include "StdAfx.h"
#include ".\installdate.h"

InstallDate::InstallDate(void)
{
}

InstallDate::~InstallDate(void)
{
}


int InstallDate::parseConfig(TiXmlElement * rule_root) {
	TiXmlElement *ele = rule_root->ToElement();
	setInstallDate(ele->Attribute(CONFIG_ITEM_MODEL_DATE));
	return 0;
}
TiXmlElement *  InstallDate::saveConfig(TiXmlElement * app_root) {
	TiXmlElement * item_root = new TiXmlElement(CONFIG_ITEM_MODEL_INSTALL);
	item_root->SetAttribute(CONFIG_ITEM_MODEL_DATE, getInstallDate().c_str());

	app_root->LinkEndChild(item_root);

	return item_root;
}