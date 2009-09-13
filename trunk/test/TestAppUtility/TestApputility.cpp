// TestSysutility.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\appinstallvaltest.h"
#include ".\AppUtilitytest.h"
#include ".\fileinfotest.h"
#include <boost\test\included\unit_test.hpp>

using namespace boost::unit_test;

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    framework::master_test_suite().add( BOOST_TEST_CASE(&testShouldRepair) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testRunInCOM) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testRunInSPI) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testRunInNone) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testServieInstall) );

    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetMainUIName) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetInstallPath) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetAppConfigFilename) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetImageDirectory) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetPageDirectory) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetRecordConfigfile) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetFileNameDir) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testRegisterOper) );

    framework::master_test_suite().add( BOOST_TEST_CASE(&testSVCHOST) );

    return 0;
}
