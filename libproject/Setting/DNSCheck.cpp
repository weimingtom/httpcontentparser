#include "StdAfx.h"
#include ".\dnscheck.h"
#include ".\dnslist.h"
#include <assert.h>


DNSCheck::DNSCheck(const DNSList *dns_list) : dns_list_(dns_list) {
	assert(dns_list != NULL);
}
DNSCheck::DNSCheck(void) {
	assert(false);
}

DNSCheck::~DNSCheck(void) {
}

bool DNSCheck::checkIP(const std::string &ip) {
	if (needCheck() == true && dns_list_->isBlackIP(ip))
		return false;
	else
		return true;
}

bool DNSCheck::checkDNS(const std::string &ip) {
	if (needCheck() == true && dns_list_->isBlackDNS(ip))
		return false;
	else
		return true;
}
void DNSCheck::enableDNSCheck(const bool checked) {
	dns_check_ = checked;
}

bool DNSCheck::needCheck() const {
	return dns_check_;
}