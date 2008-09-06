#include "StdAfx.h"
#include ".\DNSSetting.h"
#include <set>
#include <string>
#include <assert.h>
using namespace std;

DNSSetting::DNSSetting() {
	black_dns_list_ = NULL;
	white_dns_list_ = NULL;
	dns_check_  = NULL;
}

DNSSetting::~DNSSetting(void) {
}

// ��ʼ��
bool DNSSetting::initialize(DNSList *black_dns_list, DNSList *white_dns_list) {
	assert ( black_dns_list_ == NULL);
	assert ( white_dns_list_ == NULL);

	black_dns_list_ = black_dns_list;
	white_dns_list_ = white_dns_list;

	// Ϊ�˷�ֹ�ⲿ��
	assert ( dns_check_ == NULL);
	static DNSCheck dnschecker(black_dns_list_, white_dns_list_);
	dns_check_ = &dnschecker;
	return false;
}

int DNSSetting::fuzzeCheckDNS(const std::string &dns) {
	assert (dns_check_ != NULL);
	return dns_check_->fuzzeCheckDNS(dns);
}

// ���DNS
int DNSSetting::checkDNS(const std::string &dns){
	assert ( dns_check_ != NULL);
	return dns_check_->checkDNS(dns);
}

// ��DNS��� "����"��"������"
void DNSSetting::enableWhiteDNSCheck(const bool checked){
	assert ( dns_check_ != NULL);
	dns_check_->enableWhiteDNSCheck(checked);
}


void DNSSetting::enableBlackDNSCheck(const bool checked){
	assert ( dns_check_ != NULL);
	dns_check_->enableBlackDNSCheck(checked);
}

// DNSlist
// ���ɾ��DNS
bool DNSSetting::addBlackDNS(const std::string &dns){
	assert ( black_dns_list_ != NULL);
	if (checkDNS(dns) == DNSCheck::IN_WHITE_LIST) {
		return false;
	} else {
		black_dns_list_->addDNS(dns);
		return true;
	}
}

bool DNSSetting::addWhiteDNS(const std::string &dns){
	assert ( white_dns_list_ != NULL);

	if (checkDNS(dns) == DNSCheck::IN_BLACK_LIST) {
		return false;
	} else {
		white_dns_list_->addDNS(dns);
		return true;
	}
}

bool DNSSetting::removeBlackDNS(const std::string &dns_name) {
	assert ( black_dns_list_ != NULL);
	return black_dns_list_->removeDNS(dns_name); 
}
bool DNSSetting::removeWhiteDNS(const std::string &dns_name) {
	assert ( white_dns_list_ != NULL);
	return white_dns_list_->removeDNS(dns_name);
}


//=================================================================
// class DNSCheck
DNSCheck::DNSCheck(DNSList *black_dns_list, DNSList *white_dns_list)
	: black_dns_list_(black_dns_list), white_dns_list_(white_dns_list)  {
	assert(black_dns_list != NULL);
	assert(white_dns_list != NULL);
}
DNSCheck::DNSCheck(void) {
	assert(false);
}

DNSCheck::~DNSCheck(void) {
}

int DNSCheck::fuzzeCheckDNS(const std::string &dns_name) {
	assert(black_dns_list_ != NULL);
	assert(white_dns_list_ != NULL);

	if (true == white_dns_list_->fuzzeCheckDNS(dns_name)) {	// ����ڰ�������
		return IN_WHITE_LIST;
	} else if (true == black_dns_list_->fuzzeCheckDNS(dns_name)) {	// ����ں�������
		return IN_BLACK_LIST;
	} else {	// ������ں�������
		return NOT_SEPCIFIED;
	}
}

int DNSCheck::checkDNS(const std::string &dns_name) {
	assert(black_dns_list_ != NULL);
	assert(white_dns_list_ != NULL);

	if (true == white_dns_list_->checkDNS(dns_name)) {	// ����ڰ�������
		return IN_WHITE_LIST;
	} else if (true == black_dns_list_->checkDNS(dns_name)) {	// ����ں�������
		return IN_BLACK_LIST;
	} else {	// ������ں�������
		return NOT_SEPCIFIED;
	}
}

void DNSCheck::enableBlackDNSCheck(const bool checked) {
	black_dns_list_->enableCheck(checked);
}

void DNSCheck::enableWhiteDNSCheck(const bool checked) {
	white_dns_list_->enableCheck(checked);
}

//=================================================================
// class DNSCheck
DNSList::DNSList(void) {
		enable_check_ = true;
}

DNSList::~DNSList(void) {
}

//==================================
// ����DNS�Ƿ��ںڰ���������
bool DNSList::checkDNS(const std::string &dns_name) const {
	if ( false == needChecked())	// �������ڴ�������
		return false;

	if (dns_set_.end() != dns_set_.find(dns_name)) {
		return true;
	} else {
		return false;
	}
}

// �鿴dns_name�Ƿ���һ���ǰ�������
bool DNSList::fuzzeCheckDNS(const std::string &dns_name) const {
	DNS_SET::const_iterator iter = dns_set_.begin();
	for (; iter != dns_set_.end(); ++iter) {
		if (dns_name.find(*iter) != -1) {
			return true;
		}
	}

	return false;
}

//=====================================
// ��DNS���Ƴ�
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
