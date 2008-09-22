#include "StdAfx.h"
#include ".\screensaver.h"


void ScreenSaver::defaultSetting() {
	calcugraph_.initialize();
	enable(false);
	setTimeSpan(60 * 20); // 20 mins
}


//  «∑Òø…”√
bool ScreenSaver::isEnabled() const  {
	return enabled_;
}
void ScreenSaver::enable(const bool enabled) {
	enabled_ = enabled;
}

void ScreenSaver::setTimeSpan(const int seconds) {
	calcugraph_.setTimespan(seconds);
}

int ScreenSaver::getTimeSpan() const {
	return calcugraph_.getTimespan();
}

bool ScreenSaver::shouldSave() {
	if (false == isEnabled()) {
		return false;
	}
	return calcugraph_.trySwitch();
}

//==================================
// protected memberr


//===================================
// constructors and deconstructors
ScreenSaver::ScreenSaver(void) {
	defaultSetting();
}

ScreenSaver::~ScreenSaver(void) {
}


