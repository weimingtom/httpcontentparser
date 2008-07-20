#ifndef _TEST_SETTING_SETTING_TEST_H__
#define _TEST_SETTING_SETTING_TEST_H__

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class SettingTest : public CPPUNIT_NS::TestFixture {
public:
	CPPUNIT_TEST_SUITE(SettingTest);
	CPPUNIT_TEST_SUITE_END();
public:
	virtual void setUp();
	virtual void tearDown();
protected:
};

#endif  // _TEST_SETTING_SETTING_TEST_H__