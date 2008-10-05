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

// 默认设置
void EyecareSetting::defaultSetting() {
	authorize_ = NULL;
	force_locked_ = false;
	setState(EYECARE_TIME);

	setEnterTime(45 * 60);
	setEyecareTime(45 * 60);

	SettingItem::defaultSetting();

	after_eyecare_terminated_ = EYECARE_TERMIN_RESETTIMER;
}

// 验证密码
bool EyecareSetting::checkPassword(const string &password) {
	assert (NULL != authorize_);
	return (authorize_->checkPassword(password, password_type));
}

// 设置密码
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

// 获取当前状态
int EyecareSetting::getState() const {
	// 处于parent 模式时，永远处于enter mode
	if (SettingItem::getModel() == SettingItem::MODE_PARENT) {
		return EyecareSetting::ENTERT_TIME;
	}
	return calculagraph_.getCurrentState();
}

bool EyecareSetting::setPasswordType(const int type) {
	assert (NULL != authorize_);
	assert (type == PASSWORD_SU || type == PASSWORD_EYECARE);
	password_type = type;
	return true;
}

// 初始化设置
void EyecareSetting::initialize(Authorize *authorize, int state) {
	assert (NULL == authorize_);
	assert (NULL != authorize);
	authorize_ = authorize;

	password_type = PASSWORD_SU;

	// 设置当前状态
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

// 强制关闭屏幕
int EyecareSetting::ForceLockWnd() {
	force_locked_ = true;
	setState(EYECARE_TIME);
	return 0;
}

// 切换状态
int EyecareSetting::switchState(const std::string &password) {
	// 如果从娱乐状态转变，不需要验证密码
	if (getState() == ENTERT_TIME) {
		setState(EYECARE_TIME);
	} else if (true == checkPassword(password)) {
		force_locked_ = false;
		setState(ENTERT_TIME);

		if (getTerminatedMode() == EYECARE_TERMIN_RESETTIMER) {
			calculagraph_.Reset();
		} else {
			SettingItem::setModel(SettingItem::MODE_PARENT);
		}
	}

	return getState();
}