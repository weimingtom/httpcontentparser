#ifndef _SETTING_AUTOCLEAR_H__
#define _SETTING_AUTOCLEAR_H__

#include <stdio.h>
#include <sys/types.h>
#include <time.h>

// 应该能够支持64位时间
// 此类负责各种自动清空的操作
class AutoClear {
public:
	AutoClear(void);
	~AutoClear(void);

public:
	bool isEnable() const { return enable_;}
	void enable(const bool enabled) { enable_ = enabled;}

	void setTimespan(const __time64_t timespan) {
		timespan_ = timespan;
	}

	__time64_t getTimespan() const { return timespan_;}

	bool shouldExec();

	// 设置时间范围
	void setScale(const  __time64_t min, const  __time64_t max);
private:
	// 默认设置
	void defaultSetting();

	// 充值起始时间
	void reset();
private:	
	// 是否可用
	bool enable_;

	// 自动清空的范围, 单位毫秒
	__time64_t max_, min_;
	
	// 时间间隔
	__time64_t timespan_;

	// 上次执行清理
	struct __timeb  last_time_;
};

#endif  // _SETTING_AUTOCLEAR_H__
