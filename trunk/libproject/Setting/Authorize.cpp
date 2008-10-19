#include "StdAfx.h"
#include ".\authorize.h"
#include <assert.h>
#include <string>
#include <map>
#include <passwordtype.h>

Authorize::Authorize(void) {
	defaultSetting();
}

Authorize::~Authorize(void) {
}

void Authorize::defaultSetting() {
	setSuPassword(DEFAULT_PASSWORD);
}

void Authorize::setSuPassword(const char * password) {
	password_set_.insert(std::make_pair(PASSWORD_SU, password));
}

bool Authorize::setNewPassword(const std::string &password, const int type) {
	assert (type != PASSWORD_SU);
	assert(password_set_.find(type) == password_set_.end());
	if (password_set_.find(type) == password_set_.end()) {
		password_set_.insert(make_pair(type, password));
		return true;
	} else {
		return false;
	}
}

bool Authorize::checkPassword(const std::string &password, const int type) {
	PASSWORD_MAP::iterator iter = password_set_.find(type);
	assert (iter != password_set_.end());
	if (iter->second == password) {
		return true;
	} else {
		return false;
	}
}

// 如果设置失败返回 false, 成功返回 true
bool Authorize::setPassword(const std::string &password, const std::string &oldword, const int type) {
	if (checkPassword(oldword, type)) {
		password_set_[type] = password;
		return true;
	} else {
		return false;
	}
}

//========================================
//
void Authorize::EnumUsers(Enumerator2<std::string, int> * enumerator) {
	PASSWORD_MAP::const_iterator iter = password_set_.begin();
	for (; iter != password_set_.end(); ++iter) {
		enumerator->Enum(iter->second, iter->first);
	}
}

// 保存 XML
int Authorize::parseConfig(TiXmlElement * item_root) {
	getAuthorizeSetting(item_root);
	return 0;
}
int Authorize::saveConfig(TiXmlElement * item_root) {
	saveAuthorize(item_root);
	return 0;
}


namespace {

inline
const char * UserType(const int user_type) {
	if ( user_type == PASSWORD_SU) {
		return CONFIG_APPSET_AUTHORIZE_USERTYPE_SU;
	} else {
		assert (false);
		return CONFIG_APPSET_AUTHORIZE_USERTYPE_OTHER;
	}
}

// class DNSEnumerator
class EnumUsersInfo : public Enumerator2<std::string, int> {
public:
	virtual int Enum(const std::string &password, const int type) {
		TiXmlElement * url_node = new TiXmlElement(CONFIG_APPSET_AUTHORIZE_USER);
		url_node->SetAttribute(CONFIG_APPSET_AUTHORIZE_NAME, UserType(type));
		url_node->SetAttribute(CONFIG_APPSET_AUTHORIZE_PASSWORD, password);


		rule_root_->LinkEndChild(url_node);
		return 0;
	}
public:
	EnumUsersInfo(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
		assert (rule_root_ != NULL);
	}
private:
	TiXmlElement *rule_root_;
};

};

//================================================
// Authorize
int Authorize::addUser(const TCHAR *username, const TCHAR *password) {
	if ( 0 == _tcscmp(username, CONFIG_APPSET_AUTHORIZE_USERTYPE_SU)) {
		setSuPassword(password);
	}
	return 0;
}

int Authorize::getAuthorizeSetting(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_ITEM_APPSET_AUTHORIZE));

	TiXmlNode * node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele && 0 == _tcscmp(ele->Value(), CONFIG_APPSET_AUTHORIZE_USER)) {
			addUser(ele->Attribute(CONFIG_APPSET_AUTHORIZE_NAME), ele->Attribute(CONFIG_APPSET_AUTHORIZE_PASSWORD));
		}

		node = node->NextSibling();
	}
	return 0;
}

int Authorize::saveAuthorize(TiXmlElement *app_root) {
	TiXmlElement * author_root = new TiXmlElement(CONFIG_ITEM_APPSET_AUTHORIZE);
	
	EnumUsers(&EnumUsersInfo(author_root));
	app_root->LinkEndChild(author_root);
	return 0;
}