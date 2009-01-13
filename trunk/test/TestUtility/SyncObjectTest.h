#ifndef _TESTSYNCOBJECT_SYNCOBJECTTEST_H__
#define _TESTSYNCOBJECT_SYNCOBJECTTEST_H__

class SyncObjectTest  : public CPPUNIT_NS::TestFixture {
public:
	SyncObjectTest(void);
	~SyncObjectTest(void);

	CPPUNIT_TEST_SUITE(SyncObjectTest);
	CPPUNIT_TEST(testCase1);
	CPPUNIT_TEST(testCase2);
	CPPUNIT_TEST_SUITE_END();

private:
	void testCase2();
	void testCase1();
};

#endif  // _TESTSYNCOBJECT_SYNCOBJECTTEST_H__