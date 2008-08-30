#ifndef _SETTING_EYECARE_SETTING_H__
#define _SETTING_EYECARE_SETTING_H__

#include <comdef.h>
#include "calculagraph.h"

class Authorize;


class EyecareSetting {
public:
	EyecareSetting();
	~EyecareSetting(void);

	enum {
		ENTERTAINMENT_TIME,
		EYECARE_TIME
	};

public:
	// 验证密码
	bool setPassword(const std::string &password, 
		const std::string& orgin_password);

	bool setPasswordType(const int type);

	// 设置休息时间和娱乐事件
	void setEntertainTime(const int minutes);
	void setRestTime(const int minutes);

	// 获取剩余时间
	int getRemainTime() const;
	int getState() const {return state_;}// 获取目前的状态

	int getEntertainTime() const;
	int getRestTime() const;

	int trySwitch(); // 尝试切换状态，如果时间已经达标则自动切换，否则不改变
	int switchState(const std::string &password); // 切换状态

	int ForceLockWnd(); // 强制关闭屏幕

	// 从配置文件中读取设置信息
	void loadSetting();
	void initialize(Authorize *authorize);
private:
	int changeState(const int current);
	bool checkPassword(const std::string &password);

	int entertain_time_;
	int rest_time_;
	int new_state_begin_; // 新状态的开始时间
	int state_;

	// 这里需要保存密码

	// 保存状态密码， 密码类型
	// 因为密码可以使用两种类型，一种直接使用，另外一个使用全局的密码
	Authorize * authorize_;
	int password_type;

	bool force_locked_;
};

#endif  // _SETTING_EYECARE_SETTING_H__