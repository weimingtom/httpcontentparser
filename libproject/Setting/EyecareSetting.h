#ifndef _SETTING_EYECARE_SETTING_H__
#define _SETTING_EYECARE_SETTING_H__

#include <comdef.h>
#include "calculagraph.h"


class Authorize;
class XMLConfiguration;

// TODO : we must add sate store function
// TODO : 
class EyecareSetting {
public:
	EyecareSetting();
	~EyecareSetting(void);

	enum {
		ENTERTAINMENT_TIME = 0,
		EYECARE_TIME
	};

public:
	// �Ƿ����
	bool isEnable() const { return enabled_;}
	void Enable(const bool enable) {enabled_ = enable;}

	// ��֤����
	bool setPassword(const std::string &password, 
		const std::string& orgin_password);

	bool setPasswordType(const int type);


	// ��ȡʣ��ʱ��
	int getRemainTime() const { return calculagraph_.getRemainTime();}
	int getState() const {return calculagraph_.getCurrentState();}// ��ȡĿǰ��״̬

	// ������Ϣʱ��������¼�
	void setEntertainTime(const int seconds) { calculagraph_.setTimespan(seconds, ENTERTAINMENT_TIME);}
	void setRestTime(const int seconds) { calculagraph_.setTimespan(seconds, EYECARE_TIME);}
	int getEntertainTime() const  { return calculagraph_.getTimespan(ENTERTAINMENT_TIME);}
	int getRestTime() const { return calculagraph_.getTimespan(EYECARE_TIME);}

	bool trySwitch(); // �����л�״̬�����ʱ���Ѿ�������Զ��л������򲻸ı�
	int switchState(const std::string &password); // �л�״̬

	int ForceLockWnd(); // ǿ�ƹر���Ļ, ��ʱֻ����������ſɽ���

	// �������ļ��ж�ȡ������Ϣ
	void loadSetting();
	void initialize(Authorize *authorize, int state);
private:
	bool checkPassword(const std::string &password);

	void setState(int state) { calculagraph_.forceSwitch(state);}
	void setLeftTime(int timeleft) {}

	MultiCalculagraph<2> calculagraph_; // ����������ʱ��

	// ������Ҫ��������

	// ����״̬���룬 ��������
	// ��Ϊ�������ʹ���������ͣ�һ��ֱ��ʹ�ã�����һ��ʹ��ȫ�ֵ�����
	Authorize * authorize_;
	int password_type;

	bool force_locked_;

	friend class XMLConfiguration;
private:
	bool enabled_;
};

#endif  // _SETTING_EYECARE_SETTING_H__