#include "StdAfx.h"
#include ".\autoclean.h"

#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <assert.h>

//===========================================
// construtor and deconstructor
AutoClean::AutoClean(void) {
	defaultSetting();
}

AutoClean::~AutoClean(void) {
}

bool AutoClean::shouldExec() {
	if (getCurrent() > clearTime())
		return true;
	else
		return false;
}
//===========================================
//
void AutoClean::defaultSetting() {
	max_ = 30 * 24 * 60 * 60 ;
	min_ = 24 * 60 * 60 ;

	timespan_ = min_ * 2;

	enable_ = true;

	reset();
}


// ÉèÖÃÊ±¼ä·¶Î§
void AutoClean::setScale(const __int64 min, const __int64 max) {
	assert ( max > min);
	max_ = max;
	min_ = min;
}

void AutoClean::reset() {
	SYSTEMTIME sys_time;
	GetSystemTime(&sys_time);
	SystemTimeToFileTime(&sys_time, (FILETIME*)&last_time_);
}

__int64 AutoClean::clearTime() {
	return timespan_ + last_time_;
}
__int64 AutoClean::getCurrent() {
	__int64 result;
	SYSTEMTIME sys_time;
	GetSystemTime(&sys_time);
	SystemTimeToFileTime(&sys_time, (FILETIME*)&result);
	return result;
}