#ifndef _TEST_HISTORY_CONTENT_SEARCHKEYWORDUTILTEST_H__
#define _TEST_HISTORY_CONTENT_SEARCHKEYWORDUTILTEST_H__

#include <searchkeywordutil.h>
#include <cppunit/extensions/HelperMacros.h>

class SearchKeywordUtilTest  : public CPPUNIT_NS::TestFixture {
public:
	SearchKeywordUtilTest(void);
	~SearchKeywordUtilTest(void);

	CPPUNIT_TEST_SUITE(SearchKeywordUtilTest);
	CPPUNIT_TEST(testReadSearchWordsFileOper);
	CPPUNIT_TEST(testReadSearcEnumerator);
	CPPUNIT_TEST(testReadSearcGetNext);
	CPPUNIT_TEST_SUITE_END();

private:
	void testReadSearcEnumerator();
	void testReadSearcGetNext();
	void testReadSearchWordsFileOper();
};

#endif  // _TEST_HISTORY_CONTENT_SEARCHKEYWORDUTILTEST_H__