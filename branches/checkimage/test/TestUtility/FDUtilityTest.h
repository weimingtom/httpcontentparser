#pragma once

// ¸ºÔð²âÊÔ
using namespace CPPUNIT_NS;
class FDUtilityTest : public TestFixture {
public:
	FDUtilityTest(void);
	~FDUtilityTest(void);

	CPPUNIT_TEST_SUITE(FDUtilityTest);
	CPPUNIT_TEST(testFDAdd);
	CPPUNIT_TEST(testFDSet);
	CPPUNIT_TEST(testFDDel);
	CPPUNIT_TEST(testFDDel);
	CPPUNIT_TEST_SUITE_END();
private:
	void testFDAdd();
	void testFDSet();
	void testFDDel();
	void testNone();
};
