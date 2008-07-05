#ifndef _UTILITY_TEST_HTTPPACKETTEST_H_
#define _UTILITY_TEST_HTTPPACKETTEST_H_

// ≤ª∫√≤‚ ‘∞°£°....

using namespace CPPUNIT_NS;
class HTTPPacketTest : public TestFixture {
public:
	HTTPPacketTest(void);
	~HTTPPacketTest(void);

	CPPUNIT_TEST_SUITE(HTTPPacketTest);
	CPPUNIT_TEST(testNoContentPacket);
	CPPUNIT_TEST(testSeriesPacket);
	CPPUNIT_TEST(testHTTPHeaderParsed);
	CPPUNIT_TEST(testChunk);
	CPPUNIT_TEST(testWrongHeader);
	CPPUNIT_TEST(testRawPacket);
	CPPUNIT_TEST(testAddSinglePacket);
	CPPUNIT_TEST(testAddSeriesPacket);
	
	CPPUNIT_TEST_SUITE_END();
protected:
	void testNoContentPacket();
	void testSeriesPacket();
	void testWrongHeader();
	void testChunk();
	void testAddSinglePacket();
	void testAddSeriesPacket();
	void testHTTPHeaderParsed();
	void testRawPacket();
};

#endif  // _UTILITY_TEST_HTTPPACKETTEST_H_
