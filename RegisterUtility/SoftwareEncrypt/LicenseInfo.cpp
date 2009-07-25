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
		// TODO ��ȡʲô�����أ� ����û�
		internal_utility::storeSN(sn);
		// ����ע���룬 ��ʹ�Ǵ����ҲҪ������
		// ��ȷ���򱣴棬 ���򱣳�ԭ״̬
		sn_ = sn;
		return true;
	} else {
		return false;
	}
}
// �Ƿ��Ѿ�ע����
bool LicenseInfo::registered() {
	assert (true == initialized_);

	return validateSN(sn_);
}

int LicenseInfo::getDaysLeft() {
	return REG_SOFTWARE_TRAIL_DAYES - getInstallDays();
}

// ��ȡ��װʱ��
int LicenseInfo::getInstallDays() {
	assert(true == initialized_);
	boost::posix_time::ptime cur = boost::posix_time::second_clock::local_time();
	boost::posix_time::time_duration td = cur - install_time_;
	// ����Ǹ�����˵�����ڴ���
	if (td.is_negative()) {
		return MAX_DAYS;
	} else {
		return static_cast<unsigned int>(td.hours() / 24);
	}
}
void LicenseInfo::initialize() {
	// �ڳ�ʼ����ʱ���ȡ��װʱ��
	install_time_ = getInstallDataTime();

	// ��ȡSN
	sn_ = internal_utility::getSN();
	initialized_ = true;

	// �޸�
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