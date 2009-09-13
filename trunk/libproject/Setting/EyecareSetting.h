#ifndef _SETTING_EYECARE_SETTING_H__
#define _SETTING_EYECARE_SETTING_H__

#include <string>
#include <comdef.h>
#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>
#include "calculagraph.h"


class Authorize;
class XMLConfiguration;
class EyecareTest;

class EyecareSetting : public SettingItem  , public ConfigItem {
public:
	EyecareSetting();
	~EyecareSetting(void);

	enum {
		ENTERT_TIME = 0,
		EYECARE_TIME
	};

public:
	// ��֤����
	bool setPassword(const std::string &password, 
		const std::string& orgin_password);

	bool setPasswordType(const int type);


	// ��ȡʣ��ʱ��
	int getRemainTime();
	int getState() const;// ��ȡĿǰ��״̬

	// ������Ϣʱ��������¼�
	void setEnterTime(const int seconds)   { setModified(true);  calculagraph_.setTimespan(seconds, ENTERT_TIME);}
	void setEyecareTime(const int seconds) { setModified(true);  calculagraph_.setTimespan(seconds, EYECARE_TIME);}
	int getEnterTime() const  { return calculagraph_.getTimespan(ENTERT_TIME);}
	int getEyecareTime() const { return calculagraph_.getTimespan(EYECARE_TIME);}

	bool shouldStartEyecare();
	bool trySwitch(); // �����л�״̬�����ʱ���Ѿ�������Զ��л������򲻸ı�
	int switchState(const std::string &password); // �л�״̬

	void initialize(Authorize *authorize, int state);

	// ֹͣ����������
	void stopTimer() { return calculagraph_.stop();}
	void restartTimer() { return calculagraph_.restart();}
	bool isTimerStopped() { return calculagraph_.isStopped();}

	void enable(const bool enabled) {
		if (false == enabled) {
			stopTimer();
		} else {
			isTimerStopped() ? restartTimer() : false ;
		}

		SettingItem::enable(enabled);
	}

private:
	bool checkPassword(const std::string &password);

	void setState(int state) { calculagraph_.forceSwitch(state);}
	void setLeftTime(int seconds) { calculagraph_.setRemainTime(seconds);}

	MultiCalculagraph<2> calculagraph_; // ����������ʱ��

	// ������Ҫ��������

	// ����״̬���룬 ��������
	// ��Ϊ�������ʹ���������ͣ�һ��ֱ��ʹ�ã�����һ��ʹ��ȫ�ֵ�����
	Authorize * authorize_;
	int password_type;

	friend class XMLConfiguration;

	// Ĭ������
	void defaultSetting();
public:
	// ���û����������л�״̬��ķ�ӳ��������
	// 1. ���볬���û�ģʽ  2. ��ֵ�û�
	enum {EYECARE_TERMIN_ENTERSU = 0, EYECARE_TERMIN_RESETTIMER};
	void setTerimatedMode(const int mode) {after_eyecare_terminated_ = mode;}
	int getTerminatedMode() const { return after_eyecare_terminated_;}
private:
	int after_eyecare_terminated_;

	friend void TestSetLeft();

	// XML
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * root);
private:
		// Eyecare
	int getEyecareSetting(TiXmlElement *ele);
	int setEyecareSetting(const TCHAR *type, const TCHAR *time);
	int enableEyecareSetting(const TCHAR *enable);
	int setEyecareState(const TCHAR *state, const TCHAR *value);
	int setEyecareTermMode(const TCHAR * value);

	// ����
	TiXmlElement *  saveEyecare(TiXmlElement *app_root);
};

#endif  // _SETTING_EYECARE_SETTING_H__