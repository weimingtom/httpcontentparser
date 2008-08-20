#ifndef _SETTING_GLOBAL_CHECKER_H__
#define _SETTING_GLOBAL_CHECKER_H__

#include <set>

class DNSCheck;
class DNSList;
class ImageSetting;

// class GlobalSetting
// ��������а����м���Ƿ�Ӧ��ͨ��
// �������COM�������Ӵ��
class GlobalSetting {
public:
	GlobalSetting(void);
	~GlobalSetting(void);

public:
	bool initialize();

	// ��DNS��CHECK
	bool checkDNS(const std::string &dns);
	bool checkIP(const std::string &ipAddress);

	void enableDNSCheck(const bool checked);

	void addBlackDNS(const std::string &dns);
	void adllWhiteDNS(const std::string &dns);
	bool removeBlackDNS(const std::string &dns_name);
	bool removeWhiteDNS(const std::string &dns_name);

	//
	void enableShowImage(const bool show);
	bool showImage() const;
	void enableImageCheck(const int type, const bool check);
	bool imageNeedCheck(const int type) const;
private:

	bool global_enable_; // ȫ��

	DNSCheck	*dns_check_;
	ImageSetting  *image_check_;
	DNSList		* dns_list_;

	// ��ǰ�û�
	
};


#endif  // _SETTING_GLOBAL_CHECKER_H__