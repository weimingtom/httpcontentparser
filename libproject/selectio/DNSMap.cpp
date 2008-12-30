#include "StdAfx.h"
#include ".\dnsmap.h"
#include <utility\dns.h>
#include <assert.h>

DNSMap::DNSMap(void)
{
	socketsAddrs = new SOCK_DNS_MAP();
}

DNSMap::~DNSMap(void)
{
	if (NULL != socketsAddrs) {
		delete socketsAddrs;
	}
}


void DNSMap::add(SOCKET s, const std::string &addr) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);
		socketsAddrs->insert(std::make_pair(s, addr));
	} catch (...) {
		OutputDebugString("excetpion");
	}
}
void DNSMap::remove(SOCKET s) {
	if (NULL == socketsAddrs)
		return;

	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DNS_MAP::iterator iter = socketsAddrs->find(s);
	if (socketsAddrs->end() != iter) {
		socketsAddrs->erase(iter);
	}
}
std::string DNSMap::get(SOCKET s) {
	if (NULL == socketsAddrs)
		return std::string("");

	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DNS_MAP::iterator iter = socketsAddrs->find(s);
	if (socketsAddrs->end() != iter) {
		return iter->second;
	} else {
		return std::string("");
	}
}