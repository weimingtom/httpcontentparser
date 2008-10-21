#ifndef _UTILITY_DNS_TEST_H__
#define _UTILITY_DNS_TEST_H__

#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <utility/dns.h>

class DNSTest : public CPPUNIT_NS::TestFixture {
public: 
	CPPUNIT_TEST_SUITE(DNSTest);
	CPPUNIT_TEST(GetDNS);
	CPPUNIT_TEST(GetMultHostName);
	CPPUNIT_TEST(GetMultHostName);
	CPPUNIT_TEST(BeginWWWTest);
	CPPUNIT_TEST(GetMainNameTest);
	CPPUNIT_TEST_SUITE_END();

protected:
	void GetMultHostName();
	void GetDNS();
	void GetMainNameTest();
	void BeginWWWTest();
};

#endif  // _UTILITY_DNS_TEST_H__