#ifndef _TESTSETTING_CONTENTSETTINGTEST_H__
#define _TESTSETTING_CONTENTSETTINGTEST_H__

using namespace CPPUNIT_NS;
class ContentSettingTest  : public TestFixture {
public:
	ContentSettingTest(void);
	~ContentSettingTest(void);
public:
	CPPUNIT_TEST_SUITE(ContentSettingTest);
	CPPUNIT_TEST(TestEnableCheck);
	CPPUNIT_TEST(TestNeedCheck);
	CPPUNIT_TEST(TestTwoModel);
	CPPUNIT_TEST(TestTwoWrong);
	CPPUNIT_TEST_SUITE_END();

private:
	void TestEnableCheck();
	void TestNeedCheck();
	void TestTwoModel();
	void TestTwoWrong();
};

#endif  // _TESTSETTING_CONTENTSETTINGTEST_H__
