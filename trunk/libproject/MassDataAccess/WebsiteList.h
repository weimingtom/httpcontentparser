#ifndef _WEBSITE_LIST_H__
#define _WEBSITE_LIST_H__

#include <map>
#include <set>
#include <boost/function.hpp>

// ��������վ��ص�����
class WebsiteList {
public:
	WebsiteList(void);
	~WebsiteList(void);
public:
	bool is_in_set(const std::string &dns_name) const;

	// ���ɾ��DNS
	void add_website(const std::string &dns_name);
	bool remote_website(const std::string &dns_name);

	// enumerate
	void enum_webistes(boost::function<int (const char *)> enum_fun);

	// ��ȡDNS
	// ֮���Բ������ַ�ʽ������Ϊmap����ʹ���±���з���
	std::string  get_first_website();
	std::string get_next_website(const std::string &name);
protected:
	typedef std::map<std::string, std::string> WEBSITES_SET;
	WEBSITES_SET websites_set_;
};

#endif  // _WEBSITE_LIST_H__