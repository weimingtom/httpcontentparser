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

	void addBlackDNS(const std::string &dns_name);
	void addWhiteDNS(const std::string &dns_name);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);
protected:
	typedef std::set<std::string> DNS_SET;
	DNS_SET black_set_;
	DNS_SET white_set_;
};

#endif  // _SETTING_DNS_LIST_H__
