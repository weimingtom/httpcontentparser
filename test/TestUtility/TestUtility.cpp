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
#include ".\syncobjecttest.h"

#include <boost\test\included\unit_test.hpp>
using namespace boost::unit_test;

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    // BufferCallerTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&CallTest) );

    // HTTPPacketTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestGetMainServName) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestContainIPinDNS) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestValidateIPWithEnd) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestvalidateIP) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&GetMultHostName) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&GetDNS) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&GetMainNameWithPort) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&GetMainNameTest) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&BeginWWWTest) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&GetMainNameFromBrowseAddresss) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&GetMainNameFromBrowseAddressswithProto) );

    // FDUtilityTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testFDAdd) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testFDSet) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testFDDel) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testNone) );

    // HTTPPacketTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testActuallyPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testConnectionState) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testZeorLengthPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testNoContentHeader) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testAdd0LengthPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testZeroChunk) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testNoLengthSepecified) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testNoContentPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testSeriesPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testWrongHeader) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testChunk) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testAddSinglePacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testAddSeriesPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testRawPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testNoContentChunk) );

    // HttpRequestPacketTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&parsePacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&parseMultiPacket) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&NoteHTTPRequest) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&miscTest) );

    // HTTPRequestHeaderTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testHTTPHeaderParsed) );

    // ProtocolPacketTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testGetBytesCanRead) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testSeekRead) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testSeekWrite) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testWrite) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testLoopRead) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testRead) );

    // ReplacePacketTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testNewPacket) );

    // SeachPacketTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&getContentTest) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&baiduTest) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&googleTest) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&yahooTest) );

    // StrUtilityTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestSplitString) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&Teststrnstr) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&Test_extract_string) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&Test_remove_after) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestEndWith) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestToLower) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestToUpper) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&Test_extUTF8FromStr) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&Test_utf8ToDBCS) );

    // TimeutilityTest
    framework::master_test_suite().add( BOOST_TEST_CASE(&testMintueTimespan) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testTmfromString) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testUSFormatTime) );

    // WebContentTest
    framework::master_test_suite().add( BOOST_TEST_CASE(testFFFF) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testImageType) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testTextType) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&textOtherTypes) );

    // ZipUtilityTest
    // Some memory leak
    // framework::master_test_suite().add( BOOST_TEST_CASE(&testZlibUtility) );

    // SyncObjectTest
    framework::master_test_suite().add( BOOST_TEST_CASE(testCase1) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testAutoCriticalSection) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testSysMutexWithName) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testSysMutexWithoutName) );

    return 0;
}