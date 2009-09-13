// TestSoftwareEncrypt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BaseEncryptTest.h"
#include ".\installdatetest.h"
#include ".\licenseinfotest.h"
#include <softwareEncrypt\serialNumber.h>
#include <softwareEncrypt\LicenseInfo.h>
#include <softwareEncrypt\baseEncrypt.h>
#include <softwareencrypt\installdate.h>
#include <softwareStatus.h>
#include <boost\test\included\unit_test.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/time.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp>

// 在测试用例当中原有设置可能被修改
// 此类是为了在程序退出时能够恢复状态
namespace {
class test_unit_restore {
public:
    test_unit_restore() {
	    rawdate = software_encrypt::getInstallDataTime();
    }

    ~test_unit_restore() {
        tm t =	to_tm(rawdate);
        FILETIME ft;
        SYSTEMTIME st = st_from_tm(t);
        SystemTimeToFileTime(&st, &ft);
        software_encrypt::internal_utility::setInstallDateFile(ft);
        software_encrypt::internal_utility::setInstallDataOnRegistry(ft);
        software_encrypt::internal_utility::setInstallDateInWin(ft);
    }

private:
    boost::posix_time::ptime rawdate; 
} an_test_store_;
}


using namespace boost::unit_test;

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestInstallDateItem) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestGetInstallDateFromRegistry) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestGetInstallDateFromFile) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestGetInstallDateFromWin) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testSNStored) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testReg) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&testInstallDate) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&TestBaseEncry) );
    return 0;
}

