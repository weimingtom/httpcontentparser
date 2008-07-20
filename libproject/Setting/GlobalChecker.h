#ifndef _SETTING_GLOBAL_CHECKER_H__
#define _SETTING_GLOBAL_CHECKER_H__

#include <set>

class DNSCheck;
class DNSList;
class ImageCheck;

// 负责对所有包进行检测是否应该通过
class GlobalChecker {
public:
	GlobalChecker(void);
	~GlobalChecker(void);

public:
	bool initialize();

	// 对DNS的CHECK
	bool checkDNS(const std::string &dns);
	void enableDNSCheck(const bool checked);
	void addBlackDNS(const std::string &dns);
	void adllWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);

	// 全局的管理
	void enableApplications(const bool enabled);
private:

	bool global_enable_; // 全局

	DNSCheck	*dns_check_;
	ImageCheck  *image_check_;
	DNSList		* dns_list_;
};


#endif  // _SETTING_GLOBAL_CHECKER_H__