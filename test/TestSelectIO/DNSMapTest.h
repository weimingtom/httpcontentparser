#ifndef _TEST_SELECTIO_DNSMAP_H__
#define _TEST_SELECTIO_DNSMAP_H__

#include <cppunit/extensions/HelperMacros.h>


class DNSMapTest : public CPPUNIT_NS::TestFixture  {
public:
	DNSMapTest(void);
	~DNSMapTest(void);

public:
	CPPUNIT_TEST_SUITE(DNSMapTest);
	CPPUNIT_TEST(TestDNSMap);
	CPPUNIT_TEST_SUITE_END();
private:
	void TestDNSMap();
};

#endif // _TEST_SELECTIO_DNSMAP_H__
