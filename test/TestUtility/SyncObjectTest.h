#ifndef _TESTSYNCOBJECT_SYNCOBJECTTEST_H__
#define _TESTSYNCOBJECT_SYNCOBJECTTEST_H__

class SyncObjectTest  : public CPPUNIT_NS::TestFixture {
public:
	SyncObjectTest(void);
	~SyncObjectTest(void);

	CPPUNIT_TEST_SUITE(SyncObjectTest);
	CPPUNIT_TEST(testCase1);
	CPPUNIT_TEST(testAutoCriticalSection);
	CPPUNIT_TEST(testSysMutexWithName);
	CPPUNIT_TEST(testSysMutexWithoutName);
	CPPUNIT_TEST_SUITE_END();

private:
	void testCase1();
	void testAutoCriticalSection();
	void testSysMutexWithName();
	void testSysMutexWithoutName();
};

#endif  // _TESTSYNCOBJECT_SYNCOBJECTTEST_H__