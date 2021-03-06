#ifndef _SETTING_AUTOCLEAR_H__
#define _SETTING_AUTOCLEAR_H__

#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <string>
#include <atltime.h>
#include <setting\settingitem.h>

// 应该能够支持64位时间
// 此类负责各种自动清空的操作
class AutoClean : public SettingItem {
public:
	AutoClean(void);
	~AutoClean(void);

public:
	// 设置和获取自动清理的时间间隔
	void setTimespan(const int days);
	int getTimespan() const { return timespan_days_;}

	// 设置时间范围
	void setScale(const  int minDays, const  int maxDays);
	int getRangeMax() const { return max_;}
	int getRangeMin() const { return min_;}

	// 是否应该执行自动清理
	bool shouldExec();

	// 充值起始时间
	void reset();
	void setLastTime(LPCTSTR lpstr);
	std::string getLastTime();
private:
	// 默认设置
	void defaultSetting();
private:
	// 自动清空的范围, 单位天
	int max_, min_;
	
	// 时间间隔
	int timespan_days_;

	// 上次执行清理
	CTime * last_time_;
};

#endif  // _SETTING_AUTOCLEAR_H__
