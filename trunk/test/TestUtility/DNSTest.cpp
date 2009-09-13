#include "StdAfx.h"
#include ".\dnstest.h"
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

void TestGetMainServName() {
	char buffer[1024];
	{
	char *dns1 = "www.sina.com";
	get_main_serv_name(buffer, 1024, dns1);
	BOOST_ASSERT(0 == strcmp(buffer, dns1));

	char *dns2 = "http:\\www.sina.com";
	char * result2 = "www.sina.com";
	get_main_serv_name(buffer, 1024, dns1);
	BOOST_ASSERT(0 == strcmp(buffer, result2));
	}

	{
	char *dns1 = "9.186.118.34:80/index.html";
	char * result1 = "9.186.118.34:80";
	get_main_serv_name(buffer, 1024, dns1);
	BOOST_ASSERT(0 == strcmp(buffer, result1));
	}

	{
	char *dns1 = "http://www.hao123.com/jinshi.htm";
	char * result1 = "www.hao123.com";
	get_main_serv_name(buffer, 1024, dns1);
	BOOST_ASSERT(0 == strcmp(buffer, result1));
	}

	{
	char *dns = "http://www.google.com/coop/cse/";
	char * result = "www.google.com";
	get_main_serv_name(buffer, 1024, dns);
	BOOST_ASSERT(0 == strcmp(buffer, result));
	}

	{
	char *dns = "http://www.google.name/coop/cse/";
	char * result = "www.google.name";
	get_main_serv_name(buffer, 1024, dns);
	BOOST_ASSERT(0 == strcmp(buffer, result));
	}

	{
	char *dns = "https://www.google.com/accounts/ManageAccount";
	char * result = "www.google.com";
	get_main_serv_name(buffer, 1024, dns);
	BOOST_ASSERT(0 == strcmp(buffer, result));
	}

	{
	char *dns = "https://s.google.com/accounts/ManageAccount";
	char * result = "s.google.com";
	get_main_serv_name(buffer, 1024, dns);
	BOOST_ASSERT(0 == strcmp(buffer, result));
	}
}
void TestContainIPinDNS() {
	{
	char *dns1 = "www.sina.com";
	BOOST_ASSERT(! isContainsIP(dns1));

	char *dns2 = "http:\\www.sina.com";
	BOOST_ASSERT(! isContainsIP(dns2));
	}

	{
	char *dns1 = "9.186.118.34:80/index.html";
	BOOST_ASSERT( isContainsIP(dns1));

	char *dns2 = "http://9.186.118.34:80/index.html";
	BOOST_ASSERT( isContainsIP(dns2));

	char *dns3 = "http://288.186.118.34:80/index.html";
	BOOST_ASSERT(! isContainsIP(dns3));

	char *dns4 = "http://288.186.118.3480/index.html";
	BOOST_ASSERT(! isContainsIP(dns4));

	char *dns5 = "http://288.186.118.34index.html";
	BOOST_ASSERT(! isContainsIP(dns5));

	char *dns6 = "https://288.186.118.34index.html";
	BOOST_ASSERT(! isContainsIP(dns6));
	}
}
void TestValidateIPWithEnd() {
	// 结尾包含其他字母
	{
	char * end;
	TCHAR * ip1 = "9.186.181.1dfe";
	BOOST_ASSERT(validateStringIP(ip1, &end));
	BOOST_ASSERT(end[0] == 'd');
	BOOST_ASSERT(end[1] == 'f');

	TCHAR * ip2 = "9.186.1.1d";
	BOOST_ASSERT(validateStringIP(ip2, &end));
	BOOST_ASSERT(*end == 'd');

	TCHAR * ip3 = "9.1.11.34b";
	BOOST_ASSERT(validateStringIP(ip3, &end));
	BOOST_ASSERT(*end == 'b');

	TCHAR * ip4 = "1.82.255.34a";
	BOOST_ASSERT(validateStringIP(ip4, &end));
	BOOST_ASSERT(*end == 'a');
	}
}
void TestvalidateIP() {
	{
	TCHAR * ip1 = "9.186.181.34";
	BOOST_ASSERT(validateStringIP(ip1));
	}

	// 数字超限
	{
	TCHAR * ip1 = "738.186.181.34";
	BOOST_ASSERT(!validateStringIP(ip1));

	TCHAR * ip2 = "38.286.181.34";
	BOOST_ASSERT(!validateStringIP(ip2));

	TCHAR * ip3 = "38.186.281.34";
	BOOST_ASSERT(!validateStringIP(ip3));

	TCHAR * ip4 = "38.186.181.334";
	BOOST_ASSERT(!validateStringIP(ip4));
	}

	// 包含字母
	{
	TCHAR * ip1 = "9.186.181.aa";
	BOOST_ASSERT(!validateStringIP(ip1));

	TCHAR * ip2 = "9.186.aa.34";
	BOOST_ASSERT(!validateStringIP(ip2));

	TCHAR * ip3 = "9.aa.11.34";
	BOOST_ASSERT(!validateStringIP(ip3));

	TCHAR * ip4 = "a.82.255.34";
	BOOST_ASSERT(!validateStringIP(ip4));
	}
}

void GetMainNameWithPort() {
	TCHAR result[MAX_PATH];
	{
		const TCHAR * test_unit = "www.sina.com:80";
		const TCHAR * expected_result = "sina";
		int result_length = get_main_dns_name(result, MAX_PATH, test_unit);
		BOOST_ASSERT( result_length == _tcslen(expected_result));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}
}
void GetMainNameFromBrowseAddresss() {
	TCHAR result[MAX_PATH];
	{
		const TCHAR * test_unit = "code.google.com/p/httpcontentparser/issues/detail?id=57";
		const TCHAR * expected_result = "google";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.baidu.com/s?ie=gb2312&bs=%B0%C2%B6%FB%C2%B3%CB%E9%C6%AC&sr=&z=&cl=3&f=8&wd=%C4%CE%B6%FB%C2%B3%CB%E9%C6%AC&ct=0";
		const TCHAR * expected_result = "baidu";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "sports.sina.com.cn/nba/";
		const TCHAR * expected_result = "sina";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "images.sohu.com";
		const TCHAR * expected_result = "sohu";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "alpha.brand.sogou.com";
		const TCHAR * expected_result = "sogou";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.qq.com";
		const TCHAR * expected_result = "qq";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}
}

void GetMainNameFromBrowseAddressswithProto() {
	TCHAR result[MAX_PATH];
	{
		const TCHAR * test_unit = "http://code.google.com/p/httpcontentparser/issues/detail?id=57";
		const TCHAR * expected_result = "google";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "http://www.baidu.com/s?ie=gb2312&bs=%B0%C2%B6%FB%C2%B3%CB%E9%C6%AC&sr=&z=&cl=3&f=8&wd=%C4%CE%B6%FB%C2%B3%CB%E9%C6%AC&ct=0";
		const TCHAR * expected_result = "baidu";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "http://sports.sina.com.cn/nba/";
		const TCHAR * expected_result = "sina";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "https://sports.sina.com.cn/nba/";
		const TCHAR * expected_result = "sina";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}
}

void GetMainNameTest() {
	TCHAR result[MAX_PATH];

	{
		const TCHAR * test_unit = "p2.WWW.SINA.com.cn";
		const TCHAR * expected_result = "sina";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "seach.netorg.cn";
		const TCHAR * expected_result = "netorg";
		BOOST_ASSERT( _tcslen(expected_result)
			== get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}


	{
		const TCHAR * test_unit = "www.google.cn";
		const TCHAR * expected_result = "google";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.netorg.cn";
		const TCHAR * expected_result = "netorg";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.orgkk.cn";
		const TCHAR * expected_result = "orgkk";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	
	{
		const TCHAR * test_unit = "www.comkk.cn";
		const TCHAR * expected_result = "comkk";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "hello1";
		const TCHAR * expected_result = "hello1";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "seach.SINA.com.cn";
		const TCHAR * expected_result = "sina";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.google.SINA.com.cn";
		const TCHAR * expected_result = "sina";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.bit.edu.cn";
		const TCHAR * expected_result = "bit";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "google.cn";
		const TCHAR * expected_result = "google";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "google";
		const TCHAR * expected_result = "google";
		BOOST_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		BOOST_ASSERT( 0 == _tcscmp(result, expected_result));
	}

}
void BeginWWWTest() {
	const TCHAR * test_case1 = TEXT("www.");
	const TCHAR * test_case2 = TEXT("wwww.");
	const TCHAR * test_case3 = TEXT("w.ww.sina.");
	const TCHAR * test_case4 = TEXT("w.www.sina.com");
	const TCHAR * test_case5 = TEXT("ww.www.");
	const TCHAR * test_case6 = TEXT("soe.diw");
	const TCHAR * test_case7 = TEXT("WwW.");
	const TCHAR * test_case8 = TEXT("Www.");

	BOOST_ASSERT(true == beginwidht_www(test_case1));
	BOOST_ASSERT(false == beginwidht_www(test_case2));
	BOOST_ASSERT(false == beginwidht_www(test_case3));
	BOOST_ASSERT(false == beginwidht_www(test_case4));
	BOOST_ASSERT(false == beginwidht_www(test_case5));
	BOOST_ASSERT(false == beginwidht_www(test_case6));
	BOOST_ASSERT(true == beginwidht_www(test_case7));
	BOOST_ASSERT(true == beginwidht_www(test_case8));
}
void GetMultHostName() {
	//std::string dnsname = "www.sina.com";
	//const std::string noneIp = "";
	//std::vector<std::string> hostnames;
	//hostnames.push_back(_T("www.sina.com"));
	//hostnames.push_back(_T("us.sina.com.cn"));
	//hostnames.push_back(_T("news.sina.com.cn"));
	//CDNS dns;
	//dns.setHostname(dnsname);
	//dns.doDNSLookup();
	//
	//BOOST_ASSERT(dns.getHostAt(4) == noneIp);
	//BOOST_ASSERT(dns.getNumberOfHosts() == 3);
	//BOOST_ASSERT(hostnames.find(dns.getHostAt(0)) != hostnames.end());
	//BOOST_ASSERT(hostnames.find(dns.getHostAt(1)) != hostnames.end());
	//BOOST_ASSERT(hostnames.find(dns.getHostAt(2)) != hostnames.end());
}
void GetDNS() {
	//std::string dnsname = "www.bitstart.net";
	//std::string bitstartIp = _T("10.1.130.111");
	//const std::string noneIp = _T("");

	//// 查询自身网址
	//CDNS dns;
	////dns.doDNSLookup();
	////BOOST_ASSERT(dns.getNumberOfIP() == 1);
 //
	//// 查询给定网址
	//dns.setHostname(dnsname);
	//dns.doDNSLookup();
	//BOOST_ASSERT(dns.getNumberOfIP() == 1);
	//BOOST_ASSERT(dns.getIPAt(0) == bitstartIp);
	//BOOST_ASSERT(dns.getIPAt(1) == noneIp);
}