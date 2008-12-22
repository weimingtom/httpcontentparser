#ifndef _TESTUTILITY_BUFFERCALLERTEST_H__
#define _TESTUTILITY_BUFFERCALLERTEST_H__

#include <utility/buffercaller.h>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class BufferCallerTest : public CPPUNIT_NS::TestFixture 
{
public:
	BufferCallerTest(void);
	~BufferCallerTest(void);

	CPPUNIT_TEST_SUITE(BufferCallerTest);
	CPPUNIT_TEST(CallTest);
	CPPUNIT_TEST_SUITE_END();
private:
	void CallTest();
};

#endif  // _TESTUTILITY_BUFFERCALLERTEST_H__
