#include "StdAfx.h"
#include ".\contentchecksetting.h"

ContentCheckSetting::ContentCheckSetting(void) {
}

ContentCheckSetting::~ContentCheckSetting(void) {
}


//==========================
// member functions
void ContentCheckSetting::enableCheck(const bool checked, const unsigned type) {
	if (checked == true) {
		content_type_ |= type;
	} else {
		content_type_ ^= type;
	}
}

bool ContentCheckSetting::needCheck(const unsigned type) const {
	if( content_type_ & type )
		return true;
	else
		return false;
}