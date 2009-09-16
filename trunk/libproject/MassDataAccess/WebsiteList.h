#ifndef _WEBSITE_LIST_H__
#define _WEBSITE_LIST_H__

#include <map>
#include <set>
#include <boost/function.hpp>

// 保存于网站相关的数据
class WebsiteList {
public:
	WebsiteList(void);
	~WebsiteList(void);
public:
	bool is_in_set(const std::string &dns_name) const;

	// 添加删除DNS
	void add_website(const std::string &dns_name);
	bool remote_website(const std::string &dns_name);

	// enumerate
	void enum_webistes(boost::function<int (const char *)> enum_fun);

	// 获取DNS
	// 之所以采用这种方式，是因为map不能使用下表进行访问
	std::string  get_first_website();
	std::string get_next_website(const std::string &name);
protected:
	typedef std::map<std::string, std::string> WEBSITES_SET;
	WEBSITES_SET websites_set_;
};

#endif  // _WEBSITE_LIST_H__