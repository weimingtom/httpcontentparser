#ifndef _SETTING_AUTHORIZE_H__
#define _SETTING_AUTHORIZE_H__

#include <string>
#include <map>
#include <passwordtype.h>

// 此类负责密码的统一管理
// 包括密码的保存， 验证，修改等
// 管理密码
class Authorize {
public:
	Authorize(void);
	~Authorize(void);
public:
	bool setNewPassword(const std::string &password, const int type);
	bool setPassword(const std::string &password, const std::string &oldword, const int type);
	bool checkPassword(const std::string &password, const int type);
private:
	// 默认设置
	void defaultSetting();
	
	// 设置
	std::map<int, std::string> password_;
	typedef std::map<int, std::string> PASSWORD_MAP;
	PASSWORD_MAP password_set_;
};

#endif  // _SETTING_AUTHORIZE_H__
