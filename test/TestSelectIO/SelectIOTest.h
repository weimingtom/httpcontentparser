#ifndef _TEST_SELECTIO_SELECTIO_TEST_H__
#define _TEST_SELECTIO_SELECTIO_TEST_H__

#include <cppunit/extensions/HelperMacros.h>


class SelectIOTest : public CPPUNIT_NS::TestFixture {
public:
	SelectIOTest(void);
	~SelectIOTest(void);

public: 
	CPPUNIT_TEST_SUITE(SelectIOTest);
	CPPUNIT_TEST(testCloseSocket);
	CPPUNIT_TEST(testMax);
	CPPUNIT_TEST(testConstantPackets);
	CPPUNIT_TEST(testRemovePacket);
	CPPUNIT_TEST(testPostSelect);
	CPPUNIT_TEST(testZeroChunk);
	CPPUNIT_TEST(testMulitPacket);
	CPPUNIT_TEST(testInvalidateHTTPPacket);
	CPPUNIT_TEST(testCopyBuffer);
	CPPUNIT_TEST(testPreSelect);
	CPPUNIT_TEST_SUITE_END();

private:
	void testCloseSocket();
	void testRemovePacket();
	void testConstantPackets();
	void testMax();
	void testZeroChunk();
	void testMulitPacket();
	void testPreSelect();
	void testInvalidateHTTPPacket();
	void testPostSelect();
	void testCopyBuffer();
};

#endif  // _TEST_SELECTIO_SELECTIO_TEST_H__
