#include "StdAfx.h"
#include ".\contentchecksetting.h"

ContentCheckSetting::ContentCheckSetting(void) {
	content_type_ = 0;
	defaultSetting();
}

ContentCheckSetting::~ContentCheckSetting(void) {
}


//==========================
// member functions
void ContentCheckSetting::enableCheck(const unsigned type, const bool checked) {
	SettingItem::setModified(true);
	if (checked == true) {
		content_type_ |= type;
	} else {
		content_type_ &= ~type;
	}
}

bool ContentCheckSetting::needCheck(const unsigned type) const {
	if (isEnabled() == true) {
		if( content_type_ & type )
			return true;
		else
			return false;
	} else {
		return false;
	}
}

void ContentCheckSetting::defaultSetting() {
	SettingItem::defaultSetting();
	tightness_ = 2;
}

//============================
// XML
int ContentCheckSetting::parseConfig(TiXmlElement * item_root) {
	getImageRule(item_root);
	return 0;
}
TiXmlElement * ContentCheckSetting::saveConfig(TiXmlElement * item_root) {
	return saveImageRule(item_root);
}

//==========================================================
// 保存图片检测规则
TiXmlElement * ContentCheckSetting::saveImageRule(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_IMAGECHECK);

	// jgp
	TiXmlElement *item_jpg = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_jpg->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_JPG);
	item_jpg->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(needCheck(IMAGE_TYPE_JPEG)));
	rule_root->LinkEndChild(item_jpg);

	// bmp
	TiXmlElement *item_bmp = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_bmp->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_BMP);
	item_bmp->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(needCheck(IMAGE_TYPE_BMP)));
	rule_root->LinkEndChild(item_bmp);

	// gif
	TiXmlElement *item_gif = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_gif->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_GIF);
	item_gif->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(needCheck(IMAGE_TYPE_GIF)));
	rule_root->LinkEndChild(item_gif);

	// png
	TiXmlElement *item_png = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_png->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_PNG);
	item_png->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(needCheck(IMAGE_TYPE_PNG)));
	rule_root->LinkEndChild(item_png);

	root->LinkEndChild(rule_root);
	return rule_root;
}


//========================================================
// 图片规则
int ContentCheckSetting::setImageCheck(const TCHAR *imagetype, const TCHAR *enable) {
	if (NULL == imagetype || NULL == enable)
		return -1;

	bool a = enabledFromString(enable);
	if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_JPG)) {
		enableCheck(IMAGE_TYPE_JPEG, enabledFromString(enable));
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_BMP)) {
		enableCheck(IMAGE_TYPE_BMP, enabledFromString(enable));
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_GIF)) {
		enableCheck(IMAGE_TYPE_GIF, enabledFromString(enable));
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_PNG)) {
		enableCheck(IMAGE_TYPE_PNG, enabledFromString(enable));
	} else {
		assert (false);
		return -1;
	}
	return 0;
}


int ContentCheckSetting::getImageRule(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			setImageCheck(ele->Attribute(CONFIG_NODE_IMAGETYPE), ele->Attribute(CONFIG_CONST_ENABLE));
		}

		node = node->NextSibling();
	}
	return 0;
}