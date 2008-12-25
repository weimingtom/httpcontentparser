// TestUtility.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\timeutilitytest.h"
#include ".\protocolpackettest.h"
#include ".\fdutilitytest.h"
#include ".\httppackettest.h"
#include ".\DNSTEST.h"
#include ".\HTTPResponseHeaderTest .h"
#include ".\strutilitytest.h"
#include ".\webcontenttest.h"
#include ".\ziputilitytest.h"
#include ".\seachpackettest.h"
#include ".\HttpRequestPacketTest.h"
#include ".\buffercallertest.h"
#include ".\replacepackettest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ReplacePacketTest);
CPPUNIT_TEST_SUITE_REGISTRATION(HTTPRequestHeaderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(BufferCallerTest);
CPPUNIT_TEST_SUITE_REGISTRATION(SeachPacketTest);
CPPUNIT_TEST_SUITE_REGISTRATION(HttpRequestPacketTest);
CPPUNIT_TEST_SUITE_REGISTRATION(ZipUtilityTest);
CPPUNIT_TEST_SUITE_REGISTRATION(TimeutilityTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WebContentTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StrUtilityTest);
CPPUNIT_TEST_SUITE_REGISTRATION(HttpRequestPacketTest);
CPPUNIT_TEST_SUITE_REGISTRATION(HTTPPacketTest);
CPPUNIT_TEST_SUITE_REGISTRATION(ProtocolPacketTest);
CPPUNIT_TEST_SUITE_REGISTRATION(FDUtilityTest);
CPPUNIT_TEST_SUITE_REGISTRATION(DNSTest);


int _tmain(int argc, _TCHAR* argv[])
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

