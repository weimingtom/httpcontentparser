#include "StdAfx.h"
#include ".\dnslist.h"

#include <set>
#include <string>
using namespace std;

DNSList::DNSList(void) {
}

DNSList::~DNSList(void) {
}


bool DNSList::isBlackDNS(const std::string &dns_name) const {
	if (black_set_.end() != black_set_.find(dns_name))
		return true;
	else
		return false;
}
bool DNSList::isWhiteDNS(const std::string &dns_name) const {
	if (white_set_.end() != white_set_.find(dns_name))
		return true;
	else
		return false;
}

void DNSList::addBlackDNS(const std::string &dns_name) {
	black_set_.insert(dns_name);
}
void DNSList::addWhiteDNS(const std::string &dns_name) {
	white_set_.insert(dns_name);
}