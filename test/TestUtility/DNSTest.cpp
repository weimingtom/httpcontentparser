#include "StdAfx.h"
#include ".\dnstest.h"

void DNSTest::GetMainNameFromBrowseAddresss() {
	TCHAR result[MAX_PATH];
	{
		const TCHAR * test_unit = "code.google.com/p/httpcontentparser/issues/detail?id=57";
		const TCHAR * expected_result = "google";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.baidu.com/s?ie=gb2312&bs=%B0%C2%B6%FB%C2%B3%CB%E9%C6%AC&sr=&z=&cl=3&f=8&wd=%C4%CE%B6%FB%C2%B3%CB%E9%C6%AC&ct=0";
		const TCHAR * expected_result = "baidu";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "sports.sina.com.cn/nba/";
		const TCHAR * expected_result = "sina";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}
}

void DNSTest::GetMainNameFromBrowseAddressswithProto() {
	TCHAR result[MAX_PATH];
	{
		const TCHAR * test_unit = "http://code.google.com/p/httpcontentparser/issues/detail?id=57";
		const TCHAR * expected_result = "google";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "http://www.baidu.com/s?ie=gb2312&bs=%B0%C2%B6%FB%C2%B3%CB%E9%C6%AC&sr=&z=&cl=3&f=8&wd=%C4%CE%B6%FB%C2%B3%CB%E9%C6%AC&ct=0";
		const TCHAR * expected_result = "baidu";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "http://sports.sina.com.cn/nba/";
		const TCHAR * expected_result = "sina";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}
}

void DNSTest::GetMainNameTest() {
	TCHAR result[MAX_PATH];

	{
		const TCHAR * test_unit = "p2.WWW.SINA.com.cn";
		const TCHAR * expected_result = "sina";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "seach.netorg.cn";
		const TCHAR * expected_result = "netorg";
		CPPUNIT_ASSERT( _tcslen(expected_result)
			== get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}


	{
		const TCHAR * test_unit = "www.google.cn";
		const TCHAR * expected_result = "google";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.netorg.cn";
		const TCHAR * expected_result = "netorg";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.orgkk.cn";
		const TCHAR * expected_result = "orgkk";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	
	{
		const TCHAR * test_unit = "www.comkk.cn";
		const TCHAR * expected_result = "comkk";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "hello1";
		const TCHAR * expected_result = "hello1";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "seach.SINA.com.cn";
		const TCHAR * expected_result = "sina";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.google.SINA.com.cn";
		const TCHAR * expected_result = "sina";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "www.bit.edu.cn";
		const TCHAR * expected_result = "bit";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "google.cn";
		const TCHAR * expected_result = "google";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

	{
		const TCHAR * test_unit = "google";
		const TCHAR * expected_result = "google";
		CPPUNIT_ASSERT( _tcslen(expected_result) == 
			get_main_dns_name(result, MAX_PATH,test_unit));
		CPPUNIT_ASSERT( 0 == _tcscmp(result, expected_result));
	}

}
void DNSTest::BeginWWWTest() {
	const TCHAR * test_case1 = TEXT("www.");
	const TCHAR * test_case2 = TEXT("wwww.");
	const TCHAR * test_case3 = TEXT("w.ww.sina.");
	const TCHAR * test_case4 = TEXT("w.www.sina.com");
	const TCHAR * test_case5 = TEXT("ww.www.");
	const TCHAR * test_case6 = TEXT("soe.diw");
	const TCHAR * test_case7 = TEXT("WwW.");
	const TCHAR * test_case8 = TEXT("Www.");

	CPPUNIT_ASSERT(true == beginwidht_www(test_case1));
	CPPUNIT_ASSERT(false == beginwidht_www(test_case2));
	CPPUNIT_ASSERT(false == beginwidht_www(test_case3));
	CPPUNIT_ASSERT(false == beginwidht_www(test_case4));
	CPPUNIT_ASSERT(false == beginwidht_www(test_case5));
	CPPUNIT_ASSERT(false == beginwidht_www(test_case6));
	CPPUNIT_ASSERT(true == beginwidht_www(test_case7));
	CPPUNIT_ASSERT(true == beginwidht_www(test_case8));
}
void DNSTest::GetMultHostName() {
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
	//CPPUNIT_ASSERT(dns.getHostAt(4) == noneIp);
	//CPPUNIT_ASSERT(dns.getNumberOfHosts() == 3);
	//CPPUNIT_ASSERT(hostnames.find(dns.getHostAt(0)) != hostnames.end());
	//CPPUNIT_ASSERT(hostnames.find(dns.getHostAt(1)) != hostnames.end());
	//CPPUNIT_ASSERT(hostnames.find(dns.getHostAt(2)) != hostnames.end());
}
void DNSTest::GetDNS() {
	//std::string dnsname = "www.bitstart.net";
	//std::string bitstartIp = _T("10.1.130.111");
	//const std::string noneIp = _T("");

	//// 查询自身网址
	//CDNS dns;
	////dns.doDNSLookup();
	////CPPUNIT_ASSERT(dns.getNumberOfIP() == 1);
 //
	//// 查询给定网址
	//dns.setHostname(dnsname);
	//dns.doDNSLookup();
	//CPPUNIT_ASSERT(dns.getNumberOfIP() == 1);
	//CPPUNIT_ASSERT(dns.getIPAt(0) == bitstartIp);
	//CPPUNIT_ASSERT(dns.getIPAt(1) == noneIp);
}