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
	int add_website(const std::string &dns_name);
	int remote_website(const std::string &dns_name);

	// enumerate
	void enum_webistes(boost::function<int (const char *)> enum_fun);

	// ��ȡDNS
	// ֮���Բ������ַ�ʽ������Ϊmap����ʹ���±���з���
	int get_first_website(std::string *first_item);
    int get_next_website(const std::string &name, std::string *next_item);

    int get_item_num() const { return websites_set_.size();}
protected:
	typedef std::map<std::string, std::string> WEBSITES_SET;
	WEBSITES_SET websites_set_;
};

#endif  // _WEBSITE_LIST_H__