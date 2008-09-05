#include "StdAfx.h"
#include ".\dnssettingtest.h"
#include <DNSSetting.h>
using namespace CPPUNIT_NS;

DNSSettingTest::DNSSettingTest(void) {
}

DNSSettingTest::~DNSSettingTest(void) {
}

void DNSSettingTest::testCheck() {
	DNSList black, white;
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	CPPUNIT_ASSERT(true == dns_setting.addBlackDNS("sina.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addBlackDNS("sohu.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addWhiteDNS("google.com"));

	// 当已经在黑名单加入，就不能在白名单加入，反之亦然
	CPPUNIT_ASSERT(false ==   dns_setting.addWhiteDNS("sina.com"));
	CPPUNIT_ASSERT(false == dns_setting.addWhiteDNS("sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.addBlackDNS("google.com"));

	dns_setting.enableBlackDNSCheck(true);
	CPPUNIT_ASSERT(0 !=  dns_setting.checkDNS("google.com"));
	CPPUNIT_ASSERT(0 == dns_setting.checkDNS("sohu.com"));
	CPPUNIT_ASSERT(0 == dns_setting.checkDNS("sohu.com"));

	dns_setting.enableBlackDNSCheck(false);
	CPPUNIT_ASSERT(0 != dns_setting.checkDNS("google.com"));
	CPPUNIT_ASSERT(0 != dns_setting.checkDNS("sohu.com"));
	CPPUNIT_ASSERT(0 != dns_setting.checkDNS("sohu.com"));
}