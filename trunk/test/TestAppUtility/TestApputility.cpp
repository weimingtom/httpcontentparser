// TestSysutility.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\appinstallvaltest.h"
#include ".\AppUtilitytest.h"
#include ".\shellexttest.h"
#include ".\fileinfotest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ShellExtTest);
CPPUNIT_TEST_SUITE_REGISTRATION(FileInfoTest);
CPPUNIT_TEST_SUITE_REGISTRATION(AppInstallValTest);
CPPUNIT_TEST_SUITE_REGISTRATION(AppUtilityTest);

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
