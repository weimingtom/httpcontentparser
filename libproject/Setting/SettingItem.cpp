#include "StdAfx.h"
#include ".\settingitem.h"
#include <assert.h>

//==========================================
// static members
void SettingItem::setModel(const int mode) {
	assert (MODE_CHILD == mode || MODE_PARENT == mode);
	current_mode_ = mode;
}

int SettingItem::current_mode_ = SettingItem::MODE_CHILD;

//==========================================
//
SettingItem::SettingItem(void) {
}

SettingItem::~SettingItem(void) {
}

// ƒ¨»œ…Ë÷√
void SettingItem::defaultSetting() {
	enabled_ = true;
}


bool SettingItem::isEnabled() const {
	if (current_mode_ == MODE_CHILD) {
		return enabled_;
	} else {
		return false;
	}
}
void SettingItem::enable(const bool enable) {
	enabled_ = enable;
}
