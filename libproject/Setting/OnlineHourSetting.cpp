#include "StdAfx.h"
#include ".\onlinehoursetting.h"
#include <assert.h>

OnlineHourSetting::OnlineHourSetting(void) {
	enable_rule_ = true;
}

OnlineHourSetting::~OnlineHourSetting(void) {
}

//===============================================
// 
bool OnlineHourSetting::getHour(const DWORD full) {
	assert(HIWORD(full) < 7);
	assert(LOWORD(full) <24);

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
	assert(HIWORD(full) < 7);
	assert(LOWORD(full) <24);
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