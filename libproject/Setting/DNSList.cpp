#include "StdAfx.h"
#include ".\dnslist.h"

#include <set>
#include <string>
#include <utility/DNS.H>
using namespace std;

DNSList::DNSList(void) {
}

DNSList::~DNSList(void) {
}

//====================================
// 测试ip是否在。当中
bool DNSList::isBlackIP(const std::string &ip) const {
	if (black_ip_set_.end() != black_ip_set_.find(ip))
		return true;
	else
		return false;
}

bool DNSList::isWhiteIP(const std::string &ip) const {
	if (white_ip_set_.end() != white_ip_set_.find(ip))
		return true;
	else
		return false;
}

//==================================
// 测试DNS是否在黑白名单当中
bool DNSList::isBlackDNS(const std::string &dns_name) const {
	if (black_set_.end() != black_set_.find(dns_name)) {
		return true;
	} else {
		return false;
	}
}

bool DNSList::isWhiteDNS(const std::string &dns_name) const {
	if (white_set_.end() != white_set_.find(dns_name)) {
		return true;
	} else {
		return false;
	}
}

//=====================================
// 从DNS中移除
bool DNSList::removeBlackDNS(const std::string &dns_name) {
	DNS_SET::iterator iter = black_set_.find(dns_name);
	if (black_set_.end() != iter) {
		// remove IP
		removeIPS(dns_name, &black_ip_set_);

		black_set_.erase(iter);
		return true;
	}
	return false;
}
bool DNSList::removeWhiteDNS(const std::string &dns_name) {
	DNS_SET::iterator iter = white_set_.find(dns_name);
	if (white_set_.end() != iter) {
		// remove IP
		removeIPS(dns_name, &white_ip_set_);

		// REMOVE DNS
		white_set_.erase(iter);
		return true;
	}
	return false;
}

void DNSList::addBlackDNS(const std::string &dns_name) {
	black_set_.insert(dns_name);
	addIPS(dns_name, &black_ip_set_);	
}
void DNSList::addWhiteDNS(const std::string &dns_name) {
	white_set_.insert(dns_name);
	addIPS(dns_name, &white_ip_set_);
}

void DNSList::addIPS(const std::string &dns_name, DNS_SET *pSet) {
	CDNS dns;
	dns.setHostname(dns_name);
	dns.doDNSLookup();

	for (int i = 0; i < dns.getNumberOfIP(); ++i) {
		pSet->insert(dns.getIPAt(i));
	}
}

void DNSList::removeIPS(const std::string &dns_name, DNS_SET *pSet) {
	CDNS dns;
	dns.setHostname(dns_name);
	dns.doDNSLookup();

	DNS_SET::iterator iter;
	for (int i = 0; i < dns.getNumberOfIP(); ++i) {
		iter = pSet->find(dns.getIPAt(i));
		if (iter != pSet->end()) {
			pSet->erase(iter);
		}
	}
}