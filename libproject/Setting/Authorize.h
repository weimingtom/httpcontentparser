#ifndef _SETTING_AUTHORIZE_H__
#define _SETTING_AUTHORIZE_H__

#include <string>
#include <map>
#include <passwordtype.h>

// ���ฺ�������ͳһ����
// ��������ı��棬 ��֤���޸ĵ�
// ��������
class Authorize {
public:
	Authorize(void);
	~Authorize(void);
public:
	bool setNewPassword(const std::string &password, const int type);
	bool setPassword(const std::string &password, const std::string &oldword, const int type);
	bool checkPassword(const std::string &password, const int type);
private:
	// Ĭ������
	void defaultSetting();
	
	// ����
	std::map<int, std::string> password_;
	typedef std::map<int, std::string> PASSWORD_MAP;
	PASSWORD_MAP password_set_;
};

#endif  // _SETTING_AUTHORIZE_H__
