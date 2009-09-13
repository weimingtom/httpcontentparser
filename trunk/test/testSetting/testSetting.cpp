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
#include <boost\test\included\unit_test.hpp>


using namespace boost::unit_test;

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    // AppControlTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testAppConrol) );

    // AuthorizeTest 
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestCheckPassword) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestChangePassword) );

    // AutocleanTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testAutoclean) );

    // CalculargraphTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestForceswitch) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSetASmallerTime) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestCulargraph) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testCalarStopTimer) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testMulitSetTimeLeft) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testMultiStopTimer) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestMultiCalculargraph) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSetTimeEscape) );

    // ConfigReaderTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestReadFromFile) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSaveFile) );

    // ContentSettingTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestEnableCheck) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestNeedCheck) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestTwoModel) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestTwoWrong) );

    // DNSSettingTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testCheck) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testFuzzeCheck) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testTwoModels) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testJustPassedWhiteDNS) );

    // EyecareTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestPassword) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSwitchState) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestTimeSetting) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSetLeft) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestMultiModelSwitch) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestAfterModelSwitch) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestModelsInParentAndChild) );

    // HotkeySettingTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testHotkey) );

    // OnlineHourSettingTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestOnlineHour) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestTowModeSwitched) );

    // SearchRuleTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSeachRuleSetting) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSeachEnabled) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestParentChildMode) );

    // WebHistoryRecordTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestDefault) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestRegular) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestEnable) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestParentMode) );
    return 0;
}