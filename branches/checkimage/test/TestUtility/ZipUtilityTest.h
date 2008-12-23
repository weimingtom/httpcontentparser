#ifndef _UTILITYTEST_ZIPUTILITYTEST_H__
#define _UTILITYTEST_ZIPUTILITYTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class ZipUtilityTest  : public CPPUNIT_NS::TestFixture {
public:
	ZipUtilityTest(void);
	~ZipUtilityTest(void);

	CPPUNIT_TEST_SUITE(ZipUtilityTest);
	CPPUNIT_TEST(testZlibUtility);
	CPPUNIT_TEST_SUITE_END();

public:
	void testZlibUtility();
};

#endif  // _UTILITYTEST_ZIPUTILITYTEST_H__
