#ifndef _TESTAPPUTILITY_FILEINFOTEST_H__
#define _TESTAPPUTILITY_FILEINFOTEST_H__

class FileInfoTest   : public CPPUNIT_NS::TestFixture {
public:
	FileInfoTest(void);
	~FileInfoTest(void);

public:
	CPPUNIT_TEST_SUITE(FileInfoTest);
	CPPUNIT_TEST(testSVCHOST);
	CPPUNIT_TEST_SUITE_END();

private:
	void testSVCHOST();
};

#endif  // _TESTAPPUTILITY_FILEINFOTEST_H__