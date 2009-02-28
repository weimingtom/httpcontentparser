#ifndef _TEST_UTILITY_TIMEUTILITYTEST_H__
#define _TEST_UTILITY_TIMEUTILITYTEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <utility/timeutility.h>
using namespace CPPUNIT_NS;

class TimeutilityTest : public TestFixture {
public:
	TimeutilityTest(void);
	~TimeutilityTest(void);

public:
	CPPUNIT_TEST_SUITE(TimeutilityTest);
	CPPUNIT_TEST(testMintueTimespan);
	CPPUNIT_TEST(testTmfromString);
	CPPUNIT_TEST(testUSFormatTime);
	CPPUNIT_TEST_SUITE_END();
private:
	void testMintueTimespan();
	void testTmfromString();
	void testUSFormatTime();
};

#endif  // _TEST_UTILITY_TIMEUTILITYTEST_H__