#ifndef _SETTING_XMLCONFIGURATION_H__
#define _SETTING_XMLCONFIGURATION_H__

//class  XMLConfiguration
// ���ฺ�����������ļ�������������ļ�
// ����������

// 1. Ϊ�˷�ֹ�û��޸����ݣ� ����Ӧ�ö������м���
// 2. Ϊ�˷�ֹ�����ļ������쳣�� ���������ڳ���������һЩĬ��ֵ
// ������������ļ�ʧ�ܣ���ʹ��Ĭ��ֵ�����������رջ�����ֹʱ
// �ڽ����������ļ���д�������ͷ�ֹ�����ļ���۸���.
// 3. ���ܷ�ʽֱ��ʹ��zipѹ��һ�¾Ϳ����ˣ�����



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

	// Ĭ������
	void defaultSetting();
private:
	// ��ȡXML
	int readDefaultConfig();
	int readConfigFromFile(const TCHAR *filename);

	// ����XML
	int parseConfiguration(TiXmlElement * root);
	int parseRules(TiXmlNode *rules_root);
	int parseAppSet(TiXmlNode *appset_root);

private:
	int saveRules(TiXmlElement *root);
	
	// ����Ӧ�ó�������
	int saveAppSetting(TiXmlElement * root);
};

#endif  // _SETTING_XMLCONFIGURATION_H__