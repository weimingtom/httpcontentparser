#include "StdAfx.h"
#include ".\eyecaresetting.h"
#include "authorize.h"
#include <passwordtype.h>
#include <assert.h>

using namespace std;

namespace {
inline
const char * Eyecare_state(const int state) {
	if (state == EyecareSetting::ENTERT_TIME) {
		return CONFIG_APPSET_EYECARE_ENTER;
	} else if (state == EyecareSetting::EYECARE_TIME) {
		return CONFIG_APPSET_EYECARE_EYECARE;
	} else {
		assert(false); 
		return CONFIG_APPSET_EYECARE_EYECARE;
	}
}

};
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

// XML
int EyecareSetting::parseConfig(TiXmlElement * item_root) {
	getEyecareSetting(item_root);
	return 0;
}
int EyecareSetting::saveConfig(TiXmlElement * item_root) {
	saveEyecare(item_root);
	return 0;
}

//===============================================================
// Eyecare
int EyecareSetting::enableEyecareSetting(const TCHAR *isenable) {
	const bool enabled = enabledFromString(isenable);
	enable(enabled);
	return 0;
}

int EyecareSetting::setEyecareState(const TCHAR *state, const TCHAR *value) {
	long lt = _tcstol(value, NULL, 10);
	if (0 == _tcscmp(state, CONFIG_APPSET_EYECARE_EYECARE)) {
		setState(EyecareSetting::EYECARE_TIME);
		setLeftTime(lt);
	} else if (0 == _tcscmp(state, CONFIG_APPSET_EYECARE_ENTER)) {
		// 设置状体
		setState(EyecareSetting::ENTERT_TIME);
		setLeftTime(lt);
	}
	return 0;
}

int EyecareSetting::setEyecareSetting(const TCHAR *type, const TCHAR *timespan) {
	long lt = _tcstol(timespan, NULL, 10);
	if (0 == _tcscmp(type, CONFIG_APPSET_EYECARE_EYECARE)) {
		setEyecareTime(lt);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_EYECARE_ENTER)) {
		setEnterTime(lt);
	}

	return 0;
}

int EyecareSetting::setEyecareTermMode(const TCHAR * value) {
	long lt = _tcstol(value, NULL, 10);
	setTerimatedMode(lt);
	return 0;
}

int EyecareSetting::getEyecareSetting(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_ITEM_APPSET_EYECARE));

	// 设置它是否可用
	enableEyecareSetting(ele->Attribute(CONFIG_CONST_ENABLE));
	setEyecareTermMode(ele->Attribute(CONFIG_APPSET_EYECARE_TERM_MODE));

	TiXmlNode * node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			if (0 == _tcscmp(ele->Value(), CONFIG_APPSET_EYECARE_TIME)) {
			setEyecareSetting(ele->Attribute(CONFIG_CONST_NAME),
				ele->Attribute(CONFIG_APPSET_EYECARE_TIMESPAN));
			}
		}

		node = node->NextSibling();
	}

	setEyecareState(ele->Attribute(CONFIG_APPSET_EYECARE_STATE), ele->Attribute(CONFIG_APPSET_EYECARE_TIMELEFT));
	return 0;
}

//////////////////////////////////////////////////////////
// 保存
int EyecareSetting::saveEyecare(TiXmlElement *app_root) {
	TCHAR buffer[1024];

	//=========================================
	// 设置属性
	TiXmlElement * eyecare_root = new TiXmlElement( CONFIG_ITEM_APPSET_EYECARE);
	eyecare_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool( isEnabled()));
	eyecare_root->SetAttribute(CONFIG_APPSET_EYECARE_STATE, Eyecare_state( getState()));

	// 保存Term_mode
	_sntprintf(buffer, 1024, "%d",  getTerminatedMode());
	eyecare_root->SetAttribute(CONFIG_APPSET_EYECARE_TERM_MODE, buffer);

	//==========================================
	// 子集点
	// 设置剩余时间
	_sntprintf(buffer, 1024, "%d",  getRemainTime());
	eyecare_root->SetAttribute(CONFIG_APPSET_EYECARE_TIMELEFT, buffer);

	// 设置娱乐事件
	TiXmlElement * enter_time = new TiXmlElement(CONFIG_APPSET_EYECARE_TIME);
	enter_time->SetAttribute(CONFIG_CONST_NAME, CONFIG_APPSET_EYECARE_ENTER);

	_sntprintf(buffer, 1024, "%d",  getEnterTime());	// 设置娱乐时间间隔
	enter_time->SetAttribute(CONFIG_APPSET_EYECARE_TIMESPAN, buffer);
	eyecare_root->LinkEndChild(enter_time);

	// 设置休息时间
	TiXmlElement * eyecare_time = new TiXmlElement(CONFIG_APPSET_EYECARE_TIME);
	eyecare_time->SetAttribute(CONFIG_CONST_NAME, CONFIG_APPSET_EYECARE_EYECARE);

	_sntprintf(buffer, 1024, "%d",  getEyecareTime());
	eyecare_time->SetAttribute(CONFIG_APPSET_EYECARE_TIMESPAN, buffer);
	eyecare_root->LinkEndChild(eyecare_time);

	app_root->LinkEndChild(eyecare_root);
	return 0;
}
