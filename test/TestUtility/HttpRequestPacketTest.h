#ifndef _UTILITY_TEST_HTTPREQUESTPACKETTEST_H__
#define _UTILITY_TEST_HTTPREQUESTPACKETTEST_H__


using namespace CPPUNIT_NS;
class HttpRequestPacketTest : public TestFixture {
public:
	HttpRequestPacketTest(void);
	~HttpRequestPacketTest(void);

	
	CPPUNIT_TEST_SUITE(HttpRequestPacketTest);
	CPPUNIT_TEST(parsePacket);
	CPPUNIT_TEST_SUITE_END();

protected:
	void parsePacket();
};

#endif  // _UTILITY_TEST_HTTPREQUESTPACKETTEST_H__