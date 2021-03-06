#include "StdAfx.h"
#include ".\DNSSetting.h"
#include <utility\dns.h>
#include <set>
#include <string>
#include <assert.h>
#include <DebugOutput.h>
using namespace std;

#ifdef DNS_SETTING_TRACE_ENABLED
#define DNS_SETTING_TRACE(FMT)		_DEBUG_STREAM_TRC_("[Setting] {"<< __FUNCTION__<<"}"<<FMT)
#else
#define DNS_SETTING_TRACE(FMT)	
#endif


//////////////////////////////////////////////////////
// class DNSSetting
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
	setModified(true);
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
bool DNSSetting::addBlackDNS(const std::string &dns) {
	setModified(true);
	assert ( black_dns_list_ != NULL);
	if (check(dns) == IN_WHITE_LIST) {
		DNS_SETTING_TRACE("FAILED in add DNS "<<dns<<" into black DNS(Has been in white list))");
		return false;
	} else {
		DNS_SETTING_TRACE("SUCC in add DNS "<<dns<<" into black DNS");
		black_dns_list_->addDNS(dns);
		return true;
	}
}

bool DNSSetting::addWhiteDNS(const std::string &dns) {
	setModified(true);
	assert ( white_dns_list_ != NULL);

	if (check(dns) == IN_BLACK_LIST) {
		DNS_SETTING_TRACE("FAILED in add DNS "<<dns<<" into White DNS(has been in black list)");
		return false;
	} else {
		DNS_SETTING_TRACE("SUCC in add DNS "<<dns<<" into White DNS");
		white_dns_list_->addDNS(dns);
		return true;
	}
}


std::string DNSSetting::getFirstWhiteDNS() {
	return white_dns_list_->getFirstDNS();
}
std::string DNSSetting::getNextWhiteDNS(const std::string &dns) {
	return white_dns_list_->getNextDNS(dns);
}
std::string DNSSetting::getFirstBlackDNS() {
	return black_dns_list_->getFirstDNS();
}
std::string DNSSetting::getNextBlackDNS(const std::string &dns) {
	return black_dns_list_->getNextDNS(dns);
}
// 移除
bool DNSSetting::removeBlackDNS(const std::string &dns_name) {
	setModified(true);
	assert ( black_dns_list_ != NULL);
	
	bool result =  black_dns_list_->removeDNS(dns_name); 

	DNS_SETTING_TRACE("remove DNS : "<<dns_name<< "from black list "<<(result == true?" succ":" failed"));
	return result;
}

bool DNSSetting::removeWhiteDNS(const std::string &dns_name) {
	setModified(true);
	assert ( white_dns_list_ != NULL);
	

	bool result =  white_dns_list_->removeDNS(dns_name);
	DNS_SETTING_TRACE("remove DNS : "<<dns_name<< "from white list " << (result == true?" succ":" failed"));
	return result;
}

int DNSSetting::check(const std::string &dns) {
	if (true == white_dns_list_->checkDNS(dns)) {	// 如果在白名单中
		DNS_SETTING_TRACE("CHECK DNS : "<<dns<<" IN_WHITE_LIST");
		return (IN_WHITE_LIST);
	} else if (true == black_dns_list_->checkDNS(dns)) {	// 如果在黑名单中
		DNS_SETTING_TRACE("CHECK DNS : "<<dns<<" IN_BLACK_LIST");
		return (IN_BLACK_LIST);
	} else {	// 如果不在黑名单中
		DNS_SETTING_TRACE("CHECK DNS : "<<dns<<" NOT_WHITE_LIST");
		return (NOT_SEPCIFIED);
	}
}

bool DNSSetting::inWhiteList(const std::string &dns) {
	return white_dns_list_->checkDNS(dns);
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
		DNS_SETTING_TRACE("CHECK DNS : "<<dns_name<<" return true (isEnable() == false)");
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

bool DNSSetting::isWhiteDNSSettingEnable() const {
	return white_dns_list_->isSettingEnabled();
}
bool DNSSetting::isBlackDNSSettingEnable() const {
	return black_dns_list_->isSettingEnabled();
}
void DNSSetting::enableBlackDNSCheck(const bool checked) {
	setModified(true);
	black_dns_list_->enable(checked);
}

void DNSSetting::enableWhiteDNSCheck(const bool checked) {
	setModified(true);
	white_dns_list_->enable(checked);
}

//=======================================
// XML
int DNSSetting::parseConfig(TiXmlElement * item_root) {
	const TCHAR *  enable_attr_passed = item_root->Attribute(CONFIG_WHITEURL_JUSTPASSED);
	justPassWhiteDNS(enabledFromString(enable_attr_passed));
	return 0;
}

TiXmlElement * DNSSetting::saveConfig(TiXmlElement * item_root) {
	item_root->SetAttribute(CONFIG_WHITEURL_JUSTPASSED, enabledFromBool(just_pass_white_dns_));
	return item_root;
}

//////////////////////////////////////////////////
// class DNSCheck
DNSList::DNSList(const std::string & name) : ConfigItem("", name) {
	enabled_ = true;
}

DNSList::DNSList(void) {
	enabled_ = true;
}

DNSList::~DNSList(void) {
}

// 获取DNS列表
std::string  DNSList::getFirstDNS() {
	if (dns_set_.size() == 0) {
		return std::string("");
	} else {
		return dns_set_.begin()->second;
	}
}
std::string DNSList::getNextDNS(const std::string &name) {
	assert (name.length() != 0);
	if (name.length() == 0) {
		return name;
	} else {
		DNS_SET::iterator iter = dns_set_.upper_bound(name);
		if (iter == dns_set_.end()) {
			return std::string("");
		} else {
			return iter->second;
		}
	}

}

//==================================
// 测试DNS是否在黑白名单当中
bool DNSList::checkDNS(const std::string &dns_name) const {
	if ( false == isEnabled())	
		return false;

	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());

	// 表明不在此名单内
	if (dns_set_.end() != dns_set_.find(buffer)) {
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
		if (dns_name.find(iter->first) != -1) {
			return true;
		}
	}

	return false;
}

//=====================================
// 从DNS中移除
bool DNSList::removeDNS(const std::string &dns_name) {
	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());

	DNS_SET::iterator iter = dns_set_.find(buffer);
	if (dns_set_.end() != iter) {
		dns_set_.erase(iter);
		return true;
	}
	return false;
}

void DNSList::addDNS(const std::string &dns_name) {
	// 去除DNS MAIN name
	const int buf_size = MAX_PATH;
	TCHAR main_dns[buf_size], main_host_name[buf_size];
	get_main_dns_name(main_dns, buf_size, dns_name.c_str());
	get_main_serv_name(main_host_name, buf_size, dns_name.c_str());
	dns_set_.insert(std::make_pair(main_dns, main_host_name));
}


void DNSList::beginEnum(Enumerator1<std::string> *enumerator) {
	assert (NULL != enumerator);

	DNS_SET::const_iterator iter = dns_set_.begin();
	for (; iter != dns_set_.end(); ++iter) {
		enumerator->Enum(iter->second);
	}
}

//=======================================
// XML operation
int DNSList::parseConfig(TiXmlElement * item_root) {
	getURLs(item_root);
	return 0;
}
TiXmlElement * DNSList::saveConfig(TiXmlElement * item_root) {
	return saveURL(item_root);
}

namespace {
// class DNSEnumerator
class DNSEnum : public Enumerator1<std::string> {
public:
	virtual int Enum(const std::string &dns) {
		TiXmlElement * url_node = new TiXmlElement(CONFIG_NODE_URL);
		TiXmlText * text = new TiXmlText(dns);
		url_node->LinkEndChild(text);
		rule_root_->LinkEndChild(url_node);
		return 0;
	}
public:
	DNSEnum(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
		assert (rule_root_ != NULL);
	}
private:
	TiXmlElement *rule_root_;
};
};

TiXmlElement * DNSList::saveURL(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);

	// 设置属性
	rule_root->SetAttribute(CONFIG_CONST_NAME, name_);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingEnabled()));
	// 添加URL
	beginEnum(&DNSEnum(rule_root));
	root->LinkEndChild(rule_root);
	return rule_root;
}


int DNSList::enableURLcheck(const TCHAR *isenable) {
	const bool checked = enabledFromString(isenable);
	enable(checked);
	return 0;
}

int DNSList::getURLs(TiXmlElement * rule_root) {
	// enable?
	const TCHAR *  enable_attr = rule_root->Attribute(CONFIG_CONST_ENABLE);
	enableURLcheck(enable_attr);

	// 内容
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			addDNS(ele->GetText());
		}

		node = node->NextSibling();
	}
	return 0;
}
