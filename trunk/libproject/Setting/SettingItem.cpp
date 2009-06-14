#include "StdAfx.h"
#include ".\settingitem.h"
#include <softwareStatus.h>
#include <DebugOutput.h>
#include <assert.h>


_INIT_FILESCOPT_OSTRSTREAM_

//==========================================
// static members
void SettingItem::setModel(const int mode) {
	assert (MODE_CHILD == mode || MODE_PARENT == mode);
	current_mode_ = mode;
}

int SettingItem::current_mode_ = SettingItem::MODE_CHILD;

bool SettingItem::modified_ = false;
int  SettingItem::app_status_ = SNOWMAN_STATUS_TRIAL;
//==========================================
//
SettingItem::SettingItem(void) {
}

SettingItem::~SettingItem(void) {
}

// 默认设置
void SettingItem::defaultSetting() {
	enabled_ = true;
}


bool SettingItem::isEnabled() const {
	// 如果软件状态处于过期，则应该永远返回false
	if (getAppStatus() == SNOWMAN_STATUS_OVERTIME) {
		_DEBUG_STREAM_TRC_<<"[Setting] ["<<__FUNCTION__<< "] Trial time is over";
		_OUTPUT_FMT_STRING_
		return false;
	}
	if (current_mode_ == MODE_CHILD) {
		return enabled_;
	} else {
		return false;
	}
}
void SettingItem::enable(const bool enable) {
	enabled_ = enable;
	setModified(true);
}
