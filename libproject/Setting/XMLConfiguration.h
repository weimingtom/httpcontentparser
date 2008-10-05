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

#define CONFIG_ROOT_VALUE					TEXT("config")
#define CONFIG_NODE_RULES					TEXT("rules")
#define CONFIG_NODE_APPSET					TEXT("appsetting")


//======================================================
// һ����һЩ���õĳ���
#define CONFIG_CONST_NAME					TEXT("name")
#define CONFIG_CONST_TYPPE					TEXT("type")
#define CONFIG_CONST_ENABLE					TEXT("enable")
#define CONFIG_CONST_ENABLE_TRUE			TEXT("true")
#define CONFIG_CONST_ENABLE_FALSE			TEXT("false")
#define CONFIG_CONST_MIN					TEXT("min")
#define	CONFIG_CONST_MAX					TEXT("max")
#define CONSIG_CONST_TIMESPAN				TEXT("timespan")


#define CONFIG_NODE_RULE_ITEM				TEXT("rule")

#define CONFIG_NODE_NAME_BLACKURL			TEXT("blackurl")
#define CONFIG_NODE_NAME_WHITEURL			TEXT("whiteurl")
#define CONFIG_NODE_URL						TEXT("url")
#define CONFIG_NODE_NAME_SEARCH				TEXT("search")
#define CONFIG_NODE_NAME_IMAGECHECK			TEXT("imagecheck")
#define CONFIG_NODE_NAME_TEXT				TEXT("textrule")

#define CONFIG_NODE_NAME_ONLINETIME			TEXT("onlinetime")
#define CONFIG_NODE_NAME_BLACKTIME			TEXT("blocktime")
#define CONFIG_ONLINETIME_SEPERATE			TEXT("-")


#define CONFIG_NODE_IMAGE_CHECK_ITEM		TEXT("check")
#define CONFIG_NODE_IMAGETYPE				TEXT("imagetype")
#define CONFIG_NODE_IMAGETYPE_BMP			TEXT("bmp")
#define CONFIG_NODE_IMAGETYPE_GIF			TEXT("gif")
#define CONFIG_NODE_IMAGETYPE_PNG			TEXT("png")
#define CONFIG_NODE_IMAGETYPE_JPG			TEXT("jpg")

#define CONFIG_NODE_SEARCH_ENGINES			TEXT("searchengines")
#define CONDIG_NODE_SEARCH_ENGINE_ITEM		TEXT("searchengine")
#define CONFIG_NODE_BLACK_SEARCHWORD		TEXT("blackwords")
#define CONFIG_NODE_BLACK_WORDITER			TEXT("word")
//#define CONFIG_NODE_BLACK_ENINE

// Autorize
#define CONFIG_ITEM_APPSET_AUTHORIZE			TEXT("authorize")
#define CONFIG_APPSET_AUTHORIZE_USER			TEXT("user")
#define CONFIG_APPSET_AUTHORIZE_NAME			TEXT("username")
#define CONFIG_APPSET_AUTHORIZE_PASSWORD		TEXT("password")
#define CONFIG_APPSET_AUTHORIZE_USERTYPE_SU		TEXT("su")
#define CONFIG_APPSET_AUTHORIZE_USERTYPE_OTHER	TEXT("other")



#define CONFIG_ITEM_APPSET_SYSSETTING		TEXT("syssetting")

// Eyecare
#define CONFIG_ITEM_APPSET_EYECARE			TEXT("eyecare")
#define CONFIG_APPSET_EYECARE_TIME			TEXT("time")
#define CONFIG_APPSET_EYECARE_TIMESPAN		TEXT("timespan")
#define CONFIG_APPSET_EYECARE_EYECARE		TEXT("eyecare_time")
#define CONFIG_APPSET_EYECARE_ENTER			TEXT("enter_time")
#define CONFIG_APPSET_EYECARE_STATE			TEXT("state")
#define CONFIG_APPSET_EYECARE_TIMELEFT		TEXT("timeleft")
#define CONFIG_APPSET_EYECARE_TERM_MODE		TEXT("term_mode")

// WebHistory
#define CONFIG_ITEM_APPSET_WEBHISTORY			TEXT("webhistory")
#define CONFIG_APPSET_WEBHISTORY_CONTENT		TEXT("content")
#define CONFIG_APPSET_WEBHISTORY_ALL_IMAGE		TEXT("all_images")
#define CONFIG_APPSET_WEBHISTORY_PORN_IMAGE		TEXT("porn_images")
#define CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE	TEXT("all_website")
#define CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE	TEXT("porn_website")
#define CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE	TEXT("all_webpage")
#define CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE	TEXT("porn_webpage")

// screenSaver
#define CONFIG_ITEM_APPSET_SCREENSAVER			TEXT("screensave")
#define CONFIG_APPSET_SCREENSAVER_AUTOCLEAR		TEXT("autoclear")

#include <DNSSetting.h>
#include <SearchRule.h>
#include <onlinehoursetting.h>
#include <eyecaresetting.h>
#include <authorize.h>
#include <webhistoryrecordersetting.h>
#include <contentchecksetting.h>
#include <screensaver.h>
#include <autoclean.h>
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
	SearchRule *	getSearchRule() { return &search_rule_;}
	EyecareSetting* getEyecareSetting() { return &eye_care_;}
	OnlineHourSetting *getOnlineSetting() { return &online_setting_;}
	WebHistoryRecorderSetting * getWebHistoryRecordSetting() { return &web_history_;}
	Authorize *		getAuthorize() { return &authorize_;}
	ContentCheckSetting * getContentCheckSetting() { return &content_check_;}
	ScreenSaver		*getScreenSave() { return &screen_save_;}
	AutoClean		*getScreenSaveAutoClean() { return &screen_save_auto_clean_;}

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
	AutoClean					screen_save_auto_clean_;

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
	
	// Authorize
	int getAuthorizeSetting(TiXmlElement *ele);
	int addUser(const TCHAR *username, const TCHAR *password);

	// Eyecare
	int getEyecareSetting(TiXmlElement *ele);
	int setEyecareSetting(const TCHAR *type, const TCHAR *time);
	int enableEyecareSetting(const TCHAR *enable);
	int setEyecareState(const TCHAR *state, const TCHAR *value);
	int setEyecareTermMode(const TCHAR * value);

	// WebHistory
	int getWebHistoryRecorder(TiXmlElement *ele);
	int enableWebHistoryRecord(const TCHAR *enable);
	int setWebHistoryRecord(const TCHAR *type, const TCHAR *enable);

	// Screensaver
	int getScreensave(TiXmlElement * ele);
	int enableScreensave(const TCHAR *enable);
	int setScreensaveTimespan(const TCHAR *timespan);
	int setAutoClean(TiXmlElement * ele);
	int enableScreenSaveAutoClean(const TCHAR *enabled);
	int setScreensaveAutoCleanTimespan(const TCHAR *timespan);
	int setAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint);

	/////////////////////////////////////////////////////////////////////
	// ������������
	int getWhiteURL(TiXmlElement * ele);
	int getBlackURL(TiXmlElement * ele);
	int addWhiteURL(const TCHAR *URL);
	int enableWhiteURL(const TCHAR *enble);
	int addBlackURL(const TCHAR *URL);
	int enableBlackURL(const TCHAR *enble);

	// ��������
	int getOnlinetime(TiXmlElement * ele);
	int parseTime(const TCHAR *time);
	int onlineBlocktime(const TCHAR *time);

	// ��������
	int getSearchRule(TiXmlElement * ele);
	int setSearchEngineCheck(const TCHAR *word);
	int addBlackSearchWord(const TCHAR *word);
	int getSearchBlackWord(TiXmlElement * ele);
	int getSearchEngineSetting(TiXmlElement * ele);
	int setSearchEngineCheck(const TCHAR *search_engine, const TCHAR *enable);

	// �����������ľ���ϸ��
	int getImageRule(TiXmlElement * ele);
	int setImageCheck(const TCHAR *imagetype, const TCHAR *enable);
	int setTextCheck(const TCHAR *language, const TCHAR *enable);
private:
	int saveRules(TiXmlElement *root);
	int saveOnlineHour(TiXmlElement *rules_root);	// ����OnlineHour����
	int saveBlackURL(TiXmlElement *rules_root);
	int saveWhiteURL(TiXmlElement *rules_root);

	int saveImageRule(TiXmlElement *rules_root);
	
	int saveTextRule();	// δ��

	int saveSearchRule(TiXmlElement *rules_root);
	int saveBlackWord(TiXmlElement *root);
	int saveSearchEngineRule(TiXmlElement *root);

	// ����Ӧ�ó�������
	int saveAppSetting(TiXmlElement * root);
	int saveWebHistory(TiXmlElement * app_root);
	int saveEyecare(TiXmlElement *app_root);
	int saveAuthorize(TiXmlElement *app_root);

	// ����Screen Save
	int saveScreensave(TiXmlElement * root);
};

#endif  // _SETTING_XMLCONFIGURATION_H__