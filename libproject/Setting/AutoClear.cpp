#include "StdAfx.h"
#include ".\autoclear.h"

#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <assert.h>

//===========================================
// construtor and deconstructor
AutoClear::AutoClear(void) {
	defaultSetting();
}

AutoClear::~AutoClear(void) {
}

bool AutoClear::shouldExec() {
	// 获取当前时间
	_timeb tm;
	_ftime(&tm);
}
//===========================================
//
void AutoClear::defaultSetting() {
	max_ = 30 * 24 * 60 * 60 * 1000;
	min_ = 24 * 60 * 60 * 1000;

	timespan_ = min_ * 2;

	enable_ = true;

	reset();
}


// 设置时间范围
void AutoClear::setScale(const __time64_t min, const __time64_t max) {
	assert ( max > min);
}

void AutoClear::reset() {
	_ftime(&last_time_);
}