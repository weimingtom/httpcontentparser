#include "StdAfx.h"
#include ".\programcontrol.h"
#include <xmldefined.h>

ProgramControl::ProgramControl(void) {
}

ProgramControl::~ProgramControl(void) {
}

// 检测应用程序是否合法
bool ProgramControl::check(const strutility::_tstring & fullpath) {
	if (false == isEnabled())
		return true;

	PROGRAM_INFO::const_iterator iter = data_.find(fullpath);
	if (data_.end() == iter) {
		return true;
	} else {
		return false;
	}
}

int ProgramControl::addItem(const strutility::_tstring &fullpath) {
	if (fullpath.length() == 0) {
		return 0;
	}

	data_.insert(std::make_pair(fullpath, new FILEINFO));
	setModified(true);
	return 0;
}

int ProgramControl::removeitem(const strutility::_tstring &fullpath) {
	PROGRAM_INFO::iterator iter = data_.find(fullpath);
	if (data_.end() != iter) {
		data_.erase(iter);
		setModified(true);
		delete iter->second;
	}

	return 0;
}

// 枚举函数
int ProgramControl::getFirstItem(strutility::_tstring *name, FILEINFO** info) {
	if (data_.size() == 0)
		return 0;
	
	// 获取数据
	*name = data_.begin()->first;
	*info = data_.begin()->second;

	return -1;
}
int ProgramControl::getNextItem(const strutility::_tstring & cur, strutility::_tstring *name, FILEINFO** info) {
	assert(cur.length() != 0);

	PROGRAM_INFO::const_iterator iter = data_.upper_bound(cur);
	if (iter != data_.end()) {
		*name = iter->first;
		*info = iter->second;
		return -1;
	} else {
		return 0;
	}
}

// 从XML中读取应用程序设置
int ProgramControl::parseConfig(TiXmlElement * item_root)  {
	enable(enabledFromString(item_root->Attribute(CONFIG_CONST_ENABLE)));
	TiXmlNode * node = item_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			addItem(ele->Attribute(CONFIG_ITEM_APPSET_PROGRAM_ITEM_PATH));
		}
		node = node->NextSibling();
	}
	return 0;
}

// 保存应用程序设置
TiXmlElement * ProgramControl:: saveConfig(TiXmlElement * item_root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_ITEM_APPSET_PROGRAM_CONTROL);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingEnabled()));

	PROGRAM_INFO::iterator iter = data_.begin();
	for (; iter != data_.end(); ++iter) {
			TiXmlElement * item = new TiXmlElement(CONFIG_ITEM_APPSET_PROGRAM_ITEM);
			item->SetAttribute(CONFIG_ITEM_APPSET_PROGRAM_ITEM_PATH, iter->first.c_str());
			rule_root->LinkEndChild(item);
	}

	item_root->LinkEndChild(rule_root);
	return rule_root;
}