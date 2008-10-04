#include "StdAfx.h"
#include ".\eyecaresetting.h"
#include "authorize.h"
#include <passwordtype.h>
#include <assert.h>

using namespace std;

EyecareSetting::EyecareSetting() {
	defaultSetting();
}

EyecareSetting::~EyecareSetting(void) {
}

// Ĭ������
void EyecareSetting::defaultSetting() {
	authorize_ = NULL;
	force_locked_ = false;
	setState(EYECARE_TIME);

	setEnterTime(45 * 60);
	setEyecareTime(45 * 60);

	SettingItem::defaultSetting();
}

// ��֤����
bool EyecareSetting::checkPassword(const string &password) {
	assert (NULL != authorize_);
	return (authorize_->checkPassword(password, password_type));
}

// ��������
bool EyecareSetting::setPassword(const std::string &password, const std::string &oralPassword) {
	assert (NULL != authorize_);
	assert (password_type == PASSWORD_EYECARE);
	if (checkPassword(oralPassword)) {
		authorize_->setPassword(password, oralPassword, password_type);
		return true;
	} else {
		return false;
	}
}

bool EyecareSetting::setPasswordType(const int type) {
	assert (NULL != authorize_);
	assert (type == PASSWORD_SU || type == PASSWORD_EYECARE);
	password_type = type;
	return true;
}

void EyecareSetting::initialize(Authorize *authorize, int state) {
	assert (NULL == authorize_);
	assert (NULL != authorize);
	authorize_ = authorize;

	password_type = PASSWORD_SU;

	// ���õ�ǰ״̬
	assert (state == EYECARE_TIME || state== ENTERT_TIME);
	setState(state);
}

bool EyecareSetting::trySwitch() {
	if (force_locked_ == true) {
		setState(EYECARE_TIME);
		return false;
	} else {
		return calculagraph_.trySwitch();
	}
}

// ǿ�ƹر���Ļ
int EyecareSetting::ForceLockWnd() {
	force_locked_ = true;
	setState(EYECARE_TIME);
	return 0;
}

// �л�״̬
int EyecareSetting::switchState(const std::string &password) {
	// ���������״̬ת�䣬����Ҫ��֤����
	if (getState() == ENTERT_TIME) {
		setState(EYECARE_TIME);
	} else if (true == checkPassword(password)) {
		force_locked_ = false;
		setState(ENTERT_TIME);
	}

	return getState();
}