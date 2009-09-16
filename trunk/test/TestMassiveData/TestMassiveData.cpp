// TestMassiveData.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LogicalLayerTest.h"
#include <boost\test\included\unit_test.hpp>
using namespace boost::unit_test;



boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    framework::master_test_suite().add( BOOST_TEST_CASE(&init_db) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_auto_searchword_clean) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_auto_website_clean) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_whitelisted_dns) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_blasklisted_dns) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_blasklisted_word) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_sulogon) );
    return 0;
}



