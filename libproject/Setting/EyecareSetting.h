#ifndef _SETTING_EYECARE_SETTING_H__
#define _SETTING_EYECARE_SETTING_H__

#include <string>
#include <comdef.h>
#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>
#include "calculagraph.h"


class Authorize;
class XMLConfiguration;
class EyecareTest;

class EyecareSetting : public SettingItem  , public ConfigItem {
public:
	EyecareSetting();
	~EyecareSetting(void);

	enum {
		ENTERT_TIME = 0,
		EYECARE_TIME
	};

public:
	// 验证密码
	bool setPassword(const std::string &password, 
		const std::string& orgin_password);

	bool setPasswordType(const int type);


	// 获取剩余时间
	int getRemainTime();
	int getState() const;// 获取目前的状态

	// 设置休息时间和娱乐事件
	void setEnterTime(const int seconds)   { setModified(true);  calculagraph_.setTimespan(seconds, ENTERT_TIME);}
	void setEyecareTime(const int seconds) { setModified(true);  calculagraph_.setTimespan(seconds, EYECARE_TIME);}
	int getEnterTime() const  { return calculagraph_.getTimespan(ENTERT_TIME);}
	int getEyecareTime() const { return calculagraph_.getTimespan(EYECARE_TIME);}

	bool shouldStartEyecare();
	bool trySwitch(); // 尝试切换状态，如果时间已经达标则自动切换，否则不改变
	int switchState(const std::string &password); // 切换状态

	void initialize(Authorize *authorize, int state);

	// 停止或重新启动
	void stopTimer() { return calculagraph_.stop();}
	void restartTimer() { return calculagraph_.restart();}
	bool isTimerStopped() { return calculagraph_.isStopped();}

	void enable(const bool enabled) {
		if (false == enabled) {
			stopTimer();
		} else {
			isTimerStopped() ? restartTimer() : false ;
		}

		SettingItem::enable(enabled);
	}

private:
	bool checkPassword(const std::string &password);

	void setState(int state) { calculagraph_.forceSwitch(state);}
	void setLeftTime(int seconds) { calculagraph_.setRemainTime(seconds);}

	MultiCalculagraph<2> calculagraph_; // 用于两个计时器

	// 这里需要保存密码

	// 保存状态密码， 密码类型
	// 因为密码可以使用两种类型，一种直接使用，另外一个使用全局的密码
	Authorize * authorize_;
	int password_type;

	friend class XMLConfiguration;

	// 默认设置
	void defaultSetting();
public:
	// 当用户输入密码切换状态后的反映，有两种
	// 1. 进入超级用户模式  2. 充值用户
	enum {EYECARE_TERMIN_ENTERSU = 0, EYECARE_TERMIN_RESETTIMER};
	void setTerimatedMode(const int mode) {after_eyecare_terminated_ = mode;}
	int getTerminatedMode() const { return after_eyecare_terminated_;}
private:
	int after_eyecare_terminated_;

	friend void TestSetLeft();

	// XML
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * root);
private:
		// Eyecare
	int getEyecareSetting(TiXmlElement *ele);
	int setEyecareSetting(const TCHAR *type, const TCHAR *time);
	int enableEyecareSetting(const TCHAR *enable);
	int setEyecareState(const TCHAR *state, const TCHAR *value);
	int setEyecareTermMode(const TCHAR * value);

	// 保存
	TiXmlElement *  saveEyecare(TiXmlElement *app_root);
};

#endif  // _SETTING_EYECARE_SETTING_H__