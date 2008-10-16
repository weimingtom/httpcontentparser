#include "StdAfx.h"
#include ".\calculagraph.h"

Calculagraph::Calculagraph(void) {
}

Calculagraph::~Calculagraph(void) {
}

void Calculagraph::Reset() {
	state_begin_ = GetTickCount();
}

bool Calculagraph::trySwitch() {
	if (getTimeEscape() > getTimespan()) {
		Reset();
		return true;
	} else {
		return false;
	}
}

void Calculagraph::setTimeEscape(const DWORD seconds) {
	state_begin_ = GetTickCount() - seconds * 1000;
}	


// …Ë÷√
void Calculagraph::setTimespan(const DWORD seconds) {
	time_span_ = seconds * 1000 + 5;
}

DWORD Calculagraph::getTimespan() const {
	return (int)(time_span_/1000);
}

DWORD Calculagraph::getTimeEscape() const {
	return (int)((GetTickCount() - state_begin_)/1000 + 1);
}