#ifndef _DNSLOOKUP_DNS_H__
#define _DNSLOOKUP_DNS_H__

#include <string>
#include <vector>

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