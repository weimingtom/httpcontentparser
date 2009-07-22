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
#include <apputility.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <zlib\zlib.h>

#define CONFIG_FILE_MUTEX_NAME	TEXT("24483F0A-A8B1-4a37-8E47-26E256C10884")

//=====================================================
// constructor and deconstructor
XMLConfiguration::XMLConfiguration() 
	: black_url_set_(CONFIG_NODE_NAME_BLACKURL)
	, white_url_set_(CONFIG_NODE_NAME_WHITEURL) {
	first_time_ = false;
	uninstall_ = false;
	initialize_completed_ = false;
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

///////////////////////////////////////////////////////////////////////////////////
// �������
//==========================================================
// XML ���溯��
int XMLConfiguration::saveConfig(const TCHAR * configpath) {
	if (false == initialize_completed_) {
		// ���û�м�����ȫ�����ܹ������ļ�
		SettingItem::setModified(false);
		return 0;
	}

	using namespace yanglei_utility;
	CSysMutex mutex(CONFIG_FILE_MUTEX_NAME);
	SingleLock<CSysMutex> lock(&mutex);

	TCHAR encryptfile[] = ".\\.configka.xml";

	// Create XML
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	doc.LinkEndChild(decl);

	// �������ڵ�
	TiXmlElement * root_element = new TiXmlElement( CONFIG_ROOT_VALUE );

	// �Ƿ�ж��
	// �������ļ����б�����Ƿ�ֵ
	// ���Ӧ��ȥ���������ڱ����ʱ��ҲӦ��ȡ��
	root_element->SetAttribute(CONFIG_ATTRIBUTE_INSTALL, enabledFromBool(!uninstall()));
	
	saveRules(root_element);
	saveAppSetting(root_element);
	
	doc.LinkEndChild(root_element);

	
	if (false == doc.SaveFile(encryptfile)) {
		_DEBUG_STREAM_TRC_("[XMLConfiguration] TiXmlDocument::SaveFile Failed "<< GetLastError());
	}

	yanglei_utility::EncryptFile((LPTSTR)encryptfile, (LPTSTR)configpath);
	if(FALSE == DeleteFile(encryptfile)) {
		_DEBUG_STREAM_TRC_("[XMLConfiguration] Delete File Failed "<< GetLastError());
	}

	SettingItem::setModified(false);
	return 0;
}
int XMLConfiguration::saveRules(TiXmlElement *root) {
	TiXmlElement * rules_root = new TiXmlElement( CONFIG_NODE_RULES );
	// ��������ʱ�����
	getOnlineSetting()->saveConfig(rules_root);
	getBlackURLSet()->saveConfig(rules_root);
	
	// �漰������
	TiXmlElement * white_item = getWhiteURLSet()->saveConfig(rules_root);
	getDNSSetting()->saveConfig(white_item);

	getSearchRule()->saveConfig(rules_root);
	getContentCheckSetting()->saveConfig(rules_root);

	root->LinkEndChild(rules_root);
	return 0;
}

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
			const TCHAR *p =node->Value();
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
				// getSystemSetting(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_SCREENSAVER) == 0) {
				// ��Ļ�������ù���
				getScreenshotSetting()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_PROGRAM_CONTROL) == 0) {
				// �������
				getProgramControl()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_HOTKEY) == 0) {
				// �ȼ�����
				getHotkey()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_MODEL_AUTOSWITCH) == 0) {
				// �Զ��л�
				getTimeoutSwitch()->readconfig(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_SWITCHTOCHILD_ONCLOSE) == 0) {
				getMiscSetting()->readconfig(element);
			}
		}
		// ��ȡ��һ��
		node = node->NextSibling();
	}
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
	// rootӦ�ö�Ӧ<config>, ����Ļ����������ļ��Ѿ���
	if (_tcscmp(root->Value(), CONFIG_ROOT_VALUE) != 0) {
		return -1;
	}

	// ��ȡuninstall��initialize
	const TCHAR * install = root->Attribute(CONFIG_ATTRIBUTE_INSTALL);
	if ( NULL != install) {
		// �������ļ����б�����Ƿ�ֵ
		// ���Ӧ��ȥ���������ڱ����ʱ��ҲӦ��ȡ��
		setUninstall(!enabledFromString(install));
	}
	const TCHAR * initialize = root->Attribute(CONFIG_ATTRIBUTE_FIRSTTIME);
	if ( NULL != initialize) {
		first_time_ = enabledFromString(initialize);
	} else {
		first_time_ = false;
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

int XMLConfiguration::readConfigFromFile(const TCHAR *encrpytedfile) {
	using namespace yanglei_utility;
	CSysMutex mutex(CONFIG_FILE_MUTEX_NAME);
	SingleLock<CSysMutex> lock(&mutex);
	
	TCHAR decryptfile[] = ".\\.configg.xml";
	yanglei_utility::DecryptFile((LPTSTR)encrpytedfile, decryptfile);


	TiXmlDocument doc(decryptfile);
	if (!doc.LoadFile()) {
		_DEBUG_STREAM_TRC_("[XMLConfiguration]readConfigFromFile failed "<<GetLastError())
		readDefaultConfig();
		return -1;
	}

	TiXmlElement * root = doc.RootElement();
	parseConfiguration(root);

	if (FALSE == DeleteFile(decryptfile)) {
		_DEBUG_STREAM_TRC_("[XMLConfiguration]DeleteFile{read} failed "<<GetLastError())
	}

	return 0;
}


// ��ȡĬ��������Ϣ(��ʱ������)
int XMLConfiguration::readDefaultConfig() {
	return 0;
}


//========================================
// public members
int XMLConfiguration::loadConfig(const TCHAR * filename) {
	initialize_completed_ = false;
	readConfigFromFile(filename);
	initialize_completed_ = true;

	// ֮ǰ�Ŀ��ܵ���һЩ����������״̬��Ϊ�Ըı�
	// ��Ϊ�ǳ�ʼ������������һ������ı�ġ�
	SettingItem::setModified(false);
	return 0;
}

