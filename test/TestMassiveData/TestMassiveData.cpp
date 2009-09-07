// TestMassiveData.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <boost\test\included\unit_test.hpp>
#include <dblogicallayer.h>
using namespace boost::unit_test;

int init_db();
int check_wdns();

const char * website1 = "www.sina.com";
const char * website2 = "www.baidu.com";
const char * website3 = "www.zhidao.com";
const char * website4 = "www.google.com";



boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    load_db("hello.db");
    init_db();

    framework::master_test_suite().add( BOOST_TEST_CASE(&init_db) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&check_wdns) );
    return 0;
}


int check_wdns() {
    insert_white_dns(website1);
    insert_white_dns(website2);
    insert_white_dns(website3);
    insert_white_dns(website4);

    BOOST_CHECK(check_white_dns(website1));
    BOOST_CHECK(check_white_dns(website2));
    BOOST_CHECK(check_white_dns(website3));
    BOOST_CHECK(check_white_dns(website4));

    return 0;
}

// 初始化数据库
int init_db() {
    initialize_db();
    return 0;
}

