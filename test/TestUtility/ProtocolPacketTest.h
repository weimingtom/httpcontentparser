#ifndef _TEST_UTILITY_PROTOCOL_PACKET_TEST_H__
#define _TEST_UTILITY_PROTOCOL_PACKET_TEST_H__

using namespace CPPUNIT_NS;
class ProtocolPacketTest : public TestFixture {
public:
	ProtocolPacketTest(void);
	~ProtocolPacketTest(void);

	CPPUNIT_TEST_SUITE(ProtocolPacketTest);
	CPPUNIT_TEST(testGetBytesCanRead);
	CPPUNIT_TEST(testWrite);
	CPPUNIT_TEST(testSeekWrite);
	CPPUNIT_TEST(testSeekRead);
	CPPUNIT_TEST(testLoopRead);
	CPPUNIT_TEST(testRead);
	CPPUNIT_TEST_SUITE_END();
private:
	void testGetBytesCanRead();
	void testSeekRead();
	void testSeekWrite();
	void testWriteOnStack();
	void testWrite();
	void testLoopRead();
	void testRead();
};

#endif  // _TEST_UTILITY_PROTOCOL_PACKET_TEST_H__
