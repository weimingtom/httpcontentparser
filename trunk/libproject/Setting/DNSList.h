#ifndef _SETTING_DNS_LIST_H__
#define _SETTING_DNS_LIST_H__

#include <set>
#include <string>

class DNSList {
public:
	DNSList(void);
	~DNSList(void);

public:
	bool isBlackDNS(const std::string &dns_name) const;
	bool isWhiteDNS(const std::string &dns_name) const;
	bool isBlackIP(const std::string &ip) const ;
	bool isWhiteIP(const std::string &ip) const ;

	// 添加删除DNS
	void addBlackDNS(const std::string &dns_name);
	void addWhiteDNS(const std::string &dns_name);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);
protected:
	typedef std::set<std::string> DNS_SET;
	DNS_SET black_set_;
	DNS_SET white_set_;


	//  保存对应DNS的IP
	DNS_SET black_ip_set_;
	DNS_SET white_ip_set_;

	// 工具函数
	void addIPS(const std::string &dns, DNS_SET *pSet);
	void removeIPS(const std::string &dns, DNS_SET *pSet);
};

#endif  // _SETTING_DNS_LIST_H__
