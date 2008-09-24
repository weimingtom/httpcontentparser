#ifndef _SETTING_AUTOCLEAR_H__
#define _SETTING_AUTOCLEAR_H__

#include <stdio.h>
#include <sys/types.h>
#include <time.h>


// Ӧ���ܹ�֧��64λʱ��
// ���ฺ������Զ���յĲ���
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

	// ����ʱ�䷶Χ
	void setScale(const  __int64 min, const  __int64 max);

	// ��ֵ��ʼʱ��
	void reset();

	__int64 getRangeMax() const { return max_;}
	__int64 getRangeMin() const { return min_;}
private:
	// Ĭ������
	void defaultSetting();

	__int64 getCurrent();
	__int64 clearTime();
private:	
	// �Ƿ����
	bool enable_;

	// �Զ���յķ�Χ, ��λ����
	__int64 max_, min_;
	
	// ʱ����
	__int64 timespan_;

	// �ϴ�ִ������
	__int64 last_time_;
};

#endif  // _SETTING_AUTOCLEAR_H__
