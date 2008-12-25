#ifndef _UTILITY_TEST_HTTPREQUESTHEADERTEST_H_
#define _UTILITY_TEST_HTTPREQUESTHEADERTEST_H_

#include <cppunit\extensions\HelperMacros.h>
#include <cppunit\ui\text\TestRunner.h>
#include <cppunit\extensions\TestFactoryRegistry.h>
#include <cppunit\TestResult.h>
#include <cppunit\TestResultCollector.h>
#include <cppunit\BriefTestProgressListener.h>
#include <cppunit\CompilerOutputter.h> 

using namespace CPPUNIT_NS;
class HTTPRequestHeaderTest : public TestFixture {
public:
	HTTPRequestHeaderTest(void);
	~HTTPRequestHeaderTest(void);

	CPPUNIT_TEST_SUITE(HTTPRequestHeaderTest);
	CPPUNIT_TEST(testHTTPHeaderParsed);
	CPPUNIT_TEST_SUITE_END();

private:
	void testHTTPHeaderParsed();
};

#endif // _UTILITY_TEST_HTTPREQUESTHEADERTEST_H_