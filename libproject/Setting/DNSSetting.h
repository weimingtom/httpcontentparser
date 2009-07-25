// file : DNSSetting.h
// ����ļ����������࣬ ������DNSList, DNSCheck DNSSetting
// DNSList ���𱣴�DNS���б�
// DNSCheck �ṩ�˺ڰ�������ѯ��֧��
// DNSSetting ��ʹ��Bridge�ķ�ʽ�����ṩ��DNS��check����

#ifndef _SETTING_DNSSETTING_CHECKER_H__
#define _SETTING_DNSSETTING_CHECKER_H__

#include <set>
#include <map>
#include <string>
#include <Enumerate.h>
#include <setting\settingitem.h>
#include <setting\configitem.h>
#include <xmldefined.h>

// Ŀǰ����ʹ�õĻ�����Щ��Ӧ�Բ��ߣ�������Ҫ����cache���ơ�

class DNSList : public ConfigItem {
public:
	DNSList(const std::string & name);
	~DNSList(void);
private:
	DNSList(void);
public:
	bool checkDNS(const std::string &dns_name) const;
	bool fuzzeCheckDNS(const std::string &dns_name) const;

	// ���ɾ��DNS
	void addDNS(const std::string &dns_name);
	bool removeDNS(const std::string &dns_name);

	// enumerate
	void beginEnum(Enumerator1<std::string> *enumerator);

	// ��ȡDNS
	// ֮���Բ������ַ�ʽ������Ϊmap����ʹ���±���з���
	std::string  getFirstDNS();
	std::string getNextDNS(const std::string &name);
public:
	void enable(const bool check) {enabled_ = check;}
	bool isEnabled() const { return enabled_;}

	bool isSettingEnabled() const { return enabled_;}
protected:
	typedef std::map<std::string, std::string> DNS_SET;
	DNS_SET dns_set_;

	bool enabled_;

	// ��ȡXML����
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * item_root);

private:
	TiXmlElement * saveURL(TiXmlElement *root);
	int getURLs(TiXmlElement * rule_root);
	int enableURLcheck(const TCHAR *isenable);
};

// class DNSSetting
// ��������а����м���Ƿ�Ӧ��ͨ��
// �������COM�������Ӵ��
class DNSSetting  : public SettingItem,  public ConfigItem  {
public:
	DNSSetting();
	~DNSSetting(void);

private:
	enum {IN_BLACK_LIST = 0,
		IN_WHITE_LIST,
		NOT_SEPCIFIED
	};

	// ������������ȷ��DNS�Ƿ�Ϸ�
	bool dealResult(const int result);

public:
	bool initialize(DNSList *black_dns_list, DNSList *white_dns_list);

	// ��DNS��CHECK
	bool checkDNS(const std::string &dns);
	bool fuzzeCheckDNS(const std::string &dns);
	bool inWhiteList(const std::string &dns);

	// enable
	void justPassWhiteDNS(const bool checked);
	bool justPassWhiteDNS();
	void enableWhiteDNSCheck(const bool checked);
	void enableBlackDNSCheck(const bool checked);

	bool isWhiteDNSSettingEnable() const;
	bool isBlackDNSSettingEnable() const;
	// ���
	bool addBlackDNS(const std::string &dns);
	bool addWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);

	// ��ȡDNS
	std::string getFirstWhiteDNS();
	std::string getNextWhiteDNS(const std::string &dns);
	std::string getFirstBlackDNS();
	std::string getNextBlackDNS(const std::string &dns);
private:
	int check(const std::string &dns);
	int fuzzeCheck(const std::string &dns);
	DNSList		* black_dns_list_;
	DNSList		* white_dns_list_;

	bool just_pass_white_dns_;
private:
	void defaultSetting();

public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * item_root);
};


#endif  // _SETTING_DNSSETTING_CHECKER_H__