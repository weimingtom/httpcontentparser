#ifndef _SETTING_ONLINEHOURSETTING_H__
#define _SETTING_ONLINEHOURSETTING_H__

#include <set>
#include <enumerate.h>
#include <settingitem.h>

// class  OnlineHourSetting
// 设置上线的时间
class OnlineHourSetting : public SettingItem {
public:
	OnlineHourSetting(void);
	~OnlineHourSetting(void);

	void setHour(const DWORD full, const bool allow_access);
	void setHour(const DWORD day, const DWORD hour, const bool allow_access);
	bool getHour(const DWORD full);
	bool getHour(const DWORD day, const DWORD hour);
	// 使用DWROD表示一个星期中的某个小时
	// HIWORD代表 day, LOWORD 代表 hour

	// enumerate the hour
	void enumBlockHour(Enumerator2<int, int> *enumerator);
private:
	typedef std::set<DWORD> OFFLINE_HOUR;
	OFFLINE_HOUR online_hour_;
};

#endif  // _SETTING_ONLINEHOURSETTING_H__