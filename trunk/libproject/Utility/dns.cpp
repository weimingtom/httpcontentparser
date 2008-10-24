#include "stdafx.h"
#include ".\dns.h"
#include ".\strutility.h"
#include <tchar.h>
#include <assert.h>
  
namespace {
const TCHAR * DNS_POSTFIX_ORG = ".org";
const TCHAR * DNS_POSTFIX_COM = ".com";
const TCHAR * DNS_POSTFIX_NET = ".net";
const TCHAR * DNS_POSTFIX_EDU = ".edu";
const TCHAR * DNS_POSTFIX_GOV = ".gov";

// 之去掉如 .com.cn 或者 .com
// 对于 www.comdie.cn就不应该去掉.com之后的内容
int remove_postfix(TCHAR * name) {
	TCHAR *p = NULL;
	if (NULL != (p = _tcsstr(name, DNS_POSTFIX_COM))) {
		if (p[4] == '\0' || p[4] == '.' || p[4] == '/') {
			p[0] = '\0';
			return p-name;
		}
	} else if (NULL != (p = _tcsstr(name, DNS_POSTFIX_NET))) {
		if (p[4] == '\0' || p[4] == '.'|| p[4] == '/') {
			p[0] = '\0';
			return p-name;
		}
	} else if (NULL != (p = _tcsstr(name, DNS_POSTFIX_EDU))) {
		if (p[4] == '\0' || p[4] == '.'|| p[4] == '/') {
			p[0] = '\0';
			return p-name;
		}
	} else if (NULL != (p = _tcsstr(name, DNS_POSTFIX_ORG))) {
		if (p[4] == '\0' || p[4] == '.'|| p[4] == '/') {
			p[0] = '\0';
			return p-name;
		}
	} else if (NULL != (p = _tcsstr(name, DNS_POSTFIX_GOV))) {
		if (p[4] == '\0' || p[4] == '.'|| p[4] == '/') {
			p[0] = '\0';
			return p-name;
		}
	}

	return _tcslen(name);
}
};


// 前四个字幕是不是www.
bool beginwidht_www(const TCHAR * fulldns) {
	if (fulldns[0] == NULL) return false;
	else if (fulldns[0] != 'w' && fulldns[0] != 'W') return false;
	else if (fulldns[1] == NULL) return false;
	else if (fulldns[1] != 'w' && fulldns[0] != 'W') return false;
	else if (fulldns[2] == NULL) return false;
	else if (fulldns[2] != 'w' && fulldns[0] != 'W') return false;
	else if (fulldns[3] == NULL) return false;
	else if (fulldns[3] != '.' && fulldns[0] != '.') return false;

	return true;
}

int get_main_dns_name(TCHAR * main_name, const int bufsize, const TCHAR *fulldns) {
	assert (bufsize >= MAX_PATH);
	using namespace strutility;

	TCHAR name[MAX_PATH];
	// 确定拷贝函数的其实位置，不过一www.开头就向后移动四个，否则就从0开始
	const int start_index = beginwidht_www(fulldns) ? 4 : 0;
	// 去掉尾部
	memset(name, 0, sizeof(name));
	_tcscpy(name, &(fulldns[start_index]));

	// 首先转成小写
	strtolower(name);

	// 去除掉后缀
	// 仍然有问题 .net. 或者 .net'\0'才可以，否则的话， www.netconfig.com就只能剩下www了
	const int len = remove_postfix(name);
	assert (len == _tcslen(name));
	int len_remove_postfix = 0;
	
	// 去掉国别
	// 如果此时自首两个是.**， 那么去掉它，因为所有过的二级域名都是两个字符
	if (name[len - len_remove_postfix -3] == '.') {
		name[len - len_remove_postfix -3 ] = '\0';

		// 长度减少3
		len_remove_postfix += 3;
	}

	// 可能域名仍然后两个部分，例如
	// 从尾部开始向前寻找'.'
	for (int i = len - len_remove_postfix - 1; i >=0; --i) {
		if ('.' == name[i]) {
			assert (len - len_remove_postfix - 1 - i > 3);	// main name必然大于3
			_tcscpy(main_name, &(name[i+1]));

			len_remove_postfix += i+1;	// 有去掉了 i+1个字符
			return (len - len_remove_postfix);
		}
	}

	_tcsncpy(main_name, name, MAX_PATH);
	return len - len_remove_postfix;
}

/////////////////////////////////////////////////////////////////////////////
// CDNS class
CDNS::CDNS() {
}
bool CDNS::doDNSLookup() {
	// Define host and socket structures
	WSADATA sockData;                           
	hostent *dnsInfo;                     

	// 初始化Winsock
	if(WSAStartup(0x0101, &sockData) != 0) 	{
  		WSACleanup(); 
		return false;
	}

	dnsInfo = gethostbyname(hostName_.c_str());

	if(!dnsInfo) 	{
		WSACleanup();
		return false;
	}

	dnsIps_.clear();
	hostIps_.clear();

	for(int i = 0; dnsInfo->h_addr_list[i]; i++) 	{
		dnsIps_.push_back(inet_ntoa(*((struct in_addr *)dnsInfo->h_addr_list[i])));
	}

	if(dnsInfo->h_aliases[0]) 	{
   	 	for(i = 0; dnsInfo->h_aliases[i]; i++) 		{
			hostIps_.push_back(dnsInfo->h_aliases[i]);
		}
	}

	WSACleanup();
	return true;
}


std::string CDNS::getHostAt(const size_t index) {
	if (index < hostIps_.size()) {
		std::string s = hostIps_.at(index); ;
		return hostIps_.at(index); 
	} else {
		return _T("");
	}
}

size_t CDNS::getNumberOfHosts() const { 
	return hostIps_.size(); 
}

size_t CDNS::getNumberOfIP() const {
	return dnsIps_.size(); 
}


std::string CDNS::getIPAt(const size_t index) {
	if (index < dnsIps_.size())
		return dnsIps_.at(index);
	else
		return _T("");
}