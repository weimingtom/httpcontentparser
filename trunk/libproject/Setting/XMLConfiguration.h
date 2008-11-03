#ifndef _SETTING_XMLCONFIGURATION_H__
#define _SETTING_XMLCONFIGURATION_H__

//class  XMLConfiguration
// 此类负责，载入配置文件，如果打开配置文件
// 则重置设置

// 1. 为了防止用户修改数据， 我们应该对他进行加密
// 2. 为了防止配置文件发生异常， 我们首先在程序中设置一些默认值
// 如果载入配置文件失败，则使用默认值替代，当程序关闭或者终止时
// 在将整个配置文件重写，这样就防止配置文件陪篡改了.
// 3. 加密方式直接使用zip压缩一下就可以了，哈哈



// ______________________________________________________
// |                       |                            |
// |   COM Object          |     Application            |
// |_______________________|____________________________|
// |                                                    |
// |                 Setting library                    |
// |____________________________________________________|
// |                                                    |
// |                 XMLConfiguration                   |
// |____________________________________________________|



#include <DNSSetting.h>
#include <SearchRule.h>
#include <onlinehoursetting.h>
#include <eyecaresetting.h>
#include <authorize.h>
#include <webhistoryrecordersetting.h>
#include <contentchecksetting.h>
#include <Screenshot.h>
#include <autoclean.h>
#include <hotkeysetting.h>
#include <xmldefined.h>
#include <string>
#include <set>
#include <map>

class TiXmlElement;
class TiXmlNode;

class XMLConfiguration {
public:
	XMLConfiguration();
	~XMLConfiguration(void);

public:
	int loadConfig(const TCHAR * filename);
	int saveConfig(const TCHAR * filename);
public:
	DNSList *		getBlackURLSet() { return &black_url_set_;}
	DNSList *		getWhiteURLSet() { return &white_url_set_;}
	DNSSetting*		getDNSSetting() { return &dnssetting_;}
	SearchRule *	getSearchRule() { return &search_rule_;}
	EyecareSetting* getEyecareSetting() { return &eye_care_;}
	OnlineHourSetting* getOnlineSetting() { return &online_setting_;}
	WebHistoryRecorderSetting* getWebHistoryRecordSetting() { return &web_history_;}
	Authorize*		getAuthorize() { return &authorize_;}
	ContentCheckSetting* getContentCheckSetting() { return &content_check_;}
	Screenshot*	getScreenshotSetting() { return &screen_save_;}
	AutoClean*		getScreenshotAutoClean() { return getScreenshotSetting()->getAutoClean();}
	AutoClean*		getWebHistoryRecordAutoClean() { return getWebHistoryRecordSetting()->getAutoclean();}
	HotkeySetting*   getHotkey() { return &hotkey_;}
private:
	DNSList						black_url_set_;
	DNSList						white_url_set_;
	SearchRule					search_rule_;
	OnlineHourSetting			online_setting_;
	EyecareSetting				eye_care_;
	WebHistoryRecorderSetting	web_history_;
	Authorize					authorize_;
	ContentCheckSetting			content_check_;
	Screenshot					screen_save_;
	DNSSetting					dnssetting_;
	HotkeySetting				hotkey_;

	// 默认设置
	void defaultSetting();
private:
	// 读取XML
	int readDefaultConfig();
	int readConfigFromFile(const TCHAR *filename);

	// 分析XML
	int parseConfiguration(TiXmlElement * root);
	int parseRules(TiXmlNode *rules_root);
	int parseAppSet(TiXmlNode *appset_root);

private:
	int saveRules(TiXmlElement *root);
	
	// 保存应用程序设置
	int saveAppSetting(TiXmlElement * root);
};

#endif  // _SETTING_XMLCONFIGURATION_H__