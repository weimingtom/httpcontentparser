// TestMassiveData.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <boost\test\included\unit_test.hpp>
#include <dblogicallayer.h>
using namespace boost::unit_test;

int init_db();
int check_whitelisted_dns();
int check_blasklisted_dns();
int check_blasklisted_word();

const char * website1 = "www.sina.com";
const char * website2 = "www.baidu.com";
const char * website3 = "www.zhidao.com";
const char * website4 = "www.google.com";
const char * website5 = "www.not.com";
const char * dbfilename = "hello.db";

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    DeleteFile(dbfilename);
    load_db(dbfilename);
    init_db();

    framework::master_test_suite().add( BOOST_TEST_CASE(&check_whitelisted_dns) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&check_blasklisted_dns) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&check_blasklisted_word) );
    return 0;
}

int check_blasklisted_word() {
    const char * word1 = "word1";
    const char * word2 = "word2";
    const char * word3 = "word3";
    const char * word4 = "word4";
    const char * engine1 = "google";
    const char * engine2 = "baidu";

    BOOST_CHECK(0 == insert_black_searchword(word1, engine1));
    BOOST_CHECK(0 == insert_black_searchword(word2, engine1));
    BOOST_CHECK(0 == insert_black_searchword(word3, engine2));
    BOOST_CHECK(0 == insert_black_searchword(word4, engine2));

    BOOST_CHECK(true  == check_black_searchword(word1, engine1));
    BOOST_CHECK(true  == check_black_searchword(word2, engine1));
    BOOST_CHECK(false  == check_black_searchword(word3, engine1));
    BOOST_CHECK(false  == check_black_searchword(word4, engine1));
    BOOST_CHECK(false  == check_black_searchword(word1, engine2));
    BOOST_CHECK(false  == check_black_searchword(word2, engine2));
    BOOST_CHECK(true  == check_black_searchword(word3, engine2));
    BOOST_CHECK(true  == check_black_searchword(word4, engine2));
    

    BOOST_CHECK(0 == del_black_searchword(word1, engine1));
    BOOST_CHECK(0 == del_black_searchword(word3, engine2));

    BOOST_CHECK(false  == check_black_searchword(word1, engine1));
    BOOST_CHECK(true  == check_black_searchword(word2, engine1));
    BOOST_CHECK(false  == check_black_searchword(word3, engine1));
    BOOST_CHECK(false  == check_black_searchword(word4, engine1));
    BOOST_CHECK(false  == check_black_searchword(word1, engine2));
    BOOST_CHECK(false  == check_black_searchword(word2, engine2));
    BOOST_CHECK(false  == check_black_searchword(word3, engine2));
    BOOST_CHECK(true  == check_black_searchword(word4, engine2));

    return 0;
}

int check_whitelisted_dns() {
    BOOST_CHECK(0 == insert_white_dns(website1));
    BOOST_CHECK(0 == insert_white_dns(website2));
    BOOST_CHECK(0 == insert_white_dns(website3));
    BOOST_CHECK(0 == insert_white_dns(website4));


    BOOST_CHECK(true  == check_white_dns(website1));
    BOOST_CHECK(true  == check_white_dns(website2));
    BOOST_CHECK(true  == check_white_dns(website3));
    BOOST_CHECK(true  == check_white_dns(website4));

    // 移除
    BOOST_CHECK(0 == del_white_dns(website1));
    BOOST_CHECK(0 == del_white_dns(website2));
    BOOST_CHECK(0 == del_white_dns(website5));

    BOOST_CHECK(false == check_white_dns(website1));
    BOOST_CHECK(false == check_white_dns(website2));
    BOOST_CHECK(true == check_white_dns(website3));
    BOOST_CHECK(true  == check_white_dns(website4));

    return 0;
}

int check_blasklisted_dns() {
    BOOST_CHECK(0 == insert_black_dns(website1));
    BOOST_CHECK(0 == insert_black_dns(website2));
    BOOST_CHECK(0 == insert_black_dns(website3));
    BOOST_CHECK(0 == insert_black_dns(website4));


    BOOST_CHECK(true  == check_black_dns(website1));
    BOOST_CHECK(true  == check_black_dns(website2));
    BOOST_CHECK(true  == check_black_dns(website3));
    BOOST_CHECK(true  == check_black_dns(website4));

    // 移除
    BOOST_CHECK(0 == del_black_dns(website1));
    BOOST_CHECK(0 == del_black_dns(website2));
    BOOST_CHECK(0 == del_black_dns(website5));

    BOOST_CHECK(false == check_black_dns(website1));
    BOOST_CHECK(false == check_black_dns(website2));
    BOOST_CHECK(true == check_black_dns(website3));
    BOOST_CHECK(true  == check_black_dns(website4));

    return 0;
}


// 初始化数据库
int init_db() {
    initialize_db();
    return 0;
}

