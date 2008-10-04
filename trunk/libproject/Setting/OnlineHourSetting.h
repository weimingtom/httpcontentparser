#ifndef _SETTING_ONLINEHOURSETTING_H__
#define _SETTING_ONLINEHOURSETTING_H__

#include <set>
#include <enumerate.h>
#include <settingitem.h>

// class  OnlineHourSetting
// �������ߵ�ʱ��
class OnlineHourSetting : public SettingItem {
public:
	OnlineHourSetting(void);
	~OnlineHourSetting(void);

	void setHour(const DWORD full, const bool allow_access);
	void setHour(const DWORD day, const DWORD hour, const bool allow_access);
	bool getHour(const DWORD full);
	bool getHour(const DWORD day, const DWORD hour);
	// ʹ��DWROD��ʾһ�������е�ĳ��Сʱ
	// HIWORD���� day, LOWORD ���� hour

	// enumerate the hour
	void enumBlockHour(Enumerator2<int, int> *enumerator);
private:
	typedef std::set<DWORD> OFFLINE_HOUR;
	OFFLINE_HOUR online_hour_;
};

#endif  // _SETTING_ONLINEHOURSETTING_H__