#ifndef _DNSLOOKUP_DNS_H__
#define _DNSLOOKUP_DNS_H__

#include <string>
#include <vector>

bool beginwidht_www(const TCHAR * fulldns);
// ��ȡDNS������
INT_PTR get_main_dns_name(TCHAR * name, const INT_PTR len, const TCHAR *fulldns);

// ���� sports.sina.com/index.html.
// ���᷵�� sina.com
// ����� www.sina.com.cn, ���᷵��www.sina.com
char* get_main_serv_name(TCHAR * name, const INT_PTR len, const TCHAR * fulldns);

// ���DNS���Ƿ����IP��ַ
bool isContainsIP(TCHAR * dns);

bool validateStringIP(TCHAR * dns);
bool validateStringIP(TCHAR * dns,  char ** e);

/////////////////////////////////////////////////////////////////////////////
// CDNS definitions
class CDNS {
public:
	CDNS(); 
	const std::string     &getHostname() { return hostName_; }
	bool			doDNSLookup();
	std::string     getIPAt(const size_t index);
	std::string     getHostAt(const size_t index);
	INT_PTR          getNumberOfHosts() const; 
	INT_PTR          getNumberOfIP() const ;
	void			setHostname(const std::string & hostname) { hostName_ = hostname; }

protected:
	std::string      hostName_;
	std::vector<std::string> hostIps_;
	std::vector<std::string> dnsIps_;
};

#endif  // _DNSLOOKUP_DNS_H__