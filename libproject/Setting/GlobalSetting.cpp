#include "StdAfx.h"
#include ".\globalsetting.h"
#include ".\dnscheck.h"
#include ".\dnslist.h"
#include ".\imagesetting.h"

#include <assert.h>

GlobalSetting::GlobalSetting(void) {
	dns_check_ = NULL;
	dns_list_ = NULL;
	image_check_ = NULL;
}

GlobalSetting::~GlobalSetting(void) {
}

// 初始化
bool GlobalSetting::initialize() {
	assert ( dns_list_ == NULL);
	static DNSList dnslist;
	dns_list_ = &dnslist;

	// 为了防止外部类
	assert ( dns_check_ == NULL);
	static DNSCheck dnschecker(dns_list_);
	dns_check_ = &dnschecker;

	assert ( image_check_ == NULL);
	static ImageSetting imagechecker(dns_list_);
	image_check_ = &imagechecker;

	return false;
}

// 检测DNS
bool GlobalSetting::checkDNS(const std::string &dns){
	assert ( dns_check_ != NULL);
	return dns_check_->checkDNS(dns);
}
bool GlobalSetting::checkIP(const std::string &ip){
	assert ( dns_check_ != NULL);
	return dns_check_->checkIP(ip);
}

// 是DNS检测 "可用"或"不可用"
void GlobalSetting::enableDNSCheck(const bool checked){
	assert ( dns_check_ != NULL);
	dns_check_->enableDNSCheck(checked);
}

// DNSlist
// 添加删除DNS
void GlobalSetting::addBlackDNS(const std::string &dns){
	assert ( dns_list_ != NULL);
	dns_list_->addBlackDNS(dns);
}
void GlobalSetting::adllWhiteDNS(const std::string &dns){
	assert ( dns_list_ != NULL);
	dns_list_->addWhiteDNS(dns);
}

bool GlobalSetting::removeBlackDNS(const std::string &dns_name) {
	assert ( dns_list_ != NULL);
	return dns_list_->removeBlackDNS(dns_name); 
}
bool GlobalSetting::removeWhiteDNS(const std::string &dns_name) {
	assert ( dns_list_ != NULL);
	return dns_list_->removeWhiteDNS(dns_name);
}

// CHECK IMAGE
void GlobalSetting::enableImageCheck(const int type, const bool check) {
	assert ( image_check_ != NULL);
	image_check_->enableCheck(type, check);
}
bool GlobalSetting::imageNeedCheck(const int type) const {
	assert ( image_check_ != NULL);
	return image_check_->needCheck(type);
}
void GlobalSetting::enableShowImage(const bool show) {
	assert ( image_check_ != NULL);
	image_check_->enableShowImage(show);
}
bool GlobalSetting::showImage() const {
	assert ( image_check_ != NULL);
	return image_check_->showImage();
}