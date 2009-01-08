#ifndef _TEST_FILETERSETTING_IMAGECHECKTEST_H__
#define _TEST_FILETERSETTING_IMAGECHECKTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class ImageCheckTest : public CPPUNIT_NS::TestFixture {
public:
	ImageCheckTest(void);
	~ImageCheckTest(void);

public:
	CPPUNIT_TEST_SUITE(ImageCheckTest);
	CPPUNIT_TEST(TestImageCheck);
	CPPUNIT_TEST_SUITE_END();
private:
	void TestImageCheck();
};

#endif  // _TEST_FILETERSETTING_IMAGECHECKTEST_H__
