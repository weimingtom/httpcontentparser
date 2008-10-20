#ifndef _SETTING_AUTHORIZE_H__
#define _SETTING_AUTHORIZE_H__

#include <string>
#include <map>
#include <passwordtype.h>
#include <Enumerate.h>
#include <configitem.h>
#include <xmldefined.h>

class XMLConfiguration;

// 此类负责密码的统一管理
// 包括密码的保存， 验证，修改等
// 管理密码
class Authorize :  public ConfigItem  {
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
	void setSuPassword(const char *password);
	
	// 设置
	std::map<int, std::string> password_;
	typedef std::map<int, std::string> PASSWORD_MAP;
	PASSWORD_MAP password_set_;

	friend class XMLConfiguration;	//用于设置密码
	void EnumUsers(Enumerator2<std::string, int> * enumerator);

// XML file
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * root);
private:
	TiXmlElement * saveAuthorize(TiXmlElement *app_root);
	int getAuthorizeSetting(TiXmlElement *ele);
	int addUser(const TCHAR *username, const TCHAR *password);

};

#endif  // _SETTING_AUTHORIZE_H__
