#ifndef _TEST_HISTORY_CONTENT_SEARCHKEYWORDUTILTEST_H__
#define _TEST_HISTORY_CONTENT_SEARCHKEYWORDUTILTEST_H__

#include <searchkeywordutil.h>
#include <cppunit/extensions/HelperMacros.h>

class SearchKeywordUtilTest  : public CPPUNIT_NS::TestFixture {
public:
	SearchKeywordUtilTest(void);
	~SearchKeywordUtilTest(void);

	CPPUNIT_TEST_SUITE(SearchKeywordUtilTest);
	CPPUNIT_TEST(testReadSearchWords);
	CPPUNIT_TEST_SUITE_END();

private:
	void testReadSearchWords();
};

#endif  // _TEST_HISTORY_CONTENT_SEARCHKEYWORDUTILTEST_H__