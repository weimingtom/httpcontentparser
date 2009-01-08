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


bool ContentCheckSetting::isSettingNeedCheck(const unsigned type) const {
	if( content_type_ & type )
		return true;
	else
		return false;
}
bool ContentCheckSetting::needCheck(const unsigned type) const {
	if (isEnabled() == true) {
		return isSettingNeedCheck(type);
	} else {
		return false;
	}
}

bool ContentCheckSetting::needCheckBySize(const int size) const {
	if (size < min_check_size_) 
		return false;

	// 如果最大的值为0， 则不限制最大值
	if (0 == max_check_size_) 
		return true;

	if (size > max_check_size_)
		return false;

	return true;
}

void ContentCheckSetting::defaultSetting() {
	SettingItem::defaultSetting();
	image_tightness_ = 2;

	min_check_size_ = 1;
	max_check_size_ = 64;
	enabled_check_by_size_ = true;
}

void ContentCheckSetting::getCheckedScope(long * scope_min, long * scope_max) {
	assert (scope_min && scope_max);
	*scope_min = min_check_size_;
	*scope_max = max_check_size_;
}

bool ContentCheckSetting::enabledCheckBySize() const {
	return enabled_check_by_size_;
}
void ContentCheckSetting::enableCheckBySize(const bool enabled) {
	enabled_check_by_size_ = enabled;
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
	item_jpg->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingNeedCheck(IMAGE_TYPE_JPEG)));
	rule_root->LinkEndChild(item_jpg);

	// bmp
	TiXmlElement *item_bmp = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_bmp->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_BMP);
	item_bmp->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingNeedCheck(IMAGE_TYPE_BMP)));
	rule_root->LinkEndChild(item_bmp);

	// gif
	TiXmlElement *item_gif = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_gif->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_GIF);
	item_gif->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingNeedCheck(IMAGE_TYPE_GIF)));
	rule_root->LinkEndChild(item_gif);

	// png
	TiXmlElement *item_png = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_png->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_PNG);
	item_png->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingNeedCheck(IMAGE_TYPE_PNG)));
	rule_root->LinkEndChild(item_png);

	// scope
	TCHAR buffer[MAX_PATH];
	TiXmlElement *item_scope = new TiXmlElement(CONFIG_NODE_IMAGESCOPE);
	item_scope->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(enabledCheckBySize()));
	item_scope->SetAttribute(CONFIG_CONST_MIN, _itot(min_check_size_, buffer, 10));
	item_scope->SetAttribute(CONFIG_CONST_MAX, _itot(max_check_size_, buffer, 10));
	rule_root->LinkEndChild(item_scope);

	root->LinkEndChild(rule_root);
	return rule_root;
}

//========================================================
// 图片规则
int ContentCheckSetting::setImageCheck(const TCHAR *node_name, const TCHAR *enable) {
	if (NULL == node_name || NULL == enable)
		return -1;

	bool a = enabledFromString(enable);
	if (0 == _tcscmp(node_name, CONFIG_NODE_IMAGETYPE_JPG)) {
		enableCheck(IMAGE_TYPE_JPEG, enabledFromString(enable));
	} else if (0 == _tcscmp(node_name, CONFIG_NODE_IMAGETYPE_BMP)) {
		enableCheck(IMAGE_TYPE_BMP, enabledFromString(enable));
	} else if (0 == _tcscmp(node_name, CONFIG_NODE_IMAGETYPE_GIF)) {
		enableCheck(IMAGE_TYPE_GIF, enabledFromString(enable));
	} else if (0 == _tcscmp(node_name, CONFIG_NODE_IMAGETYPE_PNG)) {
		enableCheck(IMAGE_TYPE_PNG, enabledFromString(enable));
	} else if (0 == _tcscmp(node_name, CONFIG_NODE_IMAGESCOPE)) {
		enableCheckBySize(enabledFromString(enable));
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
		const char * p = ele->Value();
		if (NULL != ele && 0 == _tcscmp(ele->Value(), CONFIG_NODE_IMAGE_CHECK_ITEM)) {// 如果是check
			setImageCheck(ele->Attribute(CONFIG_NODE_IMAGETYPE), ele->Attribute(CONFIG_CONST_ENABLE));
		} else if (NULL != ele && 0 == _tcscmp(ele->Value(), CONFIG_NODE_IMAGESCOPE)) {// 如果是scope
			enableCheckBySize(enabledFromString(ele->Attribute(CONFIG_CONST_ENABLE)));
			setCheckScope(_ttoi(ele->Attribute(CONFIG_CONST_MIN)), _ttoi(ele->Attribute(CONFIG_CONST_MAX)));
		}

		node = node->NextSibling();
	}
	return 0;
}