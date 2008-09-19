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

}

bool WebHistoryRecorderSetting::recordAllPages() const {
	if (isEnable() ) {
		return recordPage_;
	} else {
		return false;
	}
}
bool WebHistoryRecorderSetting::recordPornPages() const	{
	if (isEnable() ) {
		return recordPornPage_;
	} else {
		return false;
	}
}
bool WebHistoryRecorderSetting::recordPornImage() const	{
	if (isEnable() ) {
		return recordImage_;
	} else {
		return false;
	}
}
bool WebHistoryRecorderSetting::recordAllImage() const	{
	if (isEnable() ) {
		return recordPornImage_;
	} else {
		return false;
	}
}
bool WebHistoryRecorderSetting::recordAllWebsite() const {
	if (isEnable() ) {
		return recordWebsite_;
	} else {
		return false;
	}
}
bool WebHistoryRecorderSetting::recordPornWebsite() const {
	if (isEnable() ) {
		return recordPornWebsite_;
	} else {
		return false;
	}
}
