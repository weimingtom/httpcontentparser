#include "StdAfx.h"
#include "webhistoryrecordersetting.h"

WebHistoryRecorderSetting::WebHistoryRecorderSetting(void) {
	defaultSetting();
}

WebHistoryRecorderSetting::~WebHistoryRecorderSetting(void) {
}

void WebHistoryRecorderSetting::defaultSetting() {
	enabled_ = true;

	recordPornPage_ = true;
	recordPornImage_ = true;
	recordPornWebsite_ = true;

	recordImage_ = false;
	recordPage_ = false;
	recordWebsite_ = false;

	SettingItem::defaultSetting();
}

bool WebHistoryRecorderSetting::recordAllPages() const {
	if (isEnabled() ) {
		return recordPage_;
	} else {
		return false;
	}
}


bool WebHistoryRecorderSetting::recordAllImage() const	{
	if (isEnabled() ) {
		return recordImage_;
	} else {
		return false;
	}
}
bool WebHistoryRecorderSetting::recordAllWebsite() const {
	if (isEnabled() ) {
		return recordWebsite_;
	} else {
		return false;
	}
}

bool WebHistoryRecorderSetting::recordPornImage() const	{
	if (isEnabled() ) {
		return recordPornImage_;
	} else {
		return false;
	}
}

bool WebHistoryRecorderSetting::recordPornPages() const	{
	if (isEnabled() ) {
		return recordPornPage_;
	} else {
		return false;
	}
}

bool WebHistoryRecorderSetting::recordPornWebsite() const {
	if (isEnabled() ) {
		return recordPornWebsite_;
	} else {
		return false;
	}
}
