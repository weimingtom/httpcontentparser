#include "StdAfx.h"
#include ".\licenseinfo.h"
#include ".\installDate.h"
#include ".\serialNumber.h"
#include "baseEncrypt.h"

namespace software_encrypt {

LicenseInfo::LicenseInfo(void) : initialized_(false){
}

LicenseInfo::~LicenseInfo(void) {
}

// 是否已经注册了
bool LicenseInfo::registered() {
	assert (true == initialized_);

	return validateSN(sn_);
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
	sn_ = getSN();
	initialized_ = true;
}

};