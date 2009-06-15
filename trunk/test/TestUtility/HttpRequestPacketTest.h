#ifndef _UTILITY_TEST_HTTPREQUESTPACKETTEST_H__
#define _UTILITY_TEST_HTTPREQUESTPACKETTEST_H__


using namespace CPPUNIT_NS;
class HttpRequestPacketTest : public TestFixture {
public:
	HttpRequestPacketTest(void);
	~HttpRequestPacketTest(void);
	
	CPPUNIT_TEST_SUITE(HttpRequestPacketTest);
	CPPUNIT_TEST(NoteHTTPRequest);
	CPPUNIT_TEST(parsePacket);
	CPPUNIT_TEST(parseMultiPacket);
	CPPUNIT_TEST(miscTest);
	CPPUNIT_TEST_SUITE_END();

protected:
	void parsePacket();
	void parseMultiPacket();
	void NoteHTTPRequest();
	void miscTest();
};

#endif  // _UTILITY_TEST_HTTPREQUESTPACKETTEST_H__