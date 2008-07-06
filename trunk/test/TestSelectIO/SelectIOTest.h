#ifndef _TEST_SELECTIO_SELECTIO_TEST_H__
#define _TEST_SELECTIO_SELECTIO_TEST_H__

#include <cppunit/extensions/HelperMacros.h>


class SelectIOTest : public CPPUNIT_NS::TestFixture {
public:
	SelectIOTest(void);
	~SelectIOTest(void);

public: 
	CPPUNIT_TEST_SUITE(SelectIOTest);
	CPPUNIT_TEST(testPreSelect);
	CPPUNIT_TEST(testPostSelect);
	CPPUNIT_TEST_SUITE_END();

private:
	void testPreSelect();
	void testPostSelect();
};

#endif  // _TEST_SELECTIO_SELECTIO_TEST_H__
