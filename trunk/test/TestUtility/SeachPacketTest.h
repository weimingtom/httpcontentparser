#ifndef _UTILITY_SEACHPACKETTEST_H__
#define _UTILITY_SEACHPACKETTEST_H__

using namespace CPPUNIT_NS;

class SeachPacketTest : public TestFixture {
public:
	SeachPacketTest(void);
	~SeachPacketTest(void);

	CPPUNIT_TEST_SUITE(SeachPacketTest);
	CPPUNIT_TEST(getContentTest);
	CPPUNIT_TEST(baiduTest);
	CPPUNIT_TEST(googleTest);
	CPPUNIT_TEST(yahooTest);
	CPPUNIT_TEST_SUITE_END();
protected:
	void getContentTest();
	void baiduTest();
	void googleTest();
	void yahooTest();
};

#endif  // _UTILITY_SEACHPACKETTEST_H__