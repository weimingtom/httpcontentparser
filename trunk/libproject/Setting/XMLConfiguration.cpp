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
XMLConfiguration::XMLConfiguration() 
	: black_url_set_(CONFIG_NODE_NAME_BLACKURL)
	, white_url_set_(CONFIG_NODE_NAME_WHITEURL) {
	defaultSetting();
}

XMLConfiguration::~XMLConfiguration(void) {
}

void XMLConfiguration::defaultSetting() {
	getEyecareSetting()->initialize(getAuthorize(),  EyecareSetting::ENTERT_TIME);
	getDNSSetting()->initialize(getBlackURLSet(), getWhiteURLSet());
}

///////////////////////////////////////////////////////////////////////////////////
// 保存规则

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
// 保存规则
//==========================================================
// XML 保存函数
int XMLConfiguration::saveConfig(const TCHAR * filename) {
	// Create XML
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	doc.LinkEndChild(decl);

	// 创建根节点
	TiXmlElement * root_element = new TiXmlElement( CONFIG_ROOT_VALUE );
	
	saveRules(root_element);
	saveAppSetting(root_element);
	//getHotkey()->saveConfig(root_element);
	
	doc.LinkEndChild(root_element);

	doc.SaveFile(filename);
	return 0;
}
int XMLConfiguration::saveRules(TiXmlElement *root) {
	TiXmlElement * rules_root = new TiXmlElement( CONFIG_NODE_RULES );
	// 保存上网时间规则
	getOnlineSetting()->saveConfig(rules_root);
	getBlackURLSet()->saveConfig(rules_root);
	
	// 涉及两个类
	TiXmlElement * white_item = getWhiteURLSet()->saveConfig(rules_root);
	getDNSSetting()->saveConfig(white_item);

	getSearchRule()->saveConfig(rules_root);
	getContentCheckSetting()->saveConfig(rules_root);

	root->LinkEndChild(rules_root);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////
// 读入规则
//

//======================================================
// 程序设置
int XMLConfiguration::parseAppSet(TiXmlNode *appset_root) {
	assert (0 == _tcscmp(appset_root->Value(), CONFIG_NODE_APPSET));

	TiXmlNode *node = appset_root->FirstChild();
	while (NULL != node) {
		TiXmlElement * element = node->ToElement();
		if (NULL != element) {
			if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_AUTHORIZE) == 0) {
				// 授权机制
				getAuthorize()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_EYECARE) == 0) {
				// 眼睛保护功能
				getEyecareSetting()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_WEBHISTORY) == 0) {
				// 历史记录功能
				getWebHistoryRecordSetting()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_SYSSETTING) == 0) {
				// 系统设置功能
				// getSystemSetting(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_SCREENSAVER) == 0) {
				// 屏幕保存设置功能
				getScreenSave()->readconfig(element);
	/*		} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_HOTKEY) == 0) {
				getHotkey()->readconfig(element);*/
			}
		}
		// 获取下一个
		node = node->NextSibling();
	}
	return 0;
}

//============================================================
// 解析Rules
int XMLConfiguration::parseRules(TiXmlNode *rules_root) {
	assert (0 == _tcscmp(rules_root->Value(), CONFIG_NODE_RULES));

	TiXmlNode *node = rules_root->FirstChild();
	while (NULL != node) {
		TiXmlElement * element = node->ToElement();
		if ( NULL != element ) {
			const TCHAR *  name_attr = element->Attribute(CONFIG_CONST_NAME);
			if (0 == _tcscmp(name_attr,		  CONFIG_NODE_NAME_BLACKURL)) {
				getBlackURLSet()->readconfig(element);
			} else if (0 == _tcscmp(name_attr, CONFIG_NODE_NAME_WHITEURL)) {
				getDNSSetting()->readconfig(element);
				getWhiteURLSet()->readconfig(element);
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
	// root应该对应<config>, 否则的话可能配置文件已经损坏
	if (_tcscmp(root->Value(), CONFIG_ROOT_VALUE) != 0) {
		return -1;
	}

	// 解析XML
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


// 读取默认配置信息(暂时不用了)
int XMLConfiguration::readDefaultConfig() {
	return 0;
}


//========================================
// public members
int XMLConfiguration::loadConfig(const TCHAR * filename) {
	readConfigFromFile(filename);
	return 0;
}
