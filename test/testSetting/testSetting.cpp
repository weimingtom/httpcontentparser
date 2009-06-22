// testSetting.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\dnssettingtest.h"
#include ".\authorizetest.h"
#include ".\eyecaretest.h"
#include ".\calculargraphtest.h"
#include ".\contentsettingtest.h"
#include ".\configreadertest.h"
#include ".\searchruletest.h"
#include ".\onlinehoursettingtest.h"
#include ".\webhistoryrecordtest.h"
#include ".\autocleantest.h"
#include ".\hotkeysettingtest.h"
#include ".\appcontroltest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CalculargraphTest);
CPPUNIT_TEST_SUITE_REGISTRATION(EyecareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(DNSSettingTest);
CPPUNIT_TEST_SUITE_REGISTRATION(AppControlTest);
CPPUNIT_TEST_SUITE_REGISTRATION(HotkeySettingTest);
CPPUNIT_TEST_SUITE_REGISTRATION(AutocleanTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WebHistoryRecordTest);
CPPUNIT_TEST_SUITE_REGISTRATION(OnlineHourSettingTest);
CPPUNIT_TEST_SUITE_REGISTRATION(SearchRuleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(ConfigReaderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(ContentSettingTest);
CPPUNIT_TEST_SUITE_REGISTRATION(AuthorizeTest);

int _tmain(int argc, _TCHAR* argv[]) {
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
