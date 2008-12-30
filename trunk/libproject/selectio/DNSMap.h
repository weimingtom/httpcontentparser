#ifndef _SELECTIO_DNSMAP_H__
#define _SELECTIO_DNSMAP_H__

#include <utility\syncutility.h>

// class DSNMap
// �������ڹ���SOCK��DNS֮���ӳ��
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

	// �ٽ���
	yanglei_utility::CAutoCreateCS cs_;
};

#endif  // _SELECTIO_DNSMAP_H__
