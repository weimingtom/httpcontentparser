#ifndef _SELECT_IO_DOMAINADDRESS_H__
#define _SELECT_IO_DOMAINADDRESS_H__

#include <map>
#include <string>

// class DomainAddress
// 此类负责保存对应的socket的host name
// 
class DomainAddress {
public:
	DomainAddress(void);
	~DomainAddress(void);

	void update(const SOCKET s, const std::string &host_name) {
		host_name_map_[s] = host_name;
	}

	std::string getHostname(const SOCKET s) {
		MAP_SOCK_HOSTNAME::const_iterator iter = host_name_map_.find(s);
		if (iter != host_name_map_.end()) {
			return iter->second;
		} else {
			return std::string("");
		}
	}

private:
	typedef std::map<SOCKET, std::string> MAP_SOCK_HOSTNAME;
	MAP_SOCK_HOSTNAME host_name_map_;
};

#endif  // _SELECT_IO_DOMAINADDRESS_H__
