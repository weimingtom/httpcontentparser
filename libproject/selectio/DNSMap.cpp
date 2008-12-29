#include "StdAfx.h"
#include ".\dnsmap.h"

DNSMap::DNSMap(void)
{
}

DNSMap::~DNSMap(void)
{
}


void DNSMap::add(SOCKET s, const std::string &addr) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// ªÒ»°DNS Domain
	char main_dns[128];
	get_main_dns_name(main_dns, 128, addr.c_str());

	socketsAddrs.insert(std::make_pair(s, main_dns));
}
void DNSMap::remove(SOCKET s) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DNS_MAP::iterator iter = socketsAddrs.find(s);
	if (socketsAddrs.end() != iter) {
		socketsAddrs.erase(iter);
	}
}
std::string DNSMap::get(SOCKET s) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DNS_MAP::iterator iter = socketsAddrs.find(s);
	if (socketsAddrs.end() != iter) {
		return iter->second;
	} else {
		return std::string("");
	}
}