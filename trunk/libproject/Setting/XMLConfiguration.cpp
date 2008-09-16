#include "StdAfx.h"
#include ".\xmlconfiguration.h"
#include ".\SearchRule.h"
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
XMLConfiguration::XMLConfiguration(void) {
}

XMLConfiguration::~XMLConfiguration(void) {
}

//======================================================
// ��������
int XMLConfiguration::parseAppSet(TiXmlNode *appset_root) {
	assert (0 == _tcscmp(appset_root->Value(), CONFIG_NODE_APPSET));

	TiXmlNode *node = appset_root->FirstChild();
	while (NULL != node) {
		if (_tcscmp(node->Value(), CONFIG_NODE_APPSET_AUTHORIZE) == 0) {
		} else if (_tcscmp(node->Value(), CONFIG_NODE_APPSET_EYECARE) == 0) {
		} else if (_tcscmp(node->Value(), CONFIG_NODE_APPSET_WEBHISTORY) == 0) {
		} else if (_tcscmp(node->Value(), CONFIG_NODE_APPSET_SYSSETTING) == 0) {
		}
		// ��ȡ��һ��
		node = node->NextSibling();
	}
	return 0;
}

//=========================================================
// rule set function
bool XMLConfiguration::checkEnable(const char *enable) const{
	if (NULL != enable) {
		if (0 == _tcscmp(enable, CONFIG_NODE_ENABLE_FALSE)) {
			return false;
		} else {
			return true;
		}
	} else {
		return true;
	}
}

//========================================================
// �������Ƿ����
int XMLConfiguration::enableWhiteURL(const char *enable) {
	const bool checked = checkEnable(enable);
	white_url_set.enableCheck(checked);
	return 0;
}

// ����URL ������
int XMLConfiguration::addWhiteURL(const char *URL) {
	if (NULL == URL)
		return -1;

	white_url_set.addDNS(URL);
	return 0;
}

int XMLConfiguration::getWhiteURL(TiXmlElement * rule_root) {
	// enable?
	const char *  enable_attr = rule_root->Attribute(CONFIG_NODE_ENABLE);
	enableWhiteURL(enable_attr);
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
int XMLConfiguration::enableBlackURL(const char *enable) {
	const bool checked = checkEnable(enable);
	black_url_set.enableCheck(checked);
	return 0;
}

// ����URL ������
int XMLConfiguration::addBlackURL(const char *URL) {
	if (NULL == URL)
		return -1;

	black_url_set.addDNS(URL);
	return 0;
}

int XMLConfiguration::getBlackURL(TiXmlElement * rule_root) {
	// enable?
	const char *  enable_attr = rule_root->Attribute(CONFIG_NODE_ENABLE);
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

//========================================================
// Search Rules
int XMLConfiguration::setSearchEngineCheck(const char *search_engine, const char *enable) {
	const bool enabled = checkEnable(enable);
	search_rule.addSearchHost(search_engine);
	search_rule.enableCheck(search_engine, enabled);
	return 0;
}
int XMLConfiguration::addBlackSearchWord(const char *word) {
	if (NULL == word)
		return -1;

	search_rule.addBlackSearchWord(word);
	return 0;
}

int XMLConfiguration::getSearchRule(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement * ele = node->ToElement();
		if (_tcscmp(node->Value(), CONFIG_NODE_SEARCH_ENGINE) == 0) {
			assert (NULL != ele);
			getSearchEngineSetting(ele);
		} else if (_tcscmp(node->Value(), CONFIG_NODE_BLACK_SEARCHWORD) == 0) {
			assert (NULL != ele);
			getSearchBlackWord(ele);
		} else {
		}

		node = node->NextSibling();
	}
	return 0;
}

// ��ȡSearch  ����
// Search�����漰�� ��������� Blacksearch word��
// ��������������в�ͬ
int XMLConfiguration::getSearchBlackWord(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			addBlackSearchWord(ele->GetText());
		}

		node = node->NextSibling();
	}
	return 0;
}

int XMLConfiguration::getSearchEngineSetting(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			setSearchEngineCheck(ele->Attribute(CONFIG_NODE_NAME),
				ele->Attribute(CONFIG_NODE_ENABLE));
		}

		node = node->NextSibling();
	}
	return 0;
}


//========================================================
// ʱ�����
int XMLConfiguration::onlineBlocktime(const char *time) {
	if (NULL == time)
		return -1;
	// ����ʱ��
	
	return 0;
}


int XMLConfiguration::getOnlinetime(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			onlineBlocktime(ele->GetText());
		}

		node = node->NextSibling();
	}
	return 0;
}

//========================================================
// ͼƬ����
int XMLConfiguration::setImageCheck(const char *imagetype, const char *enable) {
	if (NULL == imagetype || NULL == enable)
		return -1;

	if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_JPG)) {
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_BMP)) {
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_GIF)) {
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_PNG)) {
	} else {
		assert (false);
		return -1;
	}
	return 0;
}


int XMLConfiguration::getImageRule(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			setImageCheck(ele->Attribute(CONFIG_NODE_IMAGETYPE), ele->Attribute(CONFIG_NODE_ENABLE));
		}

		node = node->NextSibling();
	}
	return 0;
}

//============================================================
// ���ֹ���
int XMLConfiguration::setTextCheck(const char *language, const char *enable) {
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
			const char *  name_attr = element->Attribute(CONFIG_NODE_NAME);
			if (0 == _tcscmp(name_attr,		  CONFIG_NODE_NAME_BLACKURL)) {
				getBlackURL(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_WHITEURL)) {
				getWhiteURL(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_ONLINETIME)) {
				getOnlinetime(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_SEARCH)) {
				getSearchRule(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_IMAGECHECK)) {
				getImageRule(element);
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

int XMLConfiguration::readConfigFromFile(const char *filename) {
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

char * XMLConfiguration::getConfigFilePath(char *buffer, const int bufsize) {
	char directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, directory);
	_sntprintf(buffer, bufsize, "%s\\%s", directory, CONFIG_FILE_NAME);
	return buffer;
}

// �˺��������ȡ����
// ���������ȡ�����ļ�·��
// ��������ļ����ڣ���ֱ�Ӵ��ļ��л�ȡ������Ϣ
// ����ֱ�ӳ�ֵ������Ϣ
int XMLConfiguration::readConfig() {
	char filename[MAX_PATH] = {0};
	getConfigFilePath(filename, MAX_PATH);

	if (strlen(filename) == 0) {
		return readDefaultConfig();
	} else {
		return readConfigFromFile(filename);
	}
}

//========================================
// public members
int XMLConfiguration::initialize() {
	readConfig();
	return 0;
}