#ifndef _SETTING_DNS_CHECK_H__
#define _SETTING_DNS_CHECK_H__

#include <set>
#include <string>

class DNSList;

class DNSCheck {
public:
	DNSCheck(const DNSList *);
	~DNSCheck(void);

	bool checkIP(const std::string &ip);
	bool checkDNS(const std::string &dns_name);
	void enableDNSCheck(const bool checked);
protected:
	bool needCheck() const; // 是否需要检查DNS

	const DNSList * dns_list_;
	bool dns_check_;
	DNSCheck();
};



#endif  // _SETTING_DNS_CHECK_H__
