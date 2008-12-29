#include "StdAfx.h"
#include ".\globaldata.h"
#include ".\dns\dns.h"
#include <assert.h>

#include <string>

#pragma data_seg(".share")
	// 记录规则更改的时刻，如果为0表示尚未载入规则
	int		g_share_nModifyCount		= 0;

	// 记录载入COM的进程数，当为0时。
	LONG	g_share_nProcessCount		= 0;
#pragma data_seg()

// 使用uudi表示
const std::string g_filemapping_name  = "F6488313-A700-4312-8561-32CB297F9891";
const std::string g_mutex_filemapping = "EFD8D100-B5BA-49f1-9863-D3032580B310";
const std::string g_mutex_globaldata  = "E80A95EA-8505-40b7-A187-DFD110B186EC";

//============================================
// class CGlobalData;
extern CGlobalData g_globalData;
CGlobalData::CGlobalData(void) {
	setting_changed_ = false;
}

CGlobalData::~CGlobalData(void) {
}

void CGlobalData::loadSetting() {
	CComCritSecLock<CComAutoCriticalSection> lock(cs_);

	appSetting_.loadSetting();
}

void CGlobalData::storeSetting() {
	CComCritSecLock<CComAutoCriticalSection> lock(cs_);

	if (setting_changed_ == true) {
		appSetting_.storeSetting();
	}
}

void CGlobalData::setIPCheck(const bool checked) {
	appSetting_.enableIpCheck(checked);
}

bool CGlobalData::checkIP(const unsigned int ipaddress) {
	CComCritSecLock<CComAutoCriticalSection> lock(cs_);
	
	if (appSetting_.shouldCheckIp()) {
		return checkSetting_.checkIP(ipaddress);
	} else {
		return false;
	}
}

// 增加DNS
void CGlobalData::addDns(const _bstr_t &t) {
	CComCritSecLock<CComAutoCriticalSection> lock(cs_);

	setting_changed_ = true;
	checkSetting_.addDns(t);
}

void CGlobalData::removeDns(const _bstr_t &t) {
	CComCritSecLock<CComAutoCriticalSection> lock(cs_);

	setting_changed_ = true;
	checkSetting_.removeDns(t);
}

//===========================
// class AppSetting;
CGlobalData::AppSetting::AppSetting() {
	bIpCheck_ = true;
}

void CGlobalData::AppSetting::loadSetting() {
}
void CGlobalData::AppSetting::storeSetting() {
}
void CGlobalData::AppSetting::enableIpCheck(bool enable) {
	bIpCheck_ = enable;
}
bool CGlobalData::AppSetting::shouldCheckIp() const {
	return bIpCheck_;
}

//=============================
// class CheckSetting
CGlobalData::CheckSetting::CheckSetting() {
}
CGlobalData::CheckSetting::~CheckSetting() {
}

// 从文件中载入规则
void CGlobalData::CheckSetting::loadRulesFromFile() {
}

// 从共享内存中获取规则
void CGlobalData::CheckSetting::loadRulesFromShareMemory() {
}

// 载入规则
void CGlobalData::CheckSetting::loadSetting() {
	// 尚未载入规则
	// 检测是否需要从新载入规则
	if ( rulesInitialize() == false) {
		// 规则尚未从文件中载入
		loadRulesFromFile();
		seGlobaltModifyFlags();
	} else if (rulesModified() == true) {
		loadRulesFromShareMemory();
		// 规则被更改
		setSelfModifyFlags();
	} else {
		// 没有规则变更，直接返回
		;
	}
}

// 规则是否改变
bool  CGlobalData::CheckSetting::rulesModified() {
	if (g_share_nModifyCount == changed_ticket_) 
		return false;
	else 
		return true;
}

// 规则是否已经初始化
bool  CGlobalData::CheckSetting::rulesInitialize() {
	if (g_share_nModifyCount == 0)
		return false;
	else 
		return true;
}

// 通知所有COM库，规则已经被改变
DWORD CGlobalData::CheckSetting::seGlobaltModifyFlags() {
	g_share_nModifyCount = GetTickCount();
	setSelfModifyFlags();
	return g_share_nModifyCount;
}

// 设置自身的规则版本与当前最新规则同步
DWORD CGlobalData::CheckSetting::setSelfModifyFlags() {
	changed_ticket_ = g_share_nModifyCount;
	return changed_ticket_;
}

// 保存规则
void CGlobalData::CheckSetting::storeSetting() {
}

// 检测IP是否应该被删除
bool CGlobalData::CheckSetting::checkIP(const char * ipaddress) {
	return checkIP(inet_addr(ipaddress));
}
bool CGlobalData::CheckSetting::checkIP(const unsigned int ipaddress) {
	loadSetting();
	if (ips_.find(ipaddress) != ips_.end()) {
		return true;
	} else {
		return false;
	}
}

// 增加dns
void CGlobalData::CheckSetting::addDns(const _bstr_t &t) {
	CDNS dns;
	dns.setHostname((char*)t);
	dns.doDNSLookup();
	dnss_.insert(t);

	for (size_t i = 0; i < dns.getNumberOfIP(); ++i) {
		unsigned int ip = inet_addr(dns.getIPAt(i).c_str());
		ips_.insert(ip);
	}

	seGlobaltModifyFlags();
}
// 删除一个被过滤的dns
void CGlobalData::CheckSetting::removeDns(const _bstr_t &t) {
	CDNS dns;
	dns.setHostname((char*)t);
	dns.doDNSLookup();
	dnss_.insert(t);

	for (size_t i = 0; i < dns.getNumberOfIP(); ++i) {
		unsigned int ip = inet_addr(dns.getIPAt(i).c_str());
		IP_SET::iterator iter = ips_.find(ip);
		if (iter != ips_.end()) {
			ips_.erase(iter); 
		} else {
			assert(false);
		}
	}

	seGlobaltModifyFlags();
}