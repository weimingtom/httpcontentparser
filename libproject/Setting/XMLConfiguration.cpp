#include "StdAfx.h"
#include ".\xmlconfiguration.h"
#include ".\SearchRule.h"
#include ".\eyecaresetting.h"
#include ".\autoclean.h"
#include <webcontenttype.h>
#include <passwordtype.h>
#include <tinyXML\tinyxml.h>
#include <webcontenttype.h>
#include <sysutility.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <zlib\zlib.h>

//=====================================================
// constructor and deconstructor
XMLConfiguration::XMLConfiguration() {
	defaultSetting();
}

XMLConfiguration::~XMLConfiguration(void) {
}

void XMLConfiguration::defaultSetting() {
	getEyecareSetting()->initialize(getAuthorize(),  EyecareSetting::ENTERT_TIME);
	getDNSSetting()->initialize(getBlackURLSet(), getWhiteURLSet());
}

///////////////////////////////////////////////////////////////////////////////////
// �������

int XMLConfiguration::saveAppSetting(TiXmlElement * root) {
	TiXmlElement * appsetting_root = new TiXmlElement( CONFIG_NODE_APPSET );
	
	getWebHistoryRecordSetting()->saveconfig(appsetting_root);
	getEyecareSetting()->saveconfig(appsetting_root);
	getScreenSave()->saveconfig(appsetting_root);
	getAuthorize()->saveconfig(appsetting_root);
	root->LinkEndChild(appsetting_root);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////
// �������
//==========================================================
// XML ���溯��
int XMLConfiguration::saveConfig(const TCHAR * filename) {
	// Create XML
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	doc.LinkEndChild(decl);

	// �������ڵ�
	TiXmlElement * root_element = new TiXmlElement( CONFIG_ROOT_VALUE );
	
	saveRules(root_element);
	saveAppSetting(root_element);
	
	doc.LinkEndChild(root_element);

	doc.SaveFile(filename);
	return 0;
}
int XMLConfiguration::saveRules(TiXmlElement *root) {
	TiXmlElement * rules_root = new TiXmlElement( CONFIG_NODE_RULES );
	// ��������ʱ�����
	getOnlineSetting()->saveConfig(rules_root);
	saveWhiteURL(rules_root);
	saveBlackURL(rules_root);
	
	getSearchRule()->saveConfig(rules_root);
	getContentCheckSetting()->saveConfig(rules_root);
	root->LinkEndChild(rules_root);
	return 0;
}

//===========================================================
// URL Rules
namespace {
// class DNSEnumerator
class DNSEnum : public Enumerator1<std::string> {
public:
	virtual int Enum(const std::string &dns) {
		TiXmlElement * url_node = new TiXmlElement(CONFIG_NODE_URL);
		TiXmlText * text = new TiXmlText(dns);
		url_node->LinkEndChild(text);
		rule_root_->LinkEndChild(url_node);
		return 0;
	}
public:
	DNSEnum(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
		assert (rule_root_ != NULL);
	}
private:
	TiXmlElement *rule_root_;
};
};

int XMLConfiguration::saveWhiteURL(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// ��������
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_WHITEURL);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getWhiteURLSet()->isEnabled()));
	rule_root->SetAttribute(CONFIG_WHITEURL_JUSTPASSED, enabledFromBool(getDNSSetting()->justPassWhiteDNS()));
	// ���URL
	getWhiteURLSet()->beginEnum(&DNSEnum(rule_root));
	root->LinkEndChild(rule_root);
	return 0;
}

int XMLConfiguration::saveBlackURL(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// ��������
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_BLACKURL);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getBlackURLSet()->isEnabled()));

	// ���URL
	getBlackURLSet()->beginEnum(&DNSEnum(rule_root));
	root->LinkEndChild(rule_root);
	return 0;
}

//==========================================================
// save Online hour
namespace {

};


///////////////////////////////////////////////////////////////////////////////////
// �������
//

//======================================================
// ��������
int XMLConfiguration::parseAppSet(TiXmlNode *appset_root) {
	assert (0 == _tcscmp(appset_root->Value(), CONFIG_NODE_APPSET));

	TiXmlNode *node = appset_root->FirstChild();
	while (NULL != node) {
		TiXmlElement * element = node->ToElement();
		if (NULL != element) {
			if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_AUTHORIZE) == 0) {
				// ��Ȩ����
				getAuthorize()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_EYECARE) == 0) {
				// �۾���������
				getEyecareSetting()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_WEBHISTORY) == 0) {
				// ��ʷ��¼����
				getWebHistoryRecordSetting()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_SYSSETTING) == 0) {
				// ϵͳ���ù���
				getSystemSetting(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_SCREENSAVER) == 0) {
				// ��Ļ�������ù���
				getScreenSave()->readconfig(element);
			}
		}
		// ��ȡ��һ��
		node = node->NextSibling();
	}
	return 0;
}

int XMLConfiguration::getSystemSetting(TiXmlElement * ele) {
	return 0;
}

//=========================================================
// rule set function
//========================================================
// �������Ƿ����
int XMLConfiguration::enableWhiteURL(const TCHAR *enable) {
	const bool checked = enabledFromString(enable);
	getWhiteURLSet()->enable(checked);
	return 0;
}

int XMLConfiguration::enableJustPassWhite(const TCHAR *enable) {
	const bool checked = enabledFromString(enable);
	getDNSSetting()->justPassWhiteDNS(checked);
	return 0;
}
// ����URL ������
int XMLConfiguration::addWhiteURL(const TCHAR *URL) {
	if (NULL == URL)
		return -1;

	getWhiteURLSet()->addDNS(URL);
	return 0;
}

int XMLConfiguration::getWhiteURL(TiXmlElement * rule_root) {
	// enable?
	const TCHAR *  enable_attr = rule_root->Attribute(CONFIG_CONST_ENABLE);
	enableWhiteURL(enable_attr);

	const TCHAR *  enable_attr_passed = rule_root->Attribute(CONFIG_WHITEURL_JUSTPASSED);
	enableJustPassWhite(enable_attr_passed);
	// ����
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			addWhiteURL(ele->GetText());
		}

		node = node->NextSibling();
	}
	return 0;
}

//========================================================
// �������Ƿ����
int XMLConfiguration::enableBlackURL(const TCHAR *enable) {
	const bool checked = enabledFromString(enable);
	getBlackURLSet()->enable(checked);
	return 0;
}

// ����URL ������
int XMLConfiguration::addBlackURL(const TCHAR *URL) {
	if (NULL == URL)
		return -1;

	getBlackURLSet()->addDNS(URL);
	return 0;
}

int XMLConfiguration::getBlackURL(TiXmlElement * rule_root) {
	// enable?
	const TCHAR *  enable_attr = rule_root->Attribute(CONFIG_CONST_ENABLE);
	enableBlackURL(enable_attr);

	// ����
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			addBlackURL(ele->GetText());
		}

		node = node->NextSibling();
	}
	return 0;
}


//============================================================
// ���ֹ���
int XMLConfiguration::setTextCheck(const TCHAR *language, const TCHAR *enable) {
	return 0;
}


//============================================================
// ����Rules
int XMLConfiguration::parseRules(TiXmlNode *rules_root) {
	assert (0 == _tcscmp(rules_root->Value(), CONFIG_NODE_RULES));

	TiXmlNode *node = rules_root->FirstChild();
	while (NULL != node) {
		TiXmlElement * element = node->ToElement();
		if ( NULL != element ) {
			const TCHAR *  name_attr = element->Attribute(CONFIG_CONST_NAME);
			if (0 == _tcscmp(name_attr,		  CONFIG_NODE_NAME_BLACKURL)) {
				getBlackURL(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_WHITEURL)) {
				getWhiteURL(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_ONLINETIME)) {
				getOnlineSetting()->readconfig(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_SEARCH)) {
				getSearchRule()->readconfig(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_IMAGECHECK)) {
				getContentCheckSetting()->readconfig(element);
			} else {
			}
		}
		
		node = node->NextSibling();
	}

	return 0;
}

int XMLConfiguration::parseConfiguration(TiXmlElement * root) {
	assert (root != NULL);
	// rootӦ�ö�Ӧ<config>, ����Ļ����������ļ��Ѿ���
	if (_tcscmp(root->Value(), CONFIG_ROOT_VALUE) != 0) {
		return -1;
	}

	// ����XML
	TiXmlNode *node = root->FirstChild();
	while (NULL != node) {
		if (_tcscmp(node->Value(), CONFIG_NODE_RULES) == 0) {
			parseRules(node);
		} else if (_tcscmp(node->Value(), CONFIG_NODE_APPSET) == 0) {
			parseAppSet(node);
		} else {
		}
		node = node->NextSibling();
	}

	return 0;
}

int XMLConfiguration::readConfigFromFile(const TCHAR *filename) {
	TiXmlDocument doc(filename);
	if (!doc.LoadFile()) {
		readDefaultConfig();
		return -1;
	}

	TiXmlElement * root = doc.RootElement();
	parseConfiguration(root);

	return 0;
}


// ��ȡĬ��������Ϣ(��ʱ������)
int XMLConfiguration::readDefaultConfig() {
	return 0;
}


//========================================
// public members
int XMLConfiguration::loadConfig(const TCHAR * filename) {
	readConfigFromFile(filename);
	return 0;
}
