#include "StdAfx.h"
#include ".\globaldata.h"
#include <utility\dns.h>

#include <string>

#pragma data_seg(".share")
	// ��¼������ĵ�ʱ�̣����Ϊ0��ʾ��δ�������
	int		g_share_nModifyCount		= 0;

	// ��¼����COM�Ľ���������Ϊ0ʱ��
	LONG	g_share_nProcessCount		= 0;
#pragma data_seg()

// ʹ��uudi��ʾ
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

// ����DNS
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

// �������
void CGlobalData::CheckSetting::storeSetting() {
}

// ���IP�Ƿ�Ӧ�ñ�ɾ��
bool CGlobalData::CheckSetting::checkIP(const char * ipaddress) {
	return checkIP(inet_addr(ipaddress));
}
bool CGlobalData::CheckSetting::checkIP(const unsigned int ipaddress) {
	if (ips_.find(ipaddress) != ips_.end()) {
		return true;
	} else {
		return false;
	}
}
 
// ����dns
void CGlobalData::CheckSetting::addDns(const _bstr_t &t) {
	OutputDebugString("Add DNS Address");
	OutputDebugString(t);
	CDNS dns;
	dns.setHostname((char*)t);
	dns.doDNSLookup();
	dnss_.insert(t);

	for (size_t i = 0; i < dns.getNumberOfIP(); ++i) {
		unsigned int ip = inet_addr(dns.getIPAt(i).c_str());
		ips_.insert(ip);
	}
}
// ɾ��һ�������˵�dns
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
			// assert(false);
		}
	}
}