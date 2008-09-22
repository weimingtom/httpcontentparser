#ifndef _SETTING_AUTOCLEAR_H__
#define _SETTING_AUTOCLEAR_H__

#include <stdio.h>
#include <sys/types.h>
#include <time.h>

// Ӧ���ܹ�֧��64λʱ��
// ���ฺ������Զ���յĲ���
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

	// ����ʱ�䷶Χ
	void setScale(const  __time64_t min, const  __time64_t max);
private:
	// Ĭ������
	void defaultSetting();

	// ��ֵ��ʼʱ��
	void reset();
private:	
	// �Ƿ����
	bool enable_;

	// �Զ���յķ�Χ, ��λ����
	__time64_t max_, min_;
	
	// ʱ����
	__time64_t timespan_;

	// �ϴ�ִ������
	struct __timeb  last_time_;
};

#endif  // _SETTING_AUTOCLEAR_H__
