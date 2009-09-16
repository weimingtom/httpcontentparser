#include "stdafx.h"
#include "WebsiteList.h"
#include <utility\dns.h>

WebsiteList::WebsiteList(void) {
}

WebsiteList::~WebsiteList(void) {
}

// 获取DNS列表
std::string  WebsiteList::get_first_website() {
	if (websites_set_.size() == 0) {
		return std::string("");
	} else {
		return websites_set_.begin()->second;
	}
}

std::string WebsiteList::get_next_website(const std::string &name) {
	assert (name.length() != 0);
	if (name.length() == 0) {
		return name;
	} else {
		WEBSITES_SET::iterator iter = websites_set_.upper_bound(name);
		if (iter == websites_set_.end()) {
			return std::string("");
		} else {
			return iter->second;
		}
	}
}

//==================================
// 测试DNS是否在黑白名单当中
bool WebsiteList::is_in_set(const std::string &dns_name) const {
	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());

	// 表明不在此名单内
	if (websites_set_.end() != websites_set_.find(buffer)) {
		return true;
	} else {
		return false;
	}
}

//=====================================
// 从DNS中移除
bool WebsiteList::remote_website(const std::string &dns_name) {
	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());

	WEBSITES_SET::iterator iter = websites_set_.find(buffer);
	if (websites_set_.end() != iter) {
		websites_set_.erase(iter);
		return true;
	}
	return false;
}

void WebsiteList::add_website(const std::string &dns_name) {
	// 去除DNS MAIN name
	const int buf_size = 256;
	TCHAR main_dns[buf_size], main_host_name[buf_size];
	get_main_dns_name(main_dns, buf_size, dns_name.c_str());
	get_main_serv_name(main_host_name, buf_size, dns_name.c_str());
	websites_set_.insert(std::make_pair(main_dns, main_host_name));
}


void WebsiteList::enum_webistes(boost::function<int (const char *)> enum_fun) {
	WEBSITES_SET::const_iterator iter = websites_set_.begin();
	for (; iter != websites_set_.end(); ++iter) {
        enum_fun(iter->second.c_str());
	}
}

