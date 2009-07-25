// file : DNSSetting.h
// 这个文件包含三个类， 他们是DNSList, DNSCheck DNSSetting
// DNSList 负责保存DNS的列表
// DNSCheck 提供了黑白名单查询的支持
// DNSSetting 则使用Bridge的方式，对提供的DNS的check服务

#ifndef _SETTING_DNSSETTING_CHECKER_H__
#define _SETTING_DNSSETTING_CHECKER_H__

#include <set>
#include <map>
#include <string>
#include <Enumerate.h>
#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>

// 目前我们使用的机制有些适应性不高，我们需要增加cache机制。

class DNSList : public ConfigItem {
public:
	DNSList(const std::string & name);
	~DNSList(void);
private:
	DNSList(void);
public:
	bool checkDNS(const std::string &dns_name) const;
	bool fuzzeCheckDNS(const std::string &dns_name) const;

	// 添加删除DNS
	void addDNS(const std::string &dns_name);
	bool removeDNS(const std::string &dns_name);

	// enumerate
	void beginEnum(Enumerator1<std::string> *enumerator);

	// 获取DNS
	// 之所以采用这种方式，是因为map不能使用下表进行访问
	std::string  getFirstDNS();
	std::string getNextDNS(const std::string &name);
public:
	void enable(const bool check) {enabled_ = check;}
	bool isEnabled() const { return enabled_;}

	bool isSettingEnabled() const { return enabled_;}
protected:
	typedef std::map<std::string, std::string> DNS_SET;
	DNS_SET dns_set_;

	bool enabled_;

	// 读取XML配置
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * item_root);

private:
	TiXmlElement * saveURL(TiXmlElement *root);
	int getURLs(TiXmlElement * rule_root);
	int enableURLcheck(const TCHAR *isenable);
};

// class DNSSetting
// 负责对所有包进行检测是否应该通过
// 这个类在COM组件中是哟个
class DNSSetting  : public SettingItem,  public ConfigItem  {
public:
	DNSSetting();
	~DNSSetting(void);

private:
	enum {IN_BLACK_LIST = 0,
		IN_WHITE_LIST,
		NOT_SEPCIFIED
	};

	// 根据设置项来确定DNS是否合法
	bool dealResult(const int result);

public:
	bool initialize(DNSList *black_dns_list, DNSList *white_dns_list);

	// 对DNS的CHECK
	bool checkDNS(const std::string &dns);
	bool fuzzeCheckDNS(const std::string &dns);
	bool inWhiteList(const std::string &dns);

	// enable
	void justPassWhiteDNS(const bool checked);
	bool justPassWhiteDNS();
	void enableWhiteDNSCheck(const bool checked);
	void enableBlackDNSCheck(const bool checked);

	bool isWhiteDNSSettingEnable() const;
	bool isBlackDNSSettingEnable() const;
	// 添加
	bool addBlackDNS(const std::string &dns);
	bool addWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);

	// 获取DNS
	std::string getFirstWhiteDNS();
	std::string getNextWhiteDNS(const std::string &dns);
	std::string getFirstBlackDNS();
	std::string getNextBlackDNS(const std::string &dns);
private:
	int check(const std::string &dns);
	int fuzzeCheck(const std::string &dns);
	DNSList		* black_dns_list_;
	DNSList		* white_dns_list_;

	bool just_pass_white_dns_;
private:
	void defaultSetting();

public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * item_root);
};


#endif  // _SETTING_DNSSETTING_CHECKER_H__