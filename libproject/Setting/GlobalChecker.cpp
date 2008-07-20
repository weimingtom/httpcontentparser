#include "StdAfx.h"
#include ".\globalchecker.h"
#include ".\dnscheck.h"
#include ".\dnslist.h"
#include ".\imagecheck.h"

#include <assert.h>

GlobalChecker::GlobalChecker(void) {
	dns_check_ = NULL;
	dns_list_ = NULL;
}

GlobalChecker::~GlobalChecker(void) {
}

// 初始化
bool GlobalChecker::initialize() {
	assert ( dns_list_ == NULL);
	static DNSList dnslist;
	dns_list_ = &dnslist;

	// 为了防止外部类
	assert ( dns_check_ == NULL);
	static DNSCheck dnschecker(dns_list_);
	dns_check_ = &dnschecker;

	assert ( image_check_ == NULL);
	static ImageCheck imagechecker(dns_list_);
	image_check_ = &imagechecker;

	return false;
}

// 全局的管理
void GlobalChecker::enableApplications(const bool enabled) {
	global_enable_ = enabled;
}


// 检测DNS
bool GlobalChecker::checkDNS(const std::string &dns){
	assert ( dns_check_ != NULL);
	return dns_check_->checkDNS(dns);
}
void GlobalChecker::enableDNSCheck(const bool checked){
	assert ( dns_check_ != NULL);
}

// DNSlist
void GlobalChecker::addBlackDNS(const std::string &dns){
	assert ( dns_list_ != NULL);
	dns_list_->addBlackDNS(dns);
}
void GlobalChecker::adllWhiteDNS(const std::string &dns){
	assert ( dns_list_ != NULL);
	dns_list_->addWhiteDNS(dns);
}
