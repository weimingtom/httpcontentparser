#ifndef _SELECTIO_DNSMAP_H__
#define _SELECTIO_DNSMAP_H__

#include <utility\syncutility.h>

// class DSNMap
// 此类用于管理SOCK与DNS之间的映射
#include <map>
#include <string>

class DNSMap {
public: 
	DNSMap(void);
	~DNSMap(void);

public:
	void add(SOCKET s, const std::string &addr);
	void remove(SOCKET s);
	std::string get(SOCKET s);
private:
	typedef std::map<SOCKET, std::string> SOCK_DNS_MAP;
	SOCK_DNS_MAP * socketsAddrs;

	// 临界区
	yanglei_utility::CAutoCreateCS cs_;
};

#endif  // _SELECTIO_DNSMAP_H__
