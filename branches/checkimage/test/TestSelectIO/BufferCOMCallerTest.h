#ifndef _TESTSELECTIO_BUFFER_COM_CALLER_TEST_H__
#define _TESTSELECTIO_BUFFER_COM_CALLER_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class BufferCOMCallerTest : public CPPUNIT_NS::TestFixture  {
public:
	BufferCOMCallerTest(void);
	~BufferCOMCallerTest(void);

	CPPUNIT_TEST_SUITE(BufferCOMCallerTest);
	CPPUNIT_TEST(WebContentRecordCallerTest);
	CPPUNIT_TEST(WebContentCheckCallerTest);
	CPPUNIT_TEST_SUITE_END();
private:
	void WebContentRecordCallerTest();
	void WebContentCheckCallerTest();
};

#endif  // _TESTSELECTIO_BUFFER_COM_CALLER_TEST_H__
