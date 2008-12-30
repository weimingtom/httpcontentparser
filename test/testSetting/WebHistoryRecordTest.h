#ifndef _TEST_SETTING_WEBHISTORYRECORDTEST_H_
#define _TEST_SETTING_WEBHISTORYRECORDTEST_H_

#include <cppunit/extensions/HelperMacros.h>


class WebHistoryRecordTest  : public CPPUNIT_NS::TestFixture {
public:
	WebHistoryRecordTest(void);
	~WebHistoryRecordTest(void);

public:
	CPPUNIT_TEST_SUITE(WebHistoryRecordTest);
	CPPUNIT_TEST(TestDefault);
	CPPUNIT_TEST(TestRegular);
	CPPUNIT_TEST(TestEnable);
	CPPUNIT_TEST(TestParentMode);
	CPPUNIT_TEST_SUITE_END();
protected:
	void TestDefault();
	void TestRegular();
	void TestEnable();
	void TestParentMode();
};

#endif // _TEST_SETTING_WEBHISTORYRECORDTEST_H_