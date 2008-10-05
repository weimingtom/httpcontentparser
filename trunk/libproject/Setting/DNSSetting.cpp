#include "StdAfx.h"
#include ".\DNSSetting.h"
#include <set>
#include <string>
#include <assert.h>
using namespace std;



DNSSetting::DNSSetting() {
	defaultSetting();
}

DNSSetting::~DNSSetting(void) {
}


void DNSSetting::defaultSetting() {
	black_dns_list_ = NULL;
	white_dns_list_ = NULL;
	just_pass_white_dns_ = false;

	SettingItem::defaultSetting();
}
// 初始化
bool DNSSetting::initialize(DNSList *black_dns_list, DNSList *white_dns_list) {
	assert ( black_dns_list_ == NULL);
	assert ( white_dns_list_ == NULL);

	black_dns_list_ = black_dns_list;
	white_dns_list_ = white_dns_list;

	return false;
}


// 仅仅允许通过WHITE DNS
void DNSSetting::justPassWhiteDNS(const bool checked) {
	just_pass_white_dns_ = checked;

	if (true == checked)
		enableWhiteDNSCheck(true);
}

bool DNSSetting::justPassWhiteDNS() {
	assert (white_dns_list_ != NULL);
	if (false == white_dns_list_->isEnabled())
		just_pass_white_dns_ = false;

	return just_pass_white_dns_;
}
// DNSlist
// 添加删除DNS
bool DNSSetting::addBlackDNS(const std::string &dns){
	assert ( black_dns_list_ != NULL);
	if (check(dns) == IN_WHITE_LIST) {
		return false;
	} else {
		black_dns_list_->addDNS(dns);
		return true;
	}
}

bool DNSSetting::addWhiteDNS(const std::string &dns){
	assert ( white_dns_list_ != NULL);

	if (check(dns) == IN_BLACK_LIST) {
		return false;
	} else {
		white_dns_list_->addDNS(dns);
		return true;
	}
}

// 移除
bool DNSSetting::removeBlackDNS(const std::string &dns_name) {
	assert ( black_dns_list_ != NULL);
	return black_dns_list_->removeDNS(dns_name); 
}

bool DNSSetting::removeWhiteDNS(const std::string &dns_name) {
	assert ( white_dns_list_ != NULL);
	return white_dns_list_->removeDNS(dns_name);
}

int DNSSetting::check(const std::string &dns) {
	if (true == white_dns_list_->checkDNS(dns)) {	// 如果在白名单中
		return (IN_WHITE_LIST);
	} else if (true == black_dns_list_->checkDNS(dns)) {	// 如果在黑名单中
		return (IN_BLACK_LIST);
	} else {	// 如果不在黑名单中
		return (NOT_SEPCIFIED);
	}
}

int DNSSetting::fuzzeCheck(const std::string &dns) {
	if (true == white_dns_list_->fuzzeCheckDNS(dns)) {	// 如果在白名单中
		return (IN_WHITE_LIST);
	} else if (true == black_dns_list_->fuzzeCheckDNS(dns)) {	// 如果在黑名单中
		return (IN_BLACK_LIST);
	} else {	// 如果不在黑名单中
		return (NOT_SEPCIFIED);
	}
}

bool DNSSetting::fuzzeCheckDNS(const std::string &dns_name) {
	assert(black_dns_list_ != NULL);
	assert(white_dns_list_ != NULL);

	// 如果是不可用直接返回false, 这里主要为了应对SettingItem::PARENT_MODE
	if (isEnabled() == false) {
		return true;
	}

	int result = fuzzeCheck(dns_name);
	return dealResult(result);
}

bool DNSSetting::checkDNS(const std::string &dns_name) {
	assert(black_dns_list_ != NULL);
	assert(white_dns_list_ != NULL);

	// 如果是不可用直接返回false, 这里主要为了应对SettingItem::PARENT_MODE
	if (isEnabled() == false) {
		return true;
	}

	int result = check(dns_name);
	return dealResult(result);
}

bool DNSSetting::dealResult(const int result) {
	if (justPassWhiteDNS()) {
		// 如果仅仅通过白名单
		if (result == IN_WHITE_LIST) 
			return true;
		else
			return false;
	} else {
		// 如果只检测黑名单
		if (result == IN_BLACK_LIST) 
			return false;
		else
			return true;
	}
}

void DNSSetting::enableBlackDNSCheck(const bool checked) {
	black_dns_list_->enable(checked);
}

void DNSSetting::enableWhiteDNSCheck(const bool checked) {
	white_dns_list_->enable(checked);
}

//=================================================================
// class DNSCheck
DNSList::DNSList(void) {
	enabled_ = true;
}

DNSList::~DNSList(void) {
}

//==================================
// 测试DNS是否在黑白名单当中
bool DNSList::checkDNS(const std::string &dns_name) const {
	if ( false == isEnabled())	
		return false;

	// 表明不在此名单内
	if (dns_set_.end() != dns_set_.find(dns_name)) {
		return true;
	} else {
		return false;
	}
}

// 查看dns_name是否有一个是包含它的
bool DNSList::fuzzeCheckDNS(const std::string &dns_name) const {
	if (isEnabled() == false) {
		return false;
	}

	DNS_SET::const_iterator iter = dns_set_.begin();
	for (; iter != dns_set_.end(); ++iter) {
		if (dns_name.find(*iter) != -1) {
			return true;
		}
	}

	return false;
}

//=====================================
// 从DNS中移除
bool DNSList::removeDNS(const std::string &dns_name) {
	DNS_SET::iterator iter = dns_set_.find(dns_name);
	if (dns_set_.end() != iter) {
		dns_set_.erase(iter);
		return true;
	}
	return false;
}

void DNSList::addDNS(const std::string &dns_name) {
	dns_set_.insert(dns_name);
}


void DNSList::beginEnum(Enumerator1<std::string> *enumerator) {
	assert (NULL != enumerator);

	DNS_SET::const_iterator iter = dns_set_.begin();
	for (; iter != dns_set_.end(); ++iter) {
		enumerator->Enum(*iter);
	}
}
