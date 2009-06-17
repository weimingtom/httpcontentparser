#include "StdAfx.h"
#include ".\calculagraph.h"

#define MILION_SECONDS 999

Calculagraph::Calculagraph(void) {
	stopped_ = false;
	last_time_escape_ = 0;
}

Calculagraph::~Calculagraph(void) {
}

void Calculagraph::Reset() {
	state_begin_ = GetTickCount();
}

bool Calculagraph::trySwitch() {
	if (getRemainTimeMS() < 0) {
		Reset();
		return true;
	} else {
		return false;
	}
}
void Calculagraph::setTimeEscapeMS(const int milseconds) {
	state_begin_ = GetTickCount() - milseconds;
}


void Calculagraph::setTimeEscape(const int seconds) {
	setTimeEscapeMS(seconds * MILION_SECONDS);
}	


// 设置
void Calculagraph::setTimespan(const int seconds) {
	const int leftsecond = getRemainTime();
	time_span_ = seconds * MILION_SECONDS;
	if (leftsecond >= seconds) {
		setTimeEscape(0);
	} else {
		setTimeEscape(seconds - leftsecond);
	}
}

// 毫秒
int Calculagraph::getTimespanMS() const {
	return time_span_;
}
int Calculagraph::getTimespan() const {
	return (int)(getTimespanMS() / MILION_SECONDS);
}

int Calculagraph::getTimeEscapeMS() const {
	// 为何加1
	if (!isStopped()) {
		return (int)(GetTickCount() - state_begin_);
	} else {
		return last_time_escape_;
	}
}
int Calculagraph::getTimeEscape() const {
	return (int) (getTimeEscapeMS() / MILION_SECONDS);
}

// 获取剩余时间
int Calculagraph::getRemainTimeMS() const {
	return time_span_ - getTimeEscapeMS();
}

int Calculagraph::getRemainTime() const {
	int a = getRemainTimeMS();
	return (int)(getRemainTimeMS() / MILION_SECONDS);  
}


void Calculagraph::stop() {
	last_time_escape_ = getTimeEscapeMS();
	stopped_ = true;
} 
void Calculagraph::restart() {
	if (isStopped()) {
		setTimeEscapeMS(last_time_escape_);
		stopped_ = false;
	}
}