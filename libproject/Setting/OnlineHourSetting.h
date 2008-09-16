#ifndef _SETTING_ONLINEHOURSETTING_H__
#define _SETTING_ONLINEHOURSETTING_H__

#include <set>

// class  OnlineHourSetting
// 设置上线的时间
class OnlineHourSetting {
public:
	OnlineHourSetting(void);
	~OnlineHourSetting(void);

	// 是否可用
	void enableOnlineHour(const bool enabled) {
		enable_rule_ = enabled;
	}
	bool isEnabled() const {
		return enable_rule_;
	}

	void setHour(const DWORD full, const bool allow_access);
	void setHour(const DWORD day, const DWORD hour, const bool allow_access);
	bool getHour(const DWORD full);
	bool getHour(const DWORD day, const DWORD hour);
	// 使用DWROD表示一个星期中的某个小时
	// HIWORD代表 day, LOWORD 代表 hour
private:
	typedef std::set<DWORD> OFFLINE_HOUR;
	OFFLINE_HOUR online_hour_;

	bool enable_rule_;
};

#endif  // _SETTING_ONLINEHOURSETTING_H__