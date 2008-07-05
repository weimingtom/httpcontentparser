// TestDNS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
#include <cppunit/extensions/HelperMacros.h>
class DNSTest : public CPPUNIT_NS::TestFixture {
public: 
	CPPUNIT_TEST_SUITE(DNSTest);
	CPPUNIT_TEST(GetDNS);
	CPPUNIT_TEST(GetMultHostName);
	CPPUNIT_TEST_SUITE_END();

protected:
	void GetMultHostName();
	void GetDNS();
};
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

CPPUNIT_TEST_SUITE_REGISTRATION(DNSTest);

int _tmain(int argc, _TCHAR* argv[]) {
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

