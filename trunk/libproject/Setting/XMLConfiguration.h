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
#include <screensaver.h>
#include <autoclean.h>
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
	ScreenSaver*	getScreenSave() { return &screen_save_;}
	AutoClean*		getScreenSaveAutoClean() { return getScreenSave()->getAutoClean();}
	AutoClean*		getWebHistoryRecordAutoClean() { return getWebHistoryRecordSetting()->getAutoclean();}
private:
	DNSList						black_url_set_;
	DNSList						white_url_set_;
	SearchRule					search_rule_;
	OnlineHourSetting			online_setting_;
	EyecareSetting				eye_care_;
	WebHistoryRecorderSetting	web_history_;
	Authorize					authorize_;
	ContentCheckSetting			content_check_;
	ScreenSaver					screen_save_;
	DNSSetting					dnssetting_;

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


	////////////////////////////////////////////////////////////////////
	// ����Ӧ�ó�������
	int getSystemSetting(TiXmlElement * ele);

	/////////////////////////////////////////////////////////////////////
	// ������������
	int getWhiteURL(TiXmlElement * ele);
	int getBlackURL(TiXmlElement * ele);
	int addWhiteURL(const TCHAR *URL);
	int enableWhiteURL(const TCHAR *enble);
	int enableJustPassWhite(const TCHAR *enabled);
	int addBlackURL(const TCHAR *URL);
	int enableBlackURL(const TCHAR *enble);
private:
	int saveRules(TiXmlElement *root);
	int saveBlackURL(TiXmlElement *rules_root);
	int saveWhiteURL(TiXmlElement *rules_root);

	int setTextCheck(const TCHAR *language, const TCHAR *enable);
	
	int saveTextRule();	// δ��
	int saveBlackWord(TiXmlElement *root);
	int saveSearchEngineRule(TiXmlElement *root);

	// ����Ӧ�ó�������
	int saveAppSetting(TiXmlElement * root);
};

#endif  // _SETTING_XMLCONFIGURATION_H__