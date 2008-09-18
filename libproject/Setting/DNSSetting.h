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

// Ŀǰ����ʹ�õĻ�����Щ��Ӧ�Բ��ߣ�������Ҫ����cache���ơ�

class DNSEnumerator {
public:
	virtual int EnumDNS(const std::string &dns) = 0;
};

class DNSList {
public:
	DNSList(void);
	~DNSList(void);

public:
	bool checkDNS(const std::string &dns_name) const;
	bool fuzzeCheckDNS(const std::string &dns_name) const;

	// ���ɾ��DNS
	void addDNS(const std::string &dns_name);
	bool removeDNS(const std::string &dns_name);

	void enableCheck(const bool checked) { enable_check_ = checked;}
	bool needChecked() const { return enable_check_ ;}

	// enumerate
	void beginEnum(DNSEnumerator *enumerator);
protected:
	typedef std::set<std::string> DNS_SET;
	DNS_SET dns_set_;
	bool enable_check_;
};

// ���
class DNSCheck {
public:
	DNSCheck(DNSList *black_dns_list, DNSList *white_dns_list);
	~DNSCheck(void);

	enum {IN_BLACK_LIST = 0,
		IN_WHITE_LIST,
		NOT_SEPCIFIED
	};

	int fuzzeCheckDNS(const std::string &dns_name);
	int checkDNS(const std::string &dns_name);
	void enableBlackDNSCheck(const bool checked);
	void enableWhiteDNSCheck(const bool checked);
protected:

	DNSList * black_dns_list_;
	DNSList * white_dns_list_;
	DNSCheck();
};

// class DNSSetting
// ��������а����м���Ƿ�Ӧ��ͨ��
// �������COM�������Ӵ��
class DNSSetting {
public:
	DNSSetting();
	~DNSSetting(void);

public:
	bool initialize(DNSList *black_dns_list, DNSList *white_dns_list);

	// ��DNS��CHECK
	int checkDNS(const std::string &dns);
	int fuzzeCheckDNS(const std::string &dns);

	void enableWhiteDNSCheck(const bool checked);
	void enableBlackDNSCheck(const bool checked);

	bool addBlackDNS(const std::string &dns);
	bool addWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);
private:
	DNSCheck	* dns_check_;
	DNSList		* black_dns_list_;
	DNSList		* white_dns_list_;
};


#endif  // _SETTING_DNSSETTING_CHECKER_H__