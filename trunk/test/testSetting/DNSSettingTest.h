#ifndef _TEST_SETTING_DNSSETTINGTEST_H__
#define _TEST_SETTING_DNSSETTINGTEST_H__

#include "stdafx.h"
#include <DNSSetting.h>
#include <cppunit/extensions/HelperMacros.h>

class DNSSettingTest  : public CPPUNIT_NS::TestFixture {
public:
	DNSSettingTest(void);
	~DNSSettingTest(void);

public:
	CPPUNIT_TEST_SUITE(DNSSettingTest);
	CPPUNIT_TEST(testCheck);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testCheck();
};

#endif  // _TEST_SETTING_DNSSETTINGTEST_H__