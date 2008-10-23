#include "StdAfx.h"
#include ".\onlinehoursetting.h"
#include <assert.h>

OnlineHourSetting::OnlineHourSetting(void) {
	defaultSetting();
}

OnlineHourSetting::~OnlineHourSetting(void) {
}


//===============================================
// 
bool OnlineHourSetting::getHour(const DWORD full) {
	assert(LOWORD(full) < 7);
	assert(HIWORD(full) <24);

	if (isEnabled() == false) {
		return true;
	}

	if (online_hour_.find(full) == online_hour_.end()) {
		return true;
	} else {
		return false;
	}
}
bool OnlineHourSetting::getHour(const DWORD day, const DWORD hour) {
	assert(day < 7);
	assert(hour<24);
	return getHour(static_cast<DWORD>(MAKELPARAM(day, hour)));
}

void OnlineHourSetting::setHour(const DWORD full, const bool allow_access) {
	setModified(true);

	assert(LOWORD(full) < 7);
	assert(HIWORD(full) <24);
	if (allow_access == false) {
		online_hour_.insert(full);
	} else {
		// 查抄，如果存在则从offline hour中删除
		OFFLINE_HOUR::iterator iter = online_hour_.find(full);
		if (iter != online_hour_.end()) {
			online_hour_.erase(iter);
		}
	}
}

void OnlineHourSetting::setHour(const DWORD day, const DWORD hour, const bool allow_access) {
	assert(day < 7);
	assert(hour<24);
	return setHour(static_cast<DWORD>(MAKELPARAM(day, hour)), allow_access);
}

void OnlineHourSetting::enumBlockHour(Enumerator2<int, int> *enumerator) {
	OFFLINE_HOUR::iterator iter = online_hour_.begin();
	for (; iter != online_hour_.end(); ++iter) {
		enumerator->Enum(static_cast<int>(LOWORD(*iter)), static_cast<int>(HIWORD(*iter)));
	}
}

//==========================================
// XML file read
int OnlineHourSetting::parseConfig(TiXmlElement * item_root) {
	getOnlinetime(item_root);
	return 0;
}
TiXmlElement * OnlineHourSetting::saveConfig(TiXmlElement * item_root) {
	return saveOnlineHour(item_root);
}

int OnlineHourSetting::onlineBlocktime(const TCHAR *time) {
	if (NULL == time)
		return -1;

	// 解析时间
	char *p1 = _tcsstr(time, CONFIG_ONLINETIME_SEPERATE);
	assert (NULL != p1);
	char *p2 = p1;
	int day = _tcstol(time, &p2, 10);
	assert (p1 == p2);
	int hour = _tcstol(p1 + 1, NULL, 10);
	
	setHour(day, hour, false);
	return 0;
}


int OnlineHourSetting::getOnlinetime(TiXmlElement * rule_root) {
	// 是否可用
	TiXmlElement *ele = rule_root->ToElement();
	bool enabled = true;
	if (ele != NULL) {
		enabled = enabledFromString(ele->Attribute(CONFIG_CONST_NAME));
	}
	enable(enabled);

	// 获取不可上网的时间
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			onlineBlocktime(ele->GetText());
		}

		node = node->NextSibling();
	}
	return 0;
}

namespace {
class EnumOnlineHour : public Enumerator2<int, int> {
public:
	char * genBlocktime(const int day, const int hour) {
		_sntprintf(buffer, 1024, "%d%s%d", day, CONFIG_ONLINETIME_SEPERATE, hour);
		return buffer;
	}

	virtual int Enum(const int day, const int hour) {
		TiXmlElement * blocktime = new TiXmlElement(CONFIG_NODE_NAME_BLACKTIME);

		TiXmlText * itemitem = new TiXmlText(genBlocktime(day, hour));

		blocktime->LinkEndChild(itemitem);
		rule_root_->LinkEndChild(blocktime);

		return 0;
	}
public:
	EnumOnlineHour(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
	}
private:
	TiXmlElement * rule_root_;
	TCHAR buffer[1024];	// 避免重复
};
};

TiXmlElement * OnlineHourSetting::saveOnlineHour(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_ONLINETIME);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(enabled_));

	enumBlockHour(&EnumOnlineHour(rule_root));
	
	root->LinkEndChild(rule_root);
	return rule_root;
}
