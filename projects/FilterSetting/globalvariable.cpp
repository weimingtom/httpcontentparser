#include "stdafx.h"
#include ".\globalvariable.h"
#include <softwareStatus.h>

// extern Authorize g_authorize;
XMLConfiguration g_configuration;
HINSTANCE g_hInstance;
SeachKeywordUtil g_searchwordUtil;
WebsitesUtil g_websitesUtil;

namespace {
software_encrypt::LicenseInfo g_licenseInfo;
};

int getAppStatus() {
	if ( true == g_configuration.uninstall()) {
		return SNOWMAN_STATUS_UNINSTALL;
	} else {
		return  g_licenseInfo.getAppStatus();
	}
}

int refreshAppstatus() {
	g_licenseInfo.initialize();
	SettingItem::setAppStatus(getAppStatus());
	return 0;
}

int getInstallDays() {
	return g_licenseInfo.getInstallDays();
}

bool tryRegister(const char *sn) {
	return g_licenseInfo.regApp(sn);
}

bool registered() {
	return g_licenseInfo.registered();
}