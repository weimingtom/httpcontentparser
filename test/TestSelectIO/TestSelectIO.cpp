// TestSelectIO.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\selectiotest.h"
#include ".\buffercomcallertest.h"
#include ".\serviceutilitytest.h"
#include ".\dnsmapTest.h"
#include <boost\test\included\unit_test.hpp>

using namespace boost::unit_test;

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    // BufferCOMCallerTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&WebContentRecordCallerTest) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&WebContentCheckCallerTest) );

    //DNSMapTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestDNSMap) );

    // SelectIOTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testCloseSocket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testRemovePacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testConstantPackets) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testMax) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testZeroChunk) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testMulitPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testPreSelect) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testInvalidateHTTPPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testPostSelect) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testCopyBuffer) );

    // Search Rules
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestCheckSeachRule) );
    return 0;
}
