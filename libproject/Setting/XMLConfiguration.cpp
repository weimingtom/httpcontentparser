#include "StdAfx.h"
#include ".\xmlconfiguration.h"
#include ".\SearchRule.h"
#include ".\eyecaresetting.h"

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
XMLConfiguration::XMLConfiguration(void) {
}

XMLConfiguration::~XMLConfiguration(void) {
}
namespace {
// utilit fucntions
bool enabledFromString(const TCHAR *enable) {
	if (NULL != enable) {
		if (0 == _tcscmp(enable, CONFIG_CONST_ENABLE_FALSE)) {
			return false;
		} else {
			return true;
		}
	} else {
		return true;
	}
}

const char * enabledFromBool(const bool enabled) {
	if (true == enabled) {
		return CONFIG_CONST_ENABLE_TRUE;
	} else {
		return CONFIG_CONST_ENABLE_FALSE;
	}
}
};

///////////////////////////////////////////////////////////////////////////////////
// 保存规则
//

//==========================================================
// XML 保存函数
int XMLConfiguration::save() {
	// Create XML
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	doc.LinkEndChild(decl);

	// 创建根节点
	TiXmlElement * root_element = new TiXmlElement( CONFIG_ROOT_VALUE );
	
	saveRules(root_element);
	
	
	doc.LinkEndChild(root_element);
	doc.SaveFile("c:\\hello.xml");
	return 0;
}
int XMLConfiguration::saveRules(TiXmlElement *root) {
	TiXmlElement * rules_root = new TiXmlElement( CONFIG_NODE_RULES );
	// 保存上网时间规则
	saveOnlineHour(rules_root);
	saveWhiteURL(rules_root);
	saveBlackURL(rules_root);
	
	saveSearchRule(rules_root);	// 保存Search rules
	saveImageRule(rules_root);	// 保存ImageCheck
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

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_WHITEURL);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(white_url_set.needChecked()));
	// 添加URL
	white_url_set.beginEnum(&DNSEnum(rule_root));
	root->LinkEndChild(rule_root);
	return 0;
}

int XMLConfiguration::saveBlackURL(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_BLACKURL);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(black_url_set.needChecked()));

	// 添加URL
	black_url_set.beginEnum(&DNSEnum(rule_root));
	root->LinkEndChild(rule_root);
	return 0;
}

//==========================================================
// save Online hour
namespace {
class EnumOnlineHour : public Enumerator2<int, int> {
public:
	char * genBlocktime(const int day, const int hour) {
		_sntprintf(buffer, 1024, "%d%s%d", day, CONFIG_ONLINETIME_SEPERATE, hour);
		return buffer;
	}

	virtual int Enum(const int day, const int hour) {
		TiXmlElement * blocktime = new TiXmlElement(CONFIG_NODE_NAME_BLACKTIME);

		TiXmlText * itemitem = new TiXmlText(genBlocktime(day, hour));

		blocktime->LinkEndChild(itemitem);
		rule_root_->LinkEndChild(blocktime);

		return 0;
	}
public:
	EnumOnlineHour(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
	}
private:
	TiXmlElement * rule_root_;
	TCHAR buffer[1024];	// 避免重复
};
};

int XMLConfiguration::saveOnlineHour(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_ONLINETIME);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(online_setting.isEnabled()));

	online_setting.enumBlockHour(&EnumOnlineHour(rule_root));
	
	root->LinkEndChild(rule_root);
	return 0;
}

//==========================================================
// 保存图片检测规则
int XMLConfiguration::saveImageRule(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_IMAGECHECK);

	// jgp
	TiXmlElement *item_jpg = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_jpg->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_JPG);
	item_jpg->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(content_check_.needCheck(IMAGE_TYPE_JPEG)));
	rule_root->LinkEndChild(item_jpg);

	// bmp
	TiXmlElement *item_bmp = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_bmp->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_BMP);
	item_bmp->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(content_check_.needCheck(IMAGE_TYPE_BMP)));
	rule_root->LinkEndChild(item_bmp);

	// gif
	TiXmlElement *item_gif = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_gif->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_GIF);
	item_gif->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(content_check_.needCheck(IMAGE_TYPE_GIF)));
	rule_root->LinkEndChild(item_gif);

	// png
	TiXmlElement *item_png = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_png->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_PNG);
	item_png->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(content_check_.needCheck(IMAGE_TYPE_PNG)));
	rule_root->LinkEndChild(item_png);

	root->LinkEndChild(rule_root);
	return 0;
}

//==========================================================
// search rules
namespace {
class EnumBlackWord : public Enumerator1<std::string> {
public:
	virtual int Enum(const std::string &data1) {
		TiXmlElement * blackword = new TiXmlElement(CONFIG_NODE_BLACK_SEARCHWORD);
		TiXmlText * word = new TiXmlText(data1);
		blackword->LinkEndChild(word);
		rule_root_->LinkEndChild(blackword);

		return 0;
	}
public:
	EnumBlackWord(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
	}
private:
	TiXmlElement * rule_root_;
};

class EnumSearchEngine : public Enumerator2<std::string, bool> {
public:
	virtual int Enum(const std::string &data1, const bool enabled) {
		TiXmlElement * searchengine_item = new TiXmlElement(CONDIG_NODE_SEARCH_ENGINE_ITEM);
		searchengine_item->SetAttribute(CONFIG_CONST_NAME, data1);
		searchengine_item->SetAttribute(CONFIG_CONST_ENABLE, enabled);
		rule_root_->LinkEndChild(searchengine_item);

		return 0;
	}
public:
	EnumSearchEngine(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
	}
private:
	TiXmlElement * rule_root_;
};
};
int XMLConfiguration::saveSearchRule(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_SEARCH);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(search_rule.isEnabled()));

	// 设置black word
	TiXmlElement * blackword = new TiXmlElement(CONFIG_NODE_BLACK_SEARCHWORD);
	search_rule.enumBlackWord(&EnumBlackWord(blackword));
	rule_root->LinkEndChild(blackword);

	TiXmlElement *search_engine = new TiXmlElement(CONFIG_NODE_SEARCH_ENGINES);
	search_rule.enumSearchEngine(&EnumSearchEngine(search_engine));
	rule_root->LinkEndChild(search_engine);

	root->LinkEndChild(rule_root);
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
				getAuthorizeSetting(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_EYECARE) == 0) {
				// 眼睛保护功能
				getEyecareSetting(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_WEBHISTORY) == 0) {
				// 历史记录功能
				getWebHistoryRecorder(element);
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_SYSSETTING) == 0) {
				// 系统设置功能
				getSystemSetting(element);
			}
		}
		// 获取下一个
		node = node->NextSibling();
	}
	return 0;
}

//===============================================================
// Eyecare
int XMLConfiguration::enableEyecareSetting(const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	eye_care.Enable(enabled);
	return 0;
}

int XMLConfiguration::setEyecareState(const TCHAR *state, const TCHAR *timeleft) {
	long lt = _tcstol(timeleft, NULL, 10);
	if (0 == _tcscmp(state, CONFIG_APPSET_EYECARE_REST)) {
		eye_care.setState(EyecareSetting::EYECARE_TIME);
		eye_care.setLeftTime(lt);
	} else if (0 == _tcscmp(state, CONFIG_APPSET_EYECARE_ENTER)) {
		// 设置状体
		eye_care.setState(EyecareSetting::ENTERTAINMENT_TIME);
		eye_care.setLeftTime(lt);
	}
	return 0;
}

int XMLConfiguration::setEyecareSetting(const TCHAR *type, const TCHAR *timespan) {
	long lt = _tcstol(timespan, NULL, 10);
	if (0 == _tcscmp(type, CONFIG_APPSET_EYECARE_REST)) {
		eye_care.setRestTime(lt);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_EYECARE_ENTER)) {
		eye_care.setEntertainTime(lt);
	}

	return 0;
}

int XMLConfiguration::getEyecareSetting(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_ITEM_APPSET_EYECARE));

	// 设置它是否可用
	enableEyecareSetting(ele->Attribute(CONFIG_CONST_ENABLE));
	setEyecareState(ele->Attribute(CONFIG_APPSET_EYECARE_STATE), ele->Attribute(CONFIG_APPSET_EYECARE_TIMELEFT));

	TiXmlNode * node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele && 0 == _tcscmp(ele->Value(), CONFIG_APPSET_EYECARE_TIME)) {
			setEyecareSetting(ele->Attribute(CONFIG_CONST_NAME),
				ele->Attribute(CONFIG_APPSET_EYECARE_TIMESPAN));
		}

		node = node->NextSibling();
	}
	return 0;
}

//=========================================================
// WebHistory
int XMLConfiguration::enableWebHistoryRecord(const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	return 0;
}

int XMLConfiguration::setWebHistoryRecord(const TCHAR *type, const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE)) {
		web_history.recordPornPages(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE)) {
		web_history.recordAllPages(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_IMAGE)) {
		web_history.recordAllImage(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_IMAGE)) {
		web_history.recordPornImage(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE)) {
		web_history.recordAllWebsite(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE)) {
		web_history.recordPornWebsite(enabled);
	} else {
	}
	return 0;
}

int XMLConfiguration::getWebHistoryRecorder(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_ITEM_APPSET_WEBHISTORY));

	// 设置它是否可用
	enableWebHistoryRecord(ele->Attribute(CONFIG_CONST_ENABLE));

	TiXmlNode * node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele && 0 == _tcscmp(ele->Value(), CONFIG_APPSET_WEBHISTORY_CONTENT)) {
			setWebHistoryRecord(ele->Attribute(CONFIG_CONST_TYPPE), ele->Attribute(CONFIG_CONST_ENABLE));
		}

		node = node->NextSibling();
	}
	return 0;
}

//================================================
// Authorize
int XMLConfiguration::addUser(const TCHAR *username, const TCHAR *password) {
	if ( 0 == _tcscmp(username, CONFIG_APPSET_AUTHORIZE_USERTYPE_SU)) {
		authorize.setNewPassword(password, PASSWORD_SU);
	}
	return 0;
}
int XMLConfiguration::getAuthorizeSetting(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_ITEM_APPSET_AUTHORIZE));

	// 设置它是否可用
	enableWebHistoryRecord(ele->Attribute(CONFIG_CONST_ENABLE));

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
int XMLConfiguration::getSystemSetting(TiXmlElement * ele) {
	return 0;
}

//=========================================================
// rule set function
//========================================================
// 白名单是否可用
int XMLConfiguration::enableWhiteURL(const TCHAR *enable) {
	const bool checked = enabledFromString(enable);
	white_url_set.enableCheck(checked);
	return 0;
}

// 设置URL 白名单
int XMLConfiguration::addWhiteURL(const TCHAR *URL) {
	if (NULL == URL)
		return -1;

	white_url_set.addDNS(URL);
	return 0;
}

int XMLConfiguration::getWhiteURL(TiXmlElement * rule_root) {
	// enable?
	const TCHAR *  enable_attr = rule_root->Attribute(CONFIG_CONST_ENABLE);
	enableWhiteURL(enable_attr);
	// 内容
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
// 黑名单是否可用
int XMLConfiguration::enableBlackURL(const TCHAR *enable) {
	const bool checked = enabledFromString(enable);
	black_url_set.enableCheck(checked);
	return 0;
}

// 设置URL 黑名单
int XMLConfiguration::addBlackURL(const TCHAR *URL) {
	if (NULL == URL)
		return -1;

	black_url_set.addDNS(URL);
	return 0;
}

int XMLConfiguration::getBlackURL(TiXmlElement * rule_root) {
	// enable?
	const TCHAR *  enable_attr = rule_root->Attribute(CONFIG_CONST_ENABLE);
	enableBlackURL(enable_attr);

	// 内容
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
int XMLConfiguration::setSearchEngineCheck(const TCHAR *search_engine, const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	search_rule.addSearchHost(search_engine);
	search_rule.enableCheck(search_engine, enabled);
	return 0;
}
int XMLConfiguration::addBlackSearchWord(const TCHAR *word) {
	if (NULL == word)
		return -1;

	search_rule.addBlackSearchWord(word);
	return 0;
}

int XMLConfiguration::getSearchRule(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement * ele = node->ToElement();
		if (_tcscmp(node->Value(), CONFIG_NODE_SEARCH_ENGINES) == 0) {
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

// 获取Search  规则
// Search规则涉及到 搜索引擎和 Blacksearch word，
// 因此与其他的略有不同
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
			setSearchEngineCheck(ele->Attribute(CONFIG_CONST_NAME),
				ele->Attribute(CONFIG_CONST_ENABLE));
		}

		node = node->NextSibling();
	}
	return 0;
}


//========================================================
// 时间规则
int XMLConfiguration::onlineBlocktime(const TCHAR *time) {
	if (NULL == time)
		return -1;

	// 解析时间
	char *p1 = _tcsstr(time, CONFIG_ONLINETIME_SEPERATE);
	assert (NULL != p1);
	char *p2 = p1;
	int day = _tcstol(time, &p2, 10);
	assert (p1 == p2);
	int hour = _tcstol(p1 + 1, NULL, 10);
	
	online_setting.setHour(day, hour, false);
	return 0;
}


int XMLConfiguration::getOnlinetime(TiXmlElement * rule_root) {
	// 是否可用
	TiXmlElement *ele = rule_root->ToElement();
	bool enabled = true;
	if (ele != NULL) {
		enabled = enabledFromString(ele->Attribute(CONFIG_CONST_NAME));
	}
	online_setting.enableOnlineHour(enabled);

	// 获取不可上网的时间
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
// 图片规则
int XMLConfiguration::setImageCheck(const TCHAR *imagetype, const TCHAR *enable) {
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
			setImageCheck(ele->Attribute(CONFIG_NODE_IMAGETYPE), ele->Attribute(CONFIG_CONST_ENABLE));
		}

		node = node->NextSibling();
	}
	return 0;
}

//============================================================
// 文字规则
int XMLConfiguration::setTextCheck(const TCHAR *language, const TCHAR *enable) {
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

TCHAR * XMLConfiguration::getConfigFilePath(TCHAR *buffer, const int bufsize) {
	TCHAR directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, directory);
	_sntprintf(buffer, bufsize, "%s\\%s", directory, CONFIG_FILE_NAME);
	return buffer;
}

// 此函数负责读取配置
// 首先他会获取配置文件路径
// 如果配置文件存在，则直接从文件中获取配置信息
// 否则直接充值配置信息
int XMLConfiguration::readConfig() {
	TCHAR filename[MAX_PATH] = {0};
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
