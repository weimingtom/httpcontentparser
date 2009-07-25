#include "StdAfx.h"
#include ".\xmlconfiguration.h"
#include ".\SearchRule.h"
#include ".\eyecaresetting.h"
#include ".\autoclean.h"
#include <utility\syncutility.h>
#include <webcontenttype.h>
#include <crypt.h>
#include <passwordtype.h>
#include <tinyXML\tinyxml.h>
#include <webcontenttype.h>
#include <DebugOutput.h>
#include <apputility\apputility.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <zlib\zlib.h>

#define __SETTING_XMLCONFIGURATION_TRC__(FMT)		_DEBUG_STREAM_TRC_("[Family007][Setting][XMLConfiguration] "<<FMT)

#define CONFIG_FILE_MUTEX_NAME	TEXT("24483F0A-A8B1-4a37-8E47-26E256C10884")

namespace {
TCHAR * generateTempFile(const TCHAR * filename, TCHAR * fullpath, int buffersize) {
	TCHAR tempfolder[MAX_PATH];
	GetTempPath( MAX_PATH, tempfolder );
	_sntprintf(fullpath, buffersize, "%s\\%s", tempfolder, filename);
	return fullpath;
}
};

//=====================================================
// constructor and deconstructor
XMLConfiguration::XMLConfiguration() 
	: black_url_set_(CONFIG_NODE_NAME_BLACKURL)
	, white_url_set_(CONFIG_NODE_NAME_WHITEURL) {
	first_time_ = false;
	uninstall_ = false;
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
	
	getAuthorize()->saveconfig(appsetting_root);
	getEyecareSetting()->saveconfig(appsetting_root);
	getWebHistoryRecordSetting()->saveconfig(appsetting_root);
	
	getScreenshotSetting()->saveconfig(appsetting_root);
	getHotkey()->saveconfig(appsetting_root);
	getTimeoutSwitch()->saveconfig(appsetting_root);
	getProgramControl()->saveConfig(appsetting_root);
	getMiscSetting()->saveConfig(appsetting_root);
	root->LinkEndChild(appsetting_root);
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
			const TCHAR *p =node->Value();
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
				getScreenshotSetting()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_PROGRAM_CONTROL) == 0) {
				// 程序控制
				getProgramControl()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_HOTKEY) == 0) {
				// 热键设置
				getHotkey()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_MODEL_AUTOSWITCH) == 0) {
				// 自动切换
				getTimeoutSwitch()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_SWITCHTOCHILD_ONCLOSE) == 0) {
				getMiscSetting()->readconfig(element);
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

	// 获取uninstall及initialize
	const TCHAR * install = root->Attribute(CONFIG_ATTRIBUTE_INSTALL);
	if ( NULL != install) {
		// 在配置文件当中保存的是反值
		// 因此应该去反，另外在保存的时候也应该取反
		setUninstall(!enabledFromString(install));
	}
	const TCHAR * initialize = root->Attribute(CONFIG_ATTRIBUTE_FIRSTTIME);
	if ( NULL != initialize) {
		first_time_ = enabledFromString(initialize);
	} else {
		first_time_ = false;
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

int XMLConfiguration::readConfigFromFile(const TCHAR *encrpytedfile) {
	using namespace yanglei_utility;
	__SETTING_XMLCONFIGURATION_TRC__("readConfigFromFile begin");
	
	int rc = 0;
	TiXmlElement * root  = NULL;
	TiXmlDocument doc;

	// 生成一个文件名
	const char * tempfilename = ".configg.xml";
	TCHAR decryptfile[MAX_PATH];
	generateTempFile(tempfilename, decryptfile, MAX_PATH);
	
	CSysMutex mutex(CONFIG_FILE_MUTEX_NAME);
	SingleLock<CSysMutex> lock(&mutex);

	
	if (false == yanglei_utility::DecryptFile((LPTSTR)encrpytedfile, decryptfile)) {
		__SETTING_XMLCONFIGURATION_TRC__("DecryptFile{read} "<< encrpytedfile << "  failed "<<GetLastError())
		readDefaultConfig();
		rc = 1;
		goto exit;
	}

	
	if (!doc.LoadFile(decryptfile)) {
		__SETTING_XMLCONFIGURATION_TRC__("readConfigFromFile{read} "<< decryptfile << "  failed "<<GetLastError())
		readDefaultConfig();
		rc = 2;
		goto exit;
	}

	root = doc.RootElement();
	parseConfiguration(root);

exit:
	if (FALSE == DeleteFile(decryptfile)) {
		__SETTING_XMLCONFIGURATION_TRC__("DeleteFile{read} " << decryptfile<<"  failed "<<GetLastError())
	}

	__SETTING_XMLCONFIGURATION_TRC__("readConfigFromFile end");

	return rc;
}

///////////////////////////////////////////////////////////////////////////////////
// 保存规则
//==========================================================
// XML 保存函数
int XMLConfiguration::saveConfig(const TCHAR * configpath) {
	__SETTING_XMLCONFIGURATION_TRC__("saveConfig begin");
	using namespace yanglei_utility;
	CSysMutex mutex(CONFIG_FILE_MUTEX_NAME);
	SingleLock<CSysMutex> lock(&mutex);

	// 文件保存在个人文件夹当中
	const char * tempfilename = ".configka.xml";
	TCHAR encryptfile[MAX_PATH] ;
	generateTempFile(tempfilename, encryptfile, MAX_PATH);

	// Create XML
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	doc.LinkEndChild(decl);

	// 创建根节点
	TiXmlElement * root_element = new TiXmlElement( CONFIG_ROOT_VALUE );

	// 是否卸载
	// 在配置文件当中保存的是反值
	// 因此应该去反，另外在保存的时候也应该取反
	root_element->SetAttribute(CONFIG_ATTRIBUTE_INSTALL, enabledFromBool(!uninstall()));
	
	saveRules(root_element);
	saveAppSetting(root_element);
	doc.LinkEndChild(root_element);

	doc.SaveFile(encryptfile);
	__SETTING_XMLCONFIGURATION_TRC__(" TiXmlDocument::SaveFile Uncrypt "<<encryptfile<<"  Errono: "<< GetLastError());

	yanglei_utility::EncryptFile((LPTSTR)encryptfile, (LPTSTR)configpath);
	DeleteFile(encryptfile);
	__SETTING_XMLCONFIGURATION_TRC__("Delete File" << encryptfile <<"  Errono: "<< GetLastError());

	SettingItem::setModified(false);

	__SETTING_XMLCONFIGURATION_TRC__("saveConfig end");
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

	// 之前的可能调用一些函数，导致状态变为以改变
	// 因为是初始化函数，所以一定不会改变的。
	SettingItem::setModified(false);
	return 0;
}

