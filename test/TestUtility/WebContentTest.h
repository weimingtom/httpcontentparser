#ifndef _TEST_UTILITY_WEB_CONTENTTEST_H__
#define _TEST_UTILITY_WEB_CONTENTTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class WebContentTest : public CPPUNIT_NS::TestFixture {
public:
	WebContentTest(void);
	~WebContentTest(void);

	CPPUNIT_TEST_SUITE(WebContentTest);
	CPPUNIT_TEST(testImageType);
	CPPUNIT_TEST(testTextType);
	CPPUNIT_TEST(textOtherTypes);
	CPPUNIT_TEST_SUITE_END();

private:
	void testImageType();
	void testTextType();
	void textOtherTypes();
};

#endif  // _TEST_UTILITY_WEB_CONTENTTEST_H__
