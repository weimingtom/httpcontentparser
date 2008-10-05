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
#include <settingitem.h>
// 目前我们使用的机制有些适应性不高，我们需要增加cache机制。

class DNSList : public SettingItem {
public:
	DNSList(void);
	~DNSList(void);

public:
	bool checkDNS(const std::string &dns_name) const;
	bool fuzzeCheckDNS(const std::string &dns_name) const;

	// 添加删除DNS
	void addDNS(const std::string &dns_name);
	bool removeDNS(const std::string &dns_name);

	// enumerate
	void beginEnum(Enumerator1<std::string> *enumerator);
protected:
	typedef std::set<std::string> DNS_SET;
	DNS_SET dns_set_;
};

// class DNSSetting
// 负责对所有包进行检测是否应该通过
// 这个类在COM组件中是哟个
class DNSSetting {
public:
	DNSSetting();
	~DNSSetting(void);

	enum {IN_BLACK_LIST = 0,
		IN_WHITE_LIST,
		NOT_SEPCIFIED
	};

public:
	bool initialize(DNSList *black_dns_list, DNSList *white_dns_list);

	// 对DNS的CHECK
	int checkDNS(const std::string &dns);
	int fuzzeCheckDNS(const std::string &dns);

	// enable
	void justPassWhiteDNS(const bool checked);
	bool justPassWhiteDNS() const;
	void enableWhiteDNSCheck(const bool checked);
	void enableBlackDNSCheck(const bool checked);

	// 添加
	bool addBlackDNS(const std::string &dns);
	bool addWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);
private:
	DNSList		* black_dns_list_;
	DNSList		* white_dns_list_;

	bool just_pass_white_dns_;

private:
	void defaultSetting();
};


#endif  // _SETTING_DNSSETTING_CHECKER_H__