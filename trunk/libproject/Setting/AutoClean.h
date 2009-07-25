#ifndef _SETTING_AUTOCLEAR_H__
#define _SETTING_AUTOCLEAR_H__

#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <string>
#include <atltime.h>
#include <setting\settingitem.h>

// Ӧ���ܹ�֧��64λʱ��
// ���ฺ������Զ���յĲ���
class AutoClean : public SettingItem {
public:
	AutoClean(void);
	~AutoClean(void);

public:
	// ���úͻ�ȡ�Զ������ʱ����
	void setTimespan(const int days);
	int getTimespan() const { return timespan_days_;}

	// ����ʱ�䷶Χ
	void setScale(const  int minDays, const  int maxDays);
	int getRangeMax() const { return max_;}
	int getRangeMin() const { return min_;}

	// �Ƿ�Ӧ��ִ���Զ�����
	bool shouldExec();

	// ��ֵ��ʼʱ��
	void reset();
	void setLastTime(LPCTSTR lpstr);
	std::string getLastTime();
private:
	// Ĭ������
	void defaultSetting();
private:
	// �Զ���յķ�Χ, ��λ��
	int max_, min_;
	
	// ʱ����
	int timespan_days_;

	// �ϴ�ִ������
	CTime * last_time_;
};

#endif  // _SETTING_AUTOCLEAR_H__
