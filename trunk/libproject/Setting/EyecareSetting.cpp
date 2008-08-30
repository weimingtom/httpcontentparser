#include "StdAfx.h"
#include ".\eyecaresetting.h"
#include "authorize.h"
#include <passwordtype.h>
#include <assert.h>

using namespace std;

EyecareSetting::EyecareSetting() {
	authorize_ = NULL;
	force_locked_ = false;
}

EyecareSetting::~EyecareSetting(void) {
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

void EyecareSetting::initialize(Authorize *authorize) {
	assert (NULL == authorize_);
	assert (NULL != authorize);
	authorize_ = authorize;

	// ����״̬�л�ʱ��
	new_state_begin_ = GetTickCount();

	password_type = PASSWORD_SU;

	// ���õ�ǰ״̬
	state_ = EYECARE_TIME;

	setEntertainTime(3 * 60);
	setRestTime(3 * 60);
}

// ��ȡʱ��
int EyecareSetting::getEntertainTime() const {
	assert (NULL != authorize_);
	return entertain_time_ ;
}

int EyecareSetting::getRestTime() const {
	assert (NULL != authorize_);
	return rest_time_;
}

// ����ʱ��
void EyecareSetting::setEntertainTime(const int second) {
	assert (NULL != authorize_);
	entertain_time_ = second;
}

void EyecareSetting::setRestTime(const int second) {
	assert (NULL != authorize_);
	rest_time_  = second;
}

// �ı�״̬
int EyecareSetting::changeState(const int current) {
	assert (NULL != authorize_);
	if (current == ENTERTAINMENT_TIME) {
		state_ = EYECARE_TIME;
	} else if (current == EYECARE_TIME) {
		state_ = ENTERTAINMENT_TIME;
	} else {
		assert(false);
	}

	new_state_begin_ = GetTickCount();
	return 0;
}

// ��ȡʣ��ʱ��
int EyecareSetting::getRemainTime() const {
	if (true == force_locked_) {
		return 0x0FFFF; // ��������һ������0����
	}

	DWORD tick = GetTickCount();
	int remain;
	if (getState() == ENTERTAINMENT_TIME) {
		remain =  getEntertainTime() - (tick - new_state_begin_) / (1000 );
	} else {
		remain =  getRestTime() - (tick - new_state_begin_) / (1000);
	}

	return remain;
}

int EyecareSetting::trySwitch() {
	if (getRemainTime() <= 0) {
		changeState(getState());
	}
	return getState();
}

// ǿ�ƹر���Ļ
int EyecareSetting::ForceLockWnd() {
	force_locked_ = true;
	state_ = EYECARE_TIME;
	return 0;
}

// �л�״̬
int EyecareSetting::switchState(const std::string &password) {
	// ���������״̬ת�䣬����Ҫ��֤����
	if (state_ == ENTERTAINMENT_TIME) {
		changeState(state_);
	} else if (true == checkPassword(password)) {
		force_locked_ = false;
		changeState(state_);
	}

	return state_;
}