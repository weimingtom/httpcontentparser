// TestFilterSetting.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\filtersettingtest.h"
#include ".\iauthorizetest.h"
#include ".\eyecaretest.h"
#include ".\iaccessnetworktest.h"
#include ".\iseachruletest.h"
#include ".\imagechecktest.h"
#include <boost\test\included\unit_test.hpp>
using namespace boost::unit_test;

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    // IAccessNetworkTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSetAndGetBlockTime) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestTwoModel) );

    // FilterSettingTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestcheckDNS) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestaddBlackDNS) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestPassedWhiteDNS) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestEnableWhiteAndPassWhite) );

    // IAuthorizeTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testCheckPassword) );

    // ImageCheckTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestImageCheck) );

    // EyecareTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&getTimeLeft) );

    // ISeachRuleTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestISeachRule) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestRemove) );
    return 0;
}
