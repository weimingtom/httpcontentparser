#include "StdAfx.h"
#include ".\licenseinfo.h"
#include ".\installDate.h"
#include ".\serialNumber.h"
#include "baseEncrypt.h"
#include <softwareStatus.h>
#include <app_constants.h>
#include <DebugOutput.h>

#define UNINSTALL_INDICATOR		TEXT("uninstall.dll")

#define __SOFTWAREENCRYPT_LICENSEINFO__(FMT) _DEBUG_STREAM_TRC_("[Family007][SoftwareEncrypt][LicenseInfo]"<<FMT )

namespace software_encrypt {
LicenseInfo::LicenseInfo(void) : initialized_(false){
}

LicenseInfo::~LicenseInfo(void) {
}

bool LicenseInfo::regApp(const std::string &sn) {
	if (validateSN(sn)) {
		// TODO 采取什么动作呢？ 如果用户
		internal_utility::storeSN(sn);
		// 保存注册码， 即使是错误的也要保存吗？
		// 正确了则保存， 否则保持原状态
		sn_ = sn;
		return true;
	} else {
		return false;
	}
}
// 是否已经注册了
bool LicenseInfo::registered() {
	assert (true == initialized_);

	return validateSN(sn_);
}

int LicenseInfo::getDaysLeft() {
	return REG_SOFTWARE_TRAIL_DAYES - getInstallDays();
}

// 获取安装时间
int LicenseInfo::getInstallDays() {
	assert(true == initialized_);
	boost::posix_time::ptime cur = boost::posix_time::second_clock::local_time();
	boost::posix_time::time_duration td = cur - install_time_;
	// 如果是负数，说明存在错误
	if (td.is_negative()) {
		return MAX_DAYS;
	} else {
		return static_cast<unsigned int>(td.hours() / 24);
	}
}
void LicenseInfo::initialize() {
	// 在初始化的时候获取安装时间
	install_time_ = getInstallDataTime();

	// 获取SN
	sn_ = internal_utility::getSN();
	initialized_ = true;

	// 修复
	setInstall();
}

int LicenseInfo::getAppStatus() {
	if (true == registered()) {
		return SNOWMAN_STATUS_REGISTERED;
	} else if (getDaysLeft() < 0) {
		return SNOWMAN_STATUS_OVERTIME;
	} else {
		return SNOWMAN_STATUS_TRIAL;
	}
}
};