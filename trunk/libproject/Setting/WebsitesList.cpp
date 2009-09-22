#include "stdafx.h"
#include "WebsiteList.h"
#include <utility\dns.h>

WebsiteList::WebsiteList(void) {
}

WebsiteList::~WebsiteList(void) {
}

// ��ȡDNS�б�
int  WebsiteList::get_first_website(std::string * website) {
    assert(NULL != website);

	if (websites_set_.size() == 0) {
		return 1;
	} else {
		*website =  websites_set_.begin()->second;
        return 0;
	}
}

int WebsiteList::get_next_website(const std::string &name, std::string *next_item) {
    assert(NULL != next_item);
	assert (name.length() != 0);
	if (name.length() == 0) {
		return -1;
	} else {
		WEBSITES_SET::iterator iter = websites_set_.upper_bound(name);
		if (iter == websites_set_.end()) {
			return -1;
		} else {
			*next_item =  iter->second;
            return 0;
		}
	}
}

//==================================
// ����DNS�Ƿ��ںڰ���������
bool WebsiteList::is_in_set(const std::string &dns_name) const {
	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());

	// �������ڴ�������
	if (websites_set_.end() != websites_set_.find(buffer)) {
		return true;
	} else {
		return false;
	}
}

//=====================================
// ��DNS���Ƴ�
int WebsiteList::remote_website(const std::string &dns_name) {
	TCHAR buffer[1024];
	get_main_dns_name(buffer, 1024, dns_name.c_str());

	WEBSITES_SET::iterator iter = websites_set_.find(buffer);
	if (websites_set_.end() != iter) {
		websites_set_.erase(iter);
		return 0;
    } else {
	    return 1;
    }
}

int WebsiteList::add_website(const std::string &dns_name) {
	// ȥ��DNS MAIN name
	const int buf_size = 256;
	TCHAR main_dns[buf_size], main_host_name[buf_size];
	get_main_dns_name(main_dns, buf_size, dns_name.c_str());
	get_main_serv_name(main_host_name, buf_size, dns_name.c_str());
	websites_set_.insert(std::make_pair(main_dns, main_host_name));
    return 0;
}


void WebsiteList::enum_webistes(boost::function<int (const char *)> enum_fun) {
	WEBSITES_SET::const_iterator iter = websites_set_.begin();
	for (; iter != websites_set_.end(); ++iter) {
        enum_fun(iter->second.c_str());
	}
}

