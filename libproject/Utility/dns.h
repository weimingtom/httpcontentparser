#ifndef _DNSLOOKUP_DNS_H__
#define _DNSLOOKUP_DNS_H__

#include <string>
#include <vector>

bool beginwidht_www(const TCHAR * fulldns);
// 获取DNS的主名
int get_main_dns_name(TCHAR * name, const int len, const TCHAR *fulldns);

// 例如 sports.sina.com/index.html.
// 他会返回 sina.com
// 如果是 www.sina.com.cn, 他会返回www.sina.com
char* get_main_serv_name(TCHAR * name, const int len, const TCHAR * fulldns);

// 检测DNS中是否包含IP地址
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
	size_t          getNumberOfHosts() const; 
	size_t          getNumberOfIP() const ;
	void			setHostname(const std::string & hostname) { hostName_ = hostname; }

protected:
	std::string      hostName_;
	std::vector<std::string> hostIps_;
	std::vector<std::string> dnsIps_;
};

#endif  // _DNSLOOKUP_DNS_H__