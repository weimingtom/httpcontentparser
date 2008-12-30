#ifndef _UTILITY_DNS_TEST_H__
#define _UTILITY_DNS_TEST_H__

#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <utility/dns.h>

class DNSTest : public CPPUNIT_NS::TestFixture {
public: 
	CPPUNIT_TEST_SUITE(DNSTest);
	CPPUNIT_TEST(GetMainNameWithPort);
	CPPUNIT_TEST(GetMainNameTest);
	CPPUNIT_TEST(GetMainNameFromBrowseAddresss);
	CPPUNIT_TEST(GetMainNameFromBrowseAddressswithProto);
	CPPUNIT_TEST(GetDNS);
	CPPUNIT_TEST(GetMultHostName);
	CPPUNIT_TEST(GetMultHostName);
	CPPUNIT_TEST(BeginWWWTest);
	CPPUNIT_TEST(BeginWWWTest);
	CPPUNIT_TEST_SUITE_END();
protected:
	void GetMultHostName();
	void GetDNS();
	void GetMainNameWithPort();	// 测试带有端口号的地址
	void GetMainNameTest();	
	void BeginWWWTest();
	void GetMainNameFromBrowseAddresss();
	void GetMainNameFromBrowseAddressswithProto();
};

#endif  // _UTILITY_DNS_TEST_H__