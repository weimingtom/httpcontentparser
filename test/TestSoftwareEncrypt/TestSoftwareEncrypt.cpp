// TestSoftwareEncrypt.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BaseEncryptTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BaseEncryptTest);

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

