#include "StdAfx.h"
#include ".\contentchecksetting.h"

ContentCheckSetting::ContentCheckSetting(void) {
	content_type_ = 0;
	defaultSetting();
}

ContentCheckSetting::~ContentCheckSetting(void) {
}


//==========================
// member functions
void ContentCheckSetting::enableCheck(const unsigned type, const bool checked) {
	if (checked == true) {
		content_type_ |= type;
	} else {
		content_type_ ^= type;
	}
}

bool ContentCheckSetting::needCheck(const unsigned type) const {
	if (isEnabled() == true) {
		if( content_type_ & type )
			return true;
		else
			return false;
	} else {
		return false;
	}
}

void ContentCheckSetting::defaultSetting() {
	SettingItem::defaultSetting();
	tightness_ = 2;
}