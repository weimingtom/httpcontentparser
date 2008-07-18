#include "StdAfx.h"
#include ".\dnstest.h"


void DNSTest::GetMultHostName() {
	std::string dnsname = "www.sina.com";
	const std::string noneIp = "";
	std::vector<std::string> hostnames;
	hostnames.push_back(_T("www.sina.com"));
	hostnames.push_back(_T("us.sina.com.cn"));
	hostnames.push_back(_T("news.sina.com.cn"));
	CDNS dns;
	dns.setHostname(dnsname);
	dns.doDNSLookup();
	
	CPPUNIT_ASSERT(dns.getHostAt(4) == noneIp);
	CPPUNIT_ASSERT(dns.getNumberOfHosts() == 3);
	//CPPUNIT_ASSERT(hostnames.find(dns.getHostAt(0)) != hostnames.end());
	//CPPUNIT_ASSERT(hostnames.find(dns.getHostAt(1)) != hostnames.end());
	//CPPUNIT_ASSERT(hostnames.find(dns.getHostAt(2)) != hostnames.end());
}
void DNSTest::GetDNS() {
	std::string dnsname = "www.bitstart.net";
	std::string bitstartIp = _T("10.1.130.111");
	const std::string noneIp = _T("");

	// 查询自身网址
	CDNS dns;
	//dns.doDNSLookup();
	//CPPUNIT_ASSERT(dns.getNumberOfIP() == 1);
 
	// 查询给定网址
	dns.setHostname(dnsname);
	dns.doDNSLookup();
	CPPUNIT_ASSERT(dns.getNumberOfIP() == 1);
	CPPUNIT_ASSERT(dns.getIPAt(0) == bitstartIp);
	CPPUNIT_ASSERT(dns.getIPAt(1) == noneIp);
}