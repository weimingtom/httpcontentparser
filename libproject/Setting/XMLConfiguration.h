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

#define CONFIG_FILE_NAME			TEXT("config.xml")

#define CONFIG_ROOT_VALUE			TEXT("config")
#define CONFIG_NODE_RULES			TEXT("rules")
#define CONFIG_NODE_APPSET			TEXT("appsetting")

#define CONFIG_CONST_NAME			TEXT("name")
#define CONFIG_CONST_TYPPE			TEXT("type")
#define CONFIG_CONST_ENABLE			TEXT("enable")
#define CONFIG_CONST_ENABLE_TRUE	TEXT("true")
#define CONFIG_CONST_ENABLE_FALSE	TEXT("false")

#define CONFIG_NODE_NAME_BLACKURL	TEXT("blackurl")
#define CONFIG_NODE_NAME_WHITEURL	TEXT("whiteurl")
#define CONFIG_NODE_NAME_ONLINETIME	TEXT("onlinetime")
#define CONFIG_NODE_NAME_SEARCH		TEXT("search")
#define CONFIG_NODE_NAME_IMAGECHECK	TEXT("imagecheck")
#define CONFIG_NODE_NAME_TEXT		TEXT("textrule")


#define CONFIG_NODE_IMAGETYPE		TEXT("imagetype")
#define CONFIG_NODE_IMAGETYPE_BMP	TEXT("bmp")
#define CONFIG_NODE_IMAGETYPE_GIF	TEXT("gif")
#define CONFIG_NODE_IMAGETYPE_PNG	TEXT("png")
#define CONFIG_NODE_IMAGETYPE_JPG	TEXT("jpg")

#define CONFIG_NODE_SEARCH_ENGINE		TEXT("searchengine")
#define CONFIG_NODE_BLACK_SEARCHWORD	TEXT("blackwords")

// Autorize
#define CONFIG_ITEM_APPSET_AUTHORIZE		TEXT("authorize")
#define CONFIG_APPSET_AUTHORIZE_USER		TEXT("user")
#define CONFIG_APPSET_AUTHORIZE_NAME		TEXT("username")
#define CONFIG_APPSET_AUTHORIZE_PASSWORD	TEXT("password")
#define CONFIG_APPSET_AUTHORIZE_USERTYPE_SU	TEXT("su")


#define CONFIG_ITEM_APPSET_SYSSETTING	TEXT("syssetting")

// Eyecare
#define CONFIG_ITEM_APPSET_EYECARE		TEXT("eyecare")
#define CONFIG_APPSET_EYECARE_TIME		TEXT("time")
#define CONFIG_APPSET_EYECARE_TIMESPAN TEXT("timespan")
#define CONFIG_APPSET_EYECARE_REST		TEXT("rest")
#define CONFIG_APPSET_EYECARE_ENTER		TEXT("entertain")
#define CONFIG_APPSET_EYECARE_STATE		TEXT("state")
#define CONFIG_APPSET_EYECARE_TIMELEFT	TEXT("timeleft")

// WebHistory
#define CONFIG_ITEM_APPSET_WEBHISTORY			TEXT("webhistory")
#define CONFIG_APPSET_WEBHISTORY_CONTENT		TEXT("content")
#define CONFIG_APPSET_WEBHISTORY_ALL_IMAGE		TEXT("all_images")
#define CONFIG_APPSET_WEBHISTORY_PORN_IMAGE		TEXT("porn_images")
#define CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE	TEXT("all_website")
#define CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE	TEXT("porn_website")
#define CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE	TEXT("all_webpage")
#define CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE	TEXT("porn_webpage")

#include <DNSSetting.h>
#include <SearchRule.h>
#include <onlinehoursetting.h>
#include <eyecaresetting.h>
#include <authorize.h>
#include <webhistoryrecordersetting.h>
#include <string>
#include <set>
#include <map>

class TiXmlElement;
class TiXmlNode;

class XMLConfiguration {
public:
	XMLConfiguration(void);
	~XMLConfiguration(void);

	int initialize();
	int save();
public:
	DNSList black_url_set;
	DNSList white_url_set;
	SearchRule search_rule;
	OnlineHourSetting online_setting;
	EyecareSetting eye_care;
	WebHistoryRecorderSetting web_history;
	Authorize authorize;
private:
	// ��ȡXML
	int readConfig();
	int readDefaultConfig();
	int readConfigFromFile(const TCHAR *filename);
	TCHAR * getConfigFilePath(TCHAR *buffer, const int bufsize);

	// ����XML
	int parseConfiguration(TiXmlElement * root);
	int parseRules(TiXmlNode *rules_root);
	int parseAppSet(TiXmlNode *appset_root);

	// ����Ӧ�ó�������
	int getSystemSetting(TiXmlElement * ele);
	
	// Authorize
	int getAuthorizeSetting(TiXmlElement *ele);
	int addUser(const TCHAR *username, const TCHAR *password);

	// Eyecare
	int getEyecareSetting(TiXmlElement *ele);
	int setEyecareSetting(const TCHAR *type, const TCHAR *time);
	int enableEyecareSetting(const TCHAR *enable);
	int setEyecareState(const TCHAR *state, const TCHAR *timeleft);

	// WebHistory
	int getWebHistoryRecorder(TiXmlElement *ele);
	int enableWebHistoryRecord(const TCHAR *enable);
	int setWebHistoryRecord(const TCHAR *type, const TCHAR *enable);

	// ������������
	int getWhiteURL(TiXmlElement * ele);
	int getBlackURL(TiXmlElement * ele);
	int addWhiteURL(const TCHAR *URL);
	int enableWhiteURL(const TCHAR *enble);
	int addBlackURL(const TCHAR *URL);
	int enableBlackURL(const TCHAR *enble);

	// ��������
	int getOnlinetime(TiXmlElement * ele);
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

	
	bool checkEnable(const TCHAR *enable) const;
private:
	// �������ĺ���
};

#endif  // _SETTING_XMLCONFIGURATION_H__