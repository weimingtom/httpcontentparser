#ifndef _TEST_HISTORY_CONTENT_WEBSITEUTILTEST_H__
#define _TEST_HISTORY_CONTENT_WEBSITEUTILTEST_H__

#include <websitesUtil.h>
#include <cppunit/extensions/HelperMacros.h>

class WebsiteUtilTest : public CPPUNIT_NS::TestFixture  {
public:
	WebsiteUtilTest(void);
	~WebsiteUtilTest(void);

public:

	CPPUNIT_TEST_SUITE(WebsiteUtilTest);
	CPPUNIT_TEST(testReadWebisitesWordsFileOper);
	CPPUNIT_TEST(testReadWebisitesEnumerator);
	CPPUNIT_TEST(testReadWebisitesGetNext);
	CPPUNIT_TEST_SUITE_END();

private:
	void testReadWebisitesGetNext();
	void testReadWebisitesEnumerator();
	void testReadWebisitesWordsFileOper();
};

#endif  // _TEST_HISTORY_CONTENT_WEBSITEUTILTEST_H__