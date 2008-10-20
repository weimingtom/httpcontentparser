#ifndef _SETTING_AUTHORIZE_H__
#define _SETTING_AUTHORIZE_H__

#include <string>
#include <map>
#include <passwordtype.h>
#include <Enumerate.h>
#include <configitem.h>
#include <xmldefined.h>

class XMLConfiguration;

// ���ฺ�������ͳһ����
// ��������ı��棬 ��֤���޸ĵ�
// ��������
class Authorize :  public ConfigItem  {
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
	void setSuPassword(const char *password);
	
	// ����
	std::map<int, std::string> password_;
	typedef std::map<int, std::string> PASSWORD_MAP;
	PASSWORD_MAP password_set_;

	friend class XMLConfiguration;	//������������
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
