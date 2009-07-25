#ifndef _SETTING_ONLINEHOURSETTING_H__
#define _SETTING_ONLINEHOURSETTING_H__

#include <set>
#include <enumerate.h>
#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>

// class  OnlineHourSetting
// �������ߵ�ʱ��
class OnlineHourSetting : public SettingItem, public ConfigItem  {
public:
	OnlineHourSetting(void);
	~OnlineHourSetting(void);

	bool getSettingHour(const DWORD day, const DWORD hour);
	bool getSettingHour(const DWORD full);

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

	// XML file
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * root);
private:
	// ��������
	int getOnlinetime(TiXmlElement * ele);
	int parseTime(const TCHAR *time);
	int onlineBlocktime(const TCHAR *time);

	// ����OnlineHour����
	TiXmlElement * saveOnlineHour(TiXmlElement *rules_root);	
};

#endif  // _SETTING_ONLINEHOURSETTING_H__