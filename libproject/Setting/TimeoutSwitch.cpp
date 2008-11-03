#include "StdAfx.h"
#include ".\timeoutswitch.h"
#include <assert.h>


TimeoutSwitch::TimeoutSwitch(void) {
	defaultSetting();
}

TimeoutSwitch::~TimeoutSwitch(void) {
	
}


// 启动计时器
void TimeoutSwitch::startTimer() {
	if (isSettingEnabled() == true) {
		calcugraph_.initialize();
		calcugraph_.setTimespan(timespan_);	
	}
}

bool TimeoutSwitch::shouldSwitch()  {
	// 当用户处于子模式时，永远返回FALSE
	if (SettingItem::MODE_CHILD == SettingItem::getModel()) {
		return false;
	}

	// 处于不可用状态
	// 这里应该是不受Parent_model的影响
	if (isSettingEnabled() == false) {
		return false;
	}

	return calcugraph_.trySwitch();
}

// 默认设置
void TimeoutSwitch::defaultSetting() {
	enable(true);
	min_ = 60;		// 最小值一分钟
	max_ = 60 * 60;
	setTimeoutValue(60); 
	startTimer();
}


// 获取和设置
int TimeoutSwitch::getTimeoutValue() const {
	return timespan_;
}
void TimeoutSwitch::setTimeoutValue(const int seconds) {
	setModified(true); 

	// 使用取值范围内的值
	if (seconds > max_)
		timespan_ = max_;
	else if (seconds  < min_) 
		timespan_ = min_;
	else 
		timespan_ = seconds;

	calcugraph_.setTimespan(seconds);
}


// XML
int TimeoutSwitch::parseConfig(TiXmlElement * item_root) {
	assert (0 == _tcscmp(item_root->Value(), CONFIG_ITEM_MODEL_AUTOSWITCH));
	setRange(atoi(item_root->Attribute(CONFIG_CONST_MIN)), atoi(item_root->Attribute(CONFIG_CONST_MAX)));
	setTimeoutValue(atoi(item_root->Attribute(CONSIG_CONST_TIMESPAN)));
	enable(enabledFromString(item_root->Attribute(CONFIG_CONST_ENABLE)));
	return 0;
}
TiXmlElement * TimeoutSwitch::saveConfig(TiXmlElement * root) {
	TCHAR buffer[MAX_PATH];
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_ITEM_MODEL_AUTOSWITCH);
	rule_root->SetAttribute(CONFIG_CONST_MAX, _itot(getRangeMax(), buffer, 10));
	rule_root->SetAttribute(CONFIG_CONST_MIN, _itot(getRangeMin(), buffer, 10));
	rule_root->SetAttribute(CONSIG_CONST_TIMESPAN, _itot(getTimeoutValue(), buffer, 10));
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingEnabled()));

	root->LinkEndChild(rule_root);
	return rule_root;
}