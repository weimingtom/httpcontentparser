#ifndef _SETTING_EYECARE_SETTING_H__
#define _SETTING_EYECARE_SETTING_H__

#include <comdef.h>
#include "calculagraph.h"


class Authorize;
class XMLConfiguration;

// TODO : we must add sate store function
// TODO : 
class EyecareSetting {
public:
	EyecareSetting();
	~EyecareSetting(void);

	enum {
		ENTERTAINMENT_TIME = 0,
		EYECARE_TIME
	};

public:
	// 是否可用
	bool isEnable() const { return enabled_;}
	void Enable(const bool enable) {enabled_ = enable;}

	// 验证密码
	bool setPassword(const std::string &password, 
		const std::string& orgin_password);

	bool setPasswordType(const int type);


	// 获取剩余时间
	int getRemainTime() const { return calculagraph_.getRemainTime();}
	int getState() const {return calculagraph_.getCurrentState();}// 获取目前的状态

	// 设置休息时间和娱乐事件
	void setEntertainTime(const int seconds) { calculagraph_.setTimespan(seconds, ENTERTAINMENT_TIME);}
	void setRestTime(const int seconds) { calculagraph_.setTimespan(seconds, EYECARE_TIME);}
	int getEntertainTime() const  { return calculagraph_.getTimespan(ENTERTAINMENT_TIME);}
	int getRestTime() const { return calculagraph_.getTimespan(EYECARE_TIME);}

	bool trySwitch(); // 尝试切换状态，如果时间已经达标则自动切换，否则不改变
	int switchState(const std::string &password); // 切换状态

	int ForceLockWnd(); // 强制关闭屏幕, 此时只有输入密码才可进入

	// 从配置文件中读取设置信息
	void loadSetting();
	void initialize(Authorize *authorize, int state);
private:
	bool checkPassword(const std::string &password);

	void setState(int state) { calculagraph_.forceSwitch(state);}
	void setLeftTime(int timeleft) {}

	MultiCalculagraph<2> calculagraph_; // 用于两个计时器

	// 这里需要保存密码

	// 保存状态密码， 密码类型
	// 因为密码可以使用两种类型，一种直接使用，另外一个使用全局的密码
	Authorize * authorize_;
	int password_type;

	bool force_locked_;

	friend class XMLConfiguration;
private:
	bool enabled_;
};

#endif  // _SETTING_EYECARE_SETTING_H__