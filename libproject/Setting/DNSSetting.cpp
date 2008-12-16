#include "StdAfx.h"
#include ".\DNSSetting.h"
#include <utility\dns.h>
#include <set>
#include <string>
#include <assert.h>
using namespace std;


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
// ��ʼ��
bool DNSSetting::initialize(DNSList *black_dns_list, DNSList *white_dns_list) {
	assert ( black_dns_list_ == NULL);
	assert ( white_dns_list_ == NULL);

	black_dns_list_ = black_dns_list;
	white_dns_list_ = white_dns_list;

	return false;
}


// ��������ͨ��WHITE DNS
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
// ���ɾ��DNS
bool DNSSetting::addBlackDNS(const std::string &dns) {
	setModified(true);
	assert ( black_dns_list_ != NULL);
	if (check(dns) == IN_WHITE_LIST) {
		return false;
	} else {
		black_dns_list_->addDNS(dns);
		return true;
	}
}

bool DNSSetting::addWhiteDNS(const std::string &dns) {
	setModified(true);
	assert ( white_dns_list_ != NULL);

	if (check(dns) == IN_BLACK_LIST) {
		return false;
	} else {
		white_dns_list_->addDNS(dns);
		return true;
	}
}

// �Ƴ�
bool DNSSetting::removeBlackDNS(const std::string &dns_name) {
	setModified(true);
	assert ( black_dns_list_ != NULL);
	return black_dns_list_->removeDNS(dns_name); 
}

bool DNSSetting::removeWhiteDNS(const std::string &dns_name) {
	setModified(true);
	assert ( white_dns_list_ != NULL);
	return white_dns_list_->removeDNS(dns_name);
}

int DNSSetting::check(const std::string &dns) {
	if (true == white_dns_list_->checkDNS(dns)) {	// ����ڰ�������
		return (IN_WHITE_LIST);
	} else if (true == black_dns_list_->checkDNS(dns)) {	// ����ں�������
		return (IN_BLACK_LIST);
	} else {	// ������ں�������
		return (NOT_SEPCIFIED);
	}
}

int DNSSetting::fuzzeCheck(const std::string &dns) {
	if (true == white_dns_list_->fuzzeCheckDNS(dns)) {	// ����ڰ�������
		return (IN_WHITE_LIST);
	} else if (true == black_dns_list_->fuzzeCheckDNS(dns)) {	// ����ں�������
		return (IN_BLACK_LIST);
	} else {	// ������ں�������
		return (NOT_SEPCIFIED);
	}
}

bool DNSSetting::fuzzeCheckDNS(const std::string &dns_name) {
	assert(black_dns_list_ != NULL);
	assert(white_dns_list_ != NULL);

	// ����ǲ�����ֱ�ӷ���false, ������ҪΪ��Ӧ��SettingItem::PARENT_MODE
	if (isEnabled() == false) {
		return true;
	}

	int result = fuzzeCheck(dns_name);
	return dealResult(result);
}

bool DNSSetting::checkDNS(const std::string &dns_name) {
	assert(black_dns_list_ != NULL);
	assert(white_dns_list_ != NULL);

	// ����ǲ�����ֱ�ӷ���false, ������ҪΪ��Ӧ��SettingItem::PARENT_MODE
	if (isEnabled() == false) {
		return true;
	}

	int result = check(dns_name);
	return dealResult(result);
}

bool DNSSetting::dealResult(const int result) {
	if (justPassWhiteDNS()) {
		// �������ͨ��������
		if (result == IN_WHITE_LIST) 
			return true;
		else
			return false;
	} else {
		// ���ֻ��������
		if (result == IN_BLACK_LIST) 
			return false;
		else
			return true;
	}
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

//==================================
// ����DNS�Ƿ��ںڰ���������
bool DNSList::checkDNS(const std::string &dns_name) const {
	if ( false == isEnabled())	
		return false;

	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());

	// �������ڴ�������
	if (dns_set_.end() != dns_set_.find(buffer)) {
		return true;
	} else {
		return false;
	}
}

// �鿴dns_name�Ƿ���һ���ǰ�������
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
// ��DNS���Ƴ�
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
	// ȥ��DNS MAIN name
	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());
	dns_set_.insert(std::make_pair(buffer, dns_name));
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

	// ��������
	rule_root->SetAttribute(CONFIG_CONST_NAME, name_);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingEnabled()));
	// ���URL
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

	// ����
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
