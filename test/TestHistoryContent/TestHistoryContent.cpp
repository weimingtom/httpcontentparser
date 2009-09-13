// TestHistoryContent.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\searchkeywordutiltest.h"
#include ".\websiteutiltest.h"
#include <boost\test\included\unit_test.hpp>
using namespace boost::unit_test;

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    framework::master_test_suite().add( BOOST_TEST_CASE(&testReadWebisitesGetNext) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testReadWebisitesEnumerator) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testReadWebisitesWordsFileOper) );

    framework::master_test_suite().add( BOOST_TEST_CASE(&testReadSearcEnumerator) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testReadSearcGetNext) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testReadSearchWordsFileOper) );
    return 0;
}
