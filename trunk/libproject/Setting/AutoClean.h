#ifndef _SETTING_AUTOCLEAR_H__
#define _SETTING_AUTOCLEAR_H__

#include <stdio.h>
#include <sys/types.h>
#include <time.h>


// 应该能够支持64位时间
// 此类负责各种自动清空的操作
class AutoClean {
public:
	AutoClean(void);
	~AutoClean(void);

public:
	bool isEnable() const { return enable_;}
	void enable(const bool enabled) { enable_ = enabled;}

	void setTimespan(const __time64_t timespan) {
	}

	__int64 getTimespan() const { return timespan_;}

	bool shouldExec();

	// 设置时间范围
	void setScale(const  __int64 min, const  __int64 max);

	// 充值起始时间
	void reset();

	__int64 getRangeMax() const { return max_;}
	__int64 getRangeMin() const { return min_;}
private:
	// 默认设置
	void defaultSetting();

	__int64 getCurrent();
	__int64 clearTime();
private:	
	// 是否可用
	bool enable_;

	// 自动清空的范围, 单位毫秒
	__int64 max_, min_;
	
	// 时间间隔
	__int64 timespan_;

	// 上次执行清理
	__int64 last_time_;
};

#endif  // _SETTING_AUTOCLEAR_H__
