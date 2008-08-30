#ifndef _SETTING_EYECARE_SETTING_H__
#define _SETTING_EYECARE_SETTING_H__

#include <comdef.h>
#include "calculagraph.h"

class Authorize;


class EyecareSetting {
public:
	EyecareSetting();
	~EyecareSetting(void);

	enum {
		ENTERTAINMENT_TIME,
		EYECARE_TIME
	};

public:
	// ��֤����
	bool setPassword(const std::string &password, 
		const std::string& orgin_password);

	bool setPasswordType(const int type);

	// ������Ϣʱ��������¼�
	void setEntertainTime(const int minutes);
	void setRestTime(const int minutes);

	// ��ȡʣ��ʱ��
	int getRemainTime() const;
	int getState() const {return state_;}// ��ȡĿǰ��״̬

	int getEntertainTime() const;
	int getRestTime() const;

	int trySwitch(); // �����л�״̬�����ʱ���Ѿ�������Զ��л������򲻸ı�
	int switchState(const std::string &password); // �л�״̬

	int ForceLockWnd(); // ǿ�ƹر���Ļ

	// �������ļ��ж�ȡ������Ϣ
	void loadSetting();
	void initialize(Authorize *authorize);
private:
	int changeState(const int current);
	bool checkPassword(const std::string &password);

	int entertain_time_;
	int rest_time_;
	int new_state_begin_; // ��״̬�Ŀ�ʼʱ��
	int state_;

	// ������Ҫ��������

	// ����״̬���룬 ��������
	// ��Ϊ�������ʹ���������ͣ�һ��ֱ��ʹ�ã�����һ��ʹ��ȫ�ֵ�����
	Authorize * authorize_;
	int password_type;

	bool force_locked_;
};

#endif  // _SETTING_EYECARE_SETTING_H__