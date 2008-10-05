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
XMLConfiguration::XMLConfiguration() {
	defaultSetting();
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

const char * Eyecare_state(const int state) {
	if (state == EyecareSetting::ENTERT_TIME) {
		return CONFIG_APPSET_EYECARE_ENTER;
	} else if (state == EyecareSetting::EYECARE_TIME) {
		return CONFIG_APPSET_EYECARE_EYECARE;
	} else {
		assert(false); 
		return CONFIG_APPSET_EYECARE_EYECARE;
	}
}

const char * UserType(const int user_type) {
	if ( user_type == PASSWORD_SU) {
		return CONFIG_APPSET_AUTHORIZE_USERTYPE_SU;
	} else {
		assert (false);
		return CONFIG_APPSET_AUTHORIZE_USERTYPE_OTHER;
	}
}
};

void XMLConfiguration::defaultSetting() {
	getEyecareSetting()->initialize(getAuthorize(),  EyecareSetting::ENTERT_TIME);
	getDNSSetting()->initialize(getBlackURLSet(), getWhiteURLSet());
}

///////////////////////////////////////////////////////////////////////////////////
// 保存规则

namespace {
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

int XMLConfiguration::saveAuthorize(TiXmlElement *app_root) {
	TiXmlElement * author_root = new TiXmlElement(CONFIG_ITEM_APPSET_AUTHORIZE);
	
	getAuthorize()->EnumUsers(&EnumUsersInfo(author_root));
	app_root->LinkEndChild(author_root);
	return 0;
}

//////////////////////////////////////////////////////////
// 保存
int XMLConfiguration::saveEyecare(TiXmlElement *app_root) {
	TCHAR buffer[1024];

	//=========================================
	// 设置属性
	TiXmlElement * eyecare_root = new TiXmlElement( CONFIG_ITEM_APPSET_EYECARE);
	eyecare_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getEyecareSetting()->isEnabled()));
	eyecare_root->SetAttribute(CONFIG_APPSET_EYECARE_STATE, Eyecare_state(getEyecareSetting()->getState()));

	// 保存Term_mode
	_sntprintf(buffer, 1024, "%d", getEyecareSetting()->getTerminatedMode());
	eyecare_root->SetAttribute(CONFIG_APPSET_EYECARE_TERM_MODE, buffer);

	//==========================================
	// 子集点
	// 设置剩余时间
	_sntprintf(buffer, 1024, "%d", getEyecareSetting()->getRemainTime());
	eyecare_root->SetAttribute(CONFIG_APPSET_EYECARE_TIMELEFT, buffer);

	// 设置娱乐事件
	TiXmlElement * enter_time = new TiXmlElement(CONFIG_APPSET_EYECARE_TIME);
	enter_time->SetAttribute(CONFIG_CONST_NAME, CONFIG_APPSET_EYECARE_ENTER);

	_sntprintf(buffer, 1024, "%d", getEyecareSetting()->getEnterTime());	// 设置娱乐时间间隔
	enter_time->SetAttribute(CONFIG_APPSET_EYECARE_TIMESPAN, buffer);
	eyecare_root->LinkEndChild(enter_time);

	// 设置休息时间
	TiXmlElement * eyecare_time = new TiXmlElement(CONFIG_APPSET_EYECARE_TIME);
	eyecare_time->SetAttribute(CONFIG_CONST_NAME, CONFIG_APPSET_EYECARE_EYECARE);

	_sntprintf(buffer, 1024, "%d", getEyecareSetting()->getEyecareTime());
	eyecare_time->SetAttribute(CONFIG_APPSET_EYECARE_TIMESPAN, buffer);
	eyecare_root->LinkEndChild(eyecare_time);

	app_root->LinkEndChild(eyecare_root);
	return 0;
}

int XMLConfiguration::saveWebHistory(TiXmlElement * app_root) {
	TiXmlElement * webhistory_root = new TiXmlElement(CONFIG_ITEM_APPSET_WEBHISTORY); 
	webhistory_root->SetAttribute(CONFIG_CONST_NAME,  enabledFromBool(getWebHistoryRecordSetting()->isEnabled()));

	// All Images
	TiXmlElement * allimage = new TiXmlElement(CONFIG_APPSET_WEBHISTORY_CONTENT); 
	allimage->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_ALL_IMAGE);
	allimage->SetAttribute(CONFIG_CONST_NAME, enabledFromBool(getWebHistoryRecordSetting()->recordAllImage()));
	webhistory_root->LinkEndChild(allimage);

	TiXmlElement * allpages = new TiXmlElement(CONFIG_APPSET_WEBHISTORY_CONTENT); 
	allpages->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE);
	allpages->SetAttribute(CONFIG_CONST_NAME, enabledFromBool(getWebHistoryRecordSetting()->recordAllPages()));
	webhistory_root->LinkEndChild(allpages);

	TiXmlElement * allwebsite = new TiXmlElement(CONFIG_APPSET_WEBHISTORY_CONTENT); 
	allwebsite->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE);
	allwebsite->SetAttribute(CONFIG_CONST_NAME, enabledFromBool(getWebHistoryRecordSetting()->recordAllWebsite()));
	webhistory_root->LinkEndChild(allwebsite);

	// Porn
	TiXmlElement * porn_Iimage = new TiXmlElement( CONFIG_APPSET_WEBHISTORY_CONTENT ); 
	porn_Iimage->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_PORN_IMAGE);
	porn_Iimage->SetAttribute(CONFIG_CONST_NAME, enabledFromBool(getWebHistoryRecordSetting()->recordPornImage()));
	webhistory_root->LinkEndChild(porn_Iimage);

	TiXmlElement * porn_pages = new TiXmlElement( CONFIG_APPSET_WEBHISTORY_CONTENT ); 
	porn_pages->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE);
	porn_pages->SetAttribute(CONFIG_CONST_NAME, enabledFromBool(getWebHistoryRecordSetting()->recordPornPages()));
	webhistory_root->LinkEndChild(porn_pages);

	TiXmlElement * porn_website = new TiXmlElement( CONFIG_APPSET_WEBHISTORY_CONTENT ); 
	porn_website->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE);
	porn_website->SetAttribute(CONFIG_CONST_NAME, enabledFromBool(getWebHistoryRecordSetting()->recordPornWebsite()));
	webhistory_root->LinkEndChild(porn_website);

	app_root->LinkEndChild(webhistory_root);
	return 0;
}

int XMLConfiguration::saveAppSetting(TiXmlElement * root) {
	TiXmlElement * appsetting_root = new TiXmlElement( CONFIG_NODE_APPSET );
	
	saveWebHistory(appsetting_root);
	saveEyecare(appsetting_root);
	saveAuthorize(appsetting_root);
	saveScreensave(appsetting_root);
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
	
	doc.LinkEndChild(root_element);

	doc.SaveFile(filename);
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
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getWhiteURLSet()->isEnabled()));
	rule_root->SetAttribute(CONFIG_WHITEURL_JUSTPASSED, enabledFromBool(getDNSSetting()->justPassWhiteDNS()));
	// 添加URL
	getWhiteURLSet()->beginEnum(&DNSEnum(rule_root));
	root->LinkEndChild(rule_root);
	return 0;
}

int XMLConfiguration::saveBlackURL(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_BLACKURL);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getBlackURLSet()->isEnabled()));

	// 添加URL
	getBlackURLSet()->beginEnum(&DNSEnum(rule_root));
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
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getOnlineSetting()->isEnabled()));

	getOnlineSetting()->enumBlockHour(&EnumOnlineHour(rule_root));
	
	root->LinkEndChild(rule_root);
	return 0;
}

//==========================================================
// 保存屏幕保存功能
int XMLConfiguration::saveScreensave(TiXmlElement * root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_ITEM_APPSET_SCREENSAVER);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(screen_save_.isEnabled()));
	rule_root->SetAttribute(CONSIG_CONST_TIMESPAN, TEXT("10"));

	TiXmlElement * auto_save = new TiXmlElement(CONFIG_APPSET_SCREENSAVER_AUTOCLEAR);
	auto_save->SetAttribute(CONFIG_CONST_ENABLE,	enabledFromBool(screen_save_.isEnabled()));
	auto_save->SetAttribute(CONFIG_CONST_MIN,		enabledFromBool(screen_save_.isEnabled()));
	auto_save->SetAttribute(CONFIG_CONST_MAX,		enabledFromBool(screen_save_.isEnabled()));
	auto_save->SetAttribute(CONSIG_CONST_TIMESPAN,	enabledFromBool(screen_save_.isEnabled()));
	rule_root->LinkEndChild(auto_save);

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
	item_jpg->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getContentCheckSetting()->needCheck(IMAGE_TYPE_JPEG)));
	rule_root->LinkEndChild(item_jpg);

	// bmp
	TiXmlElement *item_bmp = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_bmp->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_BMP);
	item_bmp->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getContentCheckSetting()->needCheck(IMAGE_TYPE_BMP)));
	rule_root->LinkEndChild(item_bmp);

	// gif
	TiXmlElement *item_gif = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_gif->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_GIF);
	item_gif->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getContentCheckSetting()->needCheck(IMAGE_TYPE_GIF)));
	rule_root->LinkEndChild(item_gif);

	// png
	TiXmlElement *item_png = new TiXmlElement(CONFIG_NODE_IMAGE_CHECK_ITEM);
	item_png->SetAttribute(CONFIG_NODE_IMAGETYPE, CONFIG_NODE_IMAGETYPE_PNG);
	item_png->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getContentCheckSetting()->needCheck(IMAGE_TYPE_PNG)));
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
		searchengine_item->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(enabled));
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
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getSearchRule()->isEnabled()));

	// 设置black word
	TiXmlElement * blackword = new TiXmlElement(CONFIG_NODE_BLACK_SEARCHWORD);
	getSearchRule()->enumBlackWord(&EnumBlackWord(blackword));
	rule_root->LinkEndChild(blackword);

	TiXmlElement *search_engine = new TiXmlElement(CONFIG_NODE_SEARCH_ENGINES);
	getSearchRule()->enumSearchEngine(&EnumSearchEngine(search_engine));
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
			} else if (_tcscmp(node->Value(), CONFIG_ITEM_APPSET_SCREENSAVER) == 0) {
				// 屏幕保存设置功能
				getScreensave(element);
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
	getEyecareSetting()->enable(enabled);
	return 0;
}

int XMLConfiguration::setEyecareState(const TCHAR *state, const TCHAR *value) {
	long lt = _tcstol(value, NULL, 10);
	if (0 == _tcscmp(state, CONFIG_APPSET_EYECARE_EYECARE)) {
		getEyecareSetting()->setState(EyecareSetting::EYECARE_TIME);
		getEyecareSetting()->setLeftTime(lt);
	} else if (0 == _tcscmp(state, CONFIG_APPSET_EYECARE_ENTER)) {
		// 设置状体
		getEyecareSetting()->setState(EyecareSetting::ENTERT_TIME);
		getEyecareSetting()->setLeftTime(lt);
	}
	return 0;
}

int XMLConfiguration::setEyecareSetting(const TCHAR *type, const TCHAR *timespan) {
	long lt = _tcstol(timespan, NULL, 10);
	if (0 == _tcscmp(type, CONFIG_APPSET_EYECARE_EYECARE)) {
		getEyecareSetting()->setEyecareTime(lt);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_EYECARE_ENTER)) {
		getEyecareSetting()->setEnterTime(lt);
	}

	return 0;
}

int XMLConfiguration::setEyecareTermMode(const TCHAR * value) {
	long lt = _tcstol(value, NULL, 10);
	getEyecareSetting()->setTerimatedMode(lt);
	return 0;
}

int XMLConfiguration::getEyecareSetting(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_ITEM_APPSET_EYECARE));

	// 设置它是否可用
	enableEyecareSetting(ele->Attribute(CONFIG_CONST_ENABLE));
	setEyecareState(ele->Attribute(CONFIG_APPSET_EYECARE_STATE), ele->Attribute(CONFIG_APPSET_EYECARE_TIMELEFT));
	setEyecareTermMode(ele->Attribute(CONFIG_APPSET_EYECARE_TERM_MODE));

	TiXmlNode * node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			if (0 == _tcscmp(ele->Value(), CONFIG_APPSET_EYECARE_TIME)) {
			setEyecareSetting(ele->Attribute(CONFIG_CONST_NAME),
				ele->Attribute(CONFIG_APPSET_EYECARE_TIMESPAN));
			}
		}

		node = node->NextSibling();
	}
	return 0;
}

//=========================================================
// WebHistory
int XMLConfiguration::enableWebHistoryRecord(const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	web_history_.enable(enabled);
	return 0;
}

int XMLConfiguration::setWebHistoryRecord(const TCHAR *type, const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE)) {
		getWebHistoryRecordSetting()->recordPornPages(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE)) {
		getWebHistoryRecordSetting()->recordAllPages(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_IMAGE)) {
		getWebHistoryRecordSetting()->recordAllImage(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_IMAGE)) {
		getWebHistoryRecordSetting()->recordPornImage(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE)) {
		getWebHistoryRecordSetting()->recordAllWebsite(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE)) {
		getWebHistoryRecordSetting()->recordPornWebsite(enabled);
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

//===============================================
// Screensave
int XMLConfiguration::getScreensave(TiXmlElement * ele){
	enableScreensave(ele->Attribute(CONFIG_CONST_ENABLE));
	setScreensaveTimespan(ele->Attribute(CONSIG_CONST_TIMESPAN));

	return 0;
}
int XMLConfiguration::enableScreensave(const TCHAR *enable){
	const bool enabled = enabledFromString(enable);
	screen_save_.enable(enabled);
	return 0;
}

int XMLConfiguration::setScreensaveTimespan(const TCHAR *timespan){
	screen_save_.setTimeSpan(atoi(timespan));
	return 0;
}

int XMLConfiguration::setAutoClean(TiXmlElement * ele) {
	TiXmlNode *node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement * element = node->ToElement();
		if (element && _tcscmp(element->Value(), CONFIG_APPSET_SCREENSAVER_AUTOCLEAR) == 0) {
			enableScreenSaveAutoClean(element->Attribute(CONFIG_CONST_ENABLE));
			setScreensaveAutoCleanTimespan(element->Attribute(CONSIG_CONST_TIMESPAN));
			setAutoCleanTimeScale(element->Attribute(CONFIG_CONST_MAX), element->Attribute(CONFIG_CONST_MIN));
		}
		node = node->NextSibling();
	}
	return 0;
}

int XMLConfiguration::enableScreenSaveAutoClean(const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	screen_save_auto_clean_.enable(enabled);
	return 0;
}
int XMLConfiguration::setScreensaveAutoCleanTimespan(const TCHAR *timespan) {
	screen_save_auto_clean_.setTimespan(_ttoi64(timespan));
	return 0;
}

int XMLConfiguration::setAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint) {
	const __int64 low_bound = _ttoi64(mint);
	const __int64 upper_bound = _ttoi64(maxt);
	screen_save_auto_clean_.setScale(upper_bound, low_bound);
	return 0;
}


//================================================
// Authorize
int XMLConfiguration::addUser(const TCHAR *username, const TCHAR *password) {
	if ( 0 == _tcscmp(username, CONFIG_APPSET_AUTHORIZE_USERTYPE_SU)) {
		getAuthorize()->setSuPassword(password);
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
	getWhiteURLSet()->enable(checked);
	return 0;
}

int XMLConfiguration::enableJustPassWhite(const TCHAR *enable) {
	const bool checked = enabledFromString(enable);
	getDNSSetting()->justPassWhiteDNS(checked);
	return 0;
}
// 设置URL 白名单
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
	getBlackURLSet()->enable(checked);
	return 0;
}

// 设置URL 黑名单
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
	getSearchRule()->addSearchHost(search_engine);
	getSearchRule()->enableCheck(search_engine, enabled);
	return 0;
}
int XMLConfiguration::addBlackSearchWord(const TCHAR *word) {
	if (NULL == word)
		return -1;

	getSearchRule()->addBlackSearchWord(word);
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
	
	getOnlineSetting()->setHour(day, hour, false);
	return 0;
}


int XMLConfiguration::getOnlinetime(TiXmlElement * rule_root) {
	// 是否可用
	TiXmlElement *ele = rule_root->ToElement();
	bool enabled = true;
	if (ele != NULL) {
		enabled = enabledFromString(ele->Attribute(CONFIG_CONST_NAME));
	}
	getOnlineSetting()->enable(enabled);

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
		getContentCheckSetting()->enableCheck(IMAGE_TYPE_JPEG, enabledFromString(enable));
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_BMP)) {
		getContentCheckSetting()->enableCheck(IMAGE_TYPE_BMP, enabledFromString(enable));
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_GIF)) {
		getContentCheckSetting()->enableCheck(IMAGE_TYPE_GIF, enabledFromString(enable));
	} else if (0 == _tcscmp(imagetype, CONFIG_NODE_IMAGETYPE_PNG)) {
		getContentCheckSetting()->enableCheck(IMAGE_TYPE_PNG, enabledFromString(enable));
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


//========================================
// public members
int XMLConfiguration::loadConfig(const TCHAR * filename) {
	readConfigFromFile(filename);
	return 0;
}
