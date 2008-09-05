#ifndef _SETTING_DNSSETTING_CHECKER_H__
#define _SETTING_DNSSETTING_CHECKER_H__

#include <set>
#include <map>
#include <string>


class DNSList {
public:
	DNSList(void);
	~DNSList(void);

public:
	bool checkDNS(const std::string &dns_name) const;

	// 添加删除DNS
	void addDNS(const std::string &dns_name);
	bool removeDNS(const std::string &dns_name);

	void enableCheck(const bool checked) { enable_check_ = checked;}
protected:
	bool needChecked() const { return enable_check_ ;}
	typedef std::set<std::string> DNS_SET;
	DNS_SET dns_set_;
	bool enable_check_;
};

// 检测
class DNSCheck {
public:
	DNSCheck(DNSList *black_dns_list, DNSList *white_dns_list);
	~DNSCheck(void);

	enum {IN_BLACK_LIST = 0,
		IN_WHITE_LIST,
		NOT_SEPCIFIED
	};

	int checkDNS(const std::string &dns_name);
	void enableBlackDNSCheck(const bool checked);
	void enableWhiteDNSCheck(const bool checked);
protected:

	DNSList * black_dns_list_;
	DNSList * white_dns_list_;
	DNSCheck();
};

// class DNSSetting
// 负责对所有包进行检测是否应该通过
// 这个类在COM组件中是哟个
class DNSSetting {
public:
	DNSSetting();
	~DNSSetting(void);

public:
	bool initialize(DNSList *black_dns_list, DNSList *white_dns_list);

	// 对DNS的CHECK
	int checkDNS(const std::string &dns);

	void enableWhiteDNSCheck(const bool checked);
	void enableBlackDNSCheck(const bool checked);

	bool addBlackDNS(const std::string &dns);
	bool addWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);

private:
	DNSCheck	* dns_check_;
	DNSList		* black_dns_list_;
	DNSList		* white_dns_list_;
};


#endif  // _SETTING_DNSSETTING_CHECKER_H__