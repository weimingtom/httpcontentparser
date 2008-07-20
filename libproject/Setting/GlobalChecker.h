#ifndef _SETTING_GLOBAL_CHECKER_H__
#define _SETTING_GLOBAL_CHECKER_H__

#include <set>

class DNSCheck;
class DNSList;
class ImageCheck;

// ��������а����м���Ƿ�Ӧ��ͨ��
class GlobalChecker {
public:
	GlobalChecker(void);
	~GlobalChecker(void);

public:
	bool initialize();

	// ��DNS��CHECK
	bool checkDNS(const std::string &dns);
	void enableDNSCheck(const bool checked);
	void addBlackDNS(const std::string &dns);
	void adllWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);

	// ȫ�ֵĹ���
	void enableApplications(const bool enabled);
private:

	bool global_enable_; // ȫ��

	DNSCheck	*dns_check_;
	ImageCheck  *image_check_;
	DNSList		* dns_list_;
};


#endif  // _SETTING_GLOBAL_CHECKER_H__