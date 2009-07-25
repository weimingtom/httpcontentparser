#ifndef _SETTING_TIMEOUTSWITCH_H__
#define _SETTING_TIMEOUTSWITCH_H__

#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>
#include "calculagraph.h" 

// class TimeoutSwitch
// ��ʱ��ﵽ�ǣ��Զ��л�
class TimeoutSwitch  : public SettingItem , public ConfigItem {
public:
	TimeoutSwitch(void);
	~TimeoutSwitch(void);

	// �Ƿ�Ӧ�ñ��л�
	bool shouldSwitch();

	// ����TIMEOUT��ʱ��ֵ
	int getTimeoutValue() const;
	void setTimeoutValue(const int sec);

	// ��ȡȡֵ����
	int getRangeMin() const { return min_;}
	int getRangeMax() const { return max_;}

	// ���״̬�л���PARENT MODE, �����
	void startTimer();

	// ��ȡ�����л���ʱ��
	int getLeftTime() { return calcugraph_.getRemainTime();}
private:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * root);
private:
	void defaultSetting();

	// ��ʱ��
	Calculagraph calcugraph_;

	// ����ʱ������Χ
	void setRange(const int min, const int max) {
		max_ = max;
		min_ = min;
	}
	int max_, min_;
	int timespan_;
};

#endif  // _SETTING_TIMEOUTSWITCH_H__