#ifndef _SETTING_ONLINEHOURSETTING_H__
#define _SETTING_ONLINEHOURSETTING_H__

#include <set>

// class  OnlineHourSetting
// �������ߵ�ʱ��
class OnlineHourSetting {
public:
	OnlineHourSetting(void);
	~OnlineHourSetting(void);

	// �Ƿ����
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
	// ʹ��DWROD��ʾһ�������е�ĳ��Сʱ
	// HIWORD���� day, LOWORD ���� hour
private:
	typedef std::set<DWORD> OFFLINE_HOUR;
	OFFLINE_HOUR online_hour_;

	bool enable_rule_;
};

#endif  // _SETTING_ONLINEHOURSETTING_H__