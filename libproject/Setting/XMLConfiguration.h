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
	// 读取XML
	int readConfig();
	int readDefaultConfig();
	int readConfigFromFile(const char *filename);
	char * getConfigFilePath(char *buffer, const int bufsize);

	// 分析XML
	int parseConfiguration(TiXmlElement * root);
	int parseRules(TiXmlNode *rules_root);
	int parseAppSet(TiXmlNode *appset_root);

	// 分析各个规则
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
	// 修改规则的函数
private:
	bool changed_;	//  是否有规则改变
private:
	// 配置信息
	// 注： 所有的配置信息都应该在构造函数中初始化，这样
	// 即使无法读取到配置信息也可以读取也能够使用默认配置启动软件
};

#endif  // _SETTING_XMLCONFIGURATION_H__