#ifndef _SETTING_TIMEOUTSWITCH_H__
#define _SETTING_TIMEOUTSWITCH_H__

#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>
#include "calculagraph.h" 

// class TimeoutSwitch
// 当时间达到是，自动切换
class TimeoutSwitch  : public SettingItem , public ConfigItem {
public:
	TimeoutSwitch(void);
	~TimeoutSwitch(void);

	// 是否应该被切换
	bool shouldSwitch();

	// 设置TIMEOUT的时间值
	int getTimeoutValue() const;
	void setTimeoutValue(const int sec);

	// 获取取值返回
	int getRangeMin() const { return min_;}
	int getRangeMax() const { return max_;}

	// 如果状态切换到PARENT MODE, 则调用
	void startTimer();

	// 获取距离切换的时间
	int getLeftTime() { return calcugraph_.getRemainTime();}
private:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * root);
private:
	void defaultSetting();

	// 计时器
	Calculagraph calcugraph_;

	// 设置时间间隔范围
	void setRange(const int min, const int max) {
		max_ = max;
		min_ = min;
	}
	int max_, min_;
	int timespan_;
};

#endif  // _SETTING_TIMEOUTSWITCH_H__