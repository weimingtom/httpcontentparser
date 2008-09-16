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

#define CONFIG_NODE_NAME			TEXT("name")
#define CONFIG_NODE_NAME_BLACKURL	TEXT("blackurl")
#define CONFIG_NODE_NAME_WHITEURL	TEXT("whiteurl")
#define CONFIG_NODE_NAME_ONLINETIME	TEXT("onlinetime")
#define CONFIG_NODE_NAME_SEARCH		TEXT("search")
#define CONFIG_NODE_NAME_IMAGECHECK	TEXT("imagecheck")
#define CONFIG_NODE_NAME_TEXT		TEXT("textrule")

#define CONFIG_NODE_ENABLE			TEXT("enable")
#define CONFIG_NODE_ENABLE_TRUE		TEXT("true")
#define CONFIG_NODE_ENABLE_FALSE	TEXT("false")

#define CONFIG_NODE_IMAGETYPE		TEXT("imagetype")
#define CONFIG_NODE_IMAGETYPE_BMP	TEXT("bmp")
#define CONFIG_NODE_IMAGETYPE_GIF	TEXT("gif")
#define CONFIG_NODE_IMAGETYPE_PNG	TEXT("png")
#define CONFIG_NODE_IMAGETYPE_JPG	TEXT("jpg")

#define CONFIG_NODE_SEARCH_ENGINE	TEXT("searchengine")
#define CONFIG_NODE_BLACK_SEARCHWORD TEXT("blackwords")

#define CONFIG_NODE_APPSET_AUTHORIZE	TEXT("authorize")
#define CONFIG_NODE_APPSET_EYECARE		TEXT("eyecare")
#define CONFIG_NODE_APPSET_WEBHISTORY	TEXT("webhistory")
#define CONFIG_NODE_APPSET_SYSSETTING	TEXT("syssetting")

#include <DNSSetting.h>
#include <SearchRule.h>
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
private:
	// ��ȡXML
	int readConfig();
	int readDefaultConfig();
	int readConfigFromFile(const char *filename);
	char * getConfigFilePath(char *buffer, const int bufsize);

	// ����XML
	int parseConfiguration(TiXmlElement * root);
	int parseRules(TiXmlNode *rules_root);
	int parseAppSet(TiXmlNode *appset_root);

	// ������������
	int getWhiteURL(TiXmlElement * ele);
	int getBlackURL(TiXmlElement * ele);
	int getOnlinetime(TiXmlElement * ele);
	int getSearchRule(TiXmlElement * ele);
	int getImageRule(TiXmlElement * ele);
	int getSearchBlackWord(TiXmlElement * ele);
	int getSearchEngineSetting(TiXmlElement * ele);

	int addWhiteURL(const char *URL);
	int enableWhiteURL(const char *enble);
	int addBlackURL(const char *URL);
	int enableBlackURL(const char *enble);
	int onlineBlocktime(const char *time);
	int setImageCheck(const char *imagetype, const char *enable);
	int setTextCheck(const char *language, const char *enable);
	int addSearchBlackWord(const char *word);
	int setSearchEngineCheck(const char *word);
	int addBlackSearchWord(const char *word);
	int setSearchEngineCheck(const char *search_engine, const char *enable);
	bool checkEnable(const char *enable) const;
public:
	// �޸Ĺ���ĺ���
private:
	bool changed_;	//  �Ƿ��й���ı�
private:
	// ������Ϣ
	// ע�� ���е�������Ϣ��Ӧ���ڹ��캯���г�ʼ��������
	// ��ʹ�޷���ȡ��������ϢҲ���Զ�ȡҲ�ܹ�ʹ��Ĭ�������������
};

#endif  // _SETTING_XMLCONFIGURATION_H__