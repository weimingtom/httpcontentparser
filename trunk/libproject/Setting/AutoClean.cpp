#include "StdAfx.h"
#include ".\autoclean.h"
#include ".\settingitem.h"
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <assert.h>
#include <utility/timeutility.h>

//===========================================
// construtor and deconstructor
AutoClean::AutoClean(void) {
	last_time_ = NULL;
	defaultSetting();
}

AutoClean::~AutoClean(void) {
	if (last_time_ != NULL) {
		delete last_time_;
	}
}

bool AutoClean::shouldExec() {
	assert (NULL != last_time_);
	// 如果不可用
	if (isEnable() == false) {
		return false;
	}

	CTime t = CTime::GetCurrentTime();
	CTimeSpan timespan = t - *last_time_;

	if (timespan.GetTotalHours() / 24 >= getTimespan()) {
		return true;
	} else {
		return false;
	}
}
// 设置时间间隔的范围
void AutoClean::setTimespan(const int days) {
	assert (getRangeMax() > getRangeMin());
	setModified(true); 

	if (days < getRangeMin())
		timespan_days_ = getRangeMin();
	else if (days > getRangeMax()) 
		timespan_days_ = getRangeMax();
	else 
		timespan_days_ = days;
}

// 设置时间范围
void AutoClean::setScale(const int min, const int max) {
	assert ( max > min);
	max_ = max;
	min_ = min;
}

// 充值时间
void AutoClean::reset() {
	assert (NULL != last_time_);
	*last_time_ = CTime::GetCurrentTime();
}

void AutoClean::setLastTime(LPCTSTR lpstr) {
	if (NULL != last_time_) {
		delete last_time_;
	}
	struct tm t = timeutility::tmfromstring(lpstr);
	last_time_ = new CTime(t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}

// 获取上一次的清理时间
std::string AutoClean::getLastTime() {
	assert (NULL != last_time_);
	TCHAR str[MAX_PATH];
	_sntprintf(str, MAX_PATH, "%04d-%02d-%02d %02d:%02d:%02d", 
		last_time_->GetYear(), last_time_->GetMonth(), last_time_->GetDay(),
		last_time_->GetHour(), last_time_->GetMinute(), last_time_->GetSecond());

	return std::string(str);
}

//===========================================
// 默认设置
void AutoClean::defaultSetting() {
	max_ = 30 ;
	min_ = 1 ;

	timespan_days_ = min_ * 3;

	enable_ = true;
	last_time_ = new CTime();
	reset();
}

