// TestMassiveData.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <boost\test\included\unit_test.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/function.hpp>
#include <dblogicallayer.h>
using namespace boost::unit_test;

int init_db();
int test_whitelisted_dns();
int test_blasklisted_dns();
int test_blasklisted_word();
int test_auto_clean();
int test_sulogon();

const char * website1 = "www.sina.com";
const char * website2 = "www.baidu.com";
const char * website3 = "www.zhidao.com";
const char * website4 = "www.google.com";
const char * website5 = "www.not.com";
const char * dbfilename = "hello.db";

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] ) {
    framework::master_test_suite().add( BOOST_TEST_CASE(&init_db) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_whitelisted_dns) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_blasklisted_dns) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_blasklisted_word) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_auto_clean) );
    framework::master_test_suite().add( BOOST_TEST_CASE(&test_sulogon) );
    return 0;
}

//=====================
// 超级用户登录记录
int print_info(int type, const char * timestamp) {
    using namespace std;
    cout<<(type == 0? "logon " : "logoff ") << timestamp<<endl;
    return 0;
}

int test_sulogon() {
    su_user_logon();
    su_user_logon();

    su_user_logoff();
    su_user_logoff();
    su_user_logoff();

    enum_su_logon(&print_info);

    return 0;
}

// 自从清理
int test_auto_clean() {
    // 设置环境
    using boost::date_time::date;
    using boost::date_time::day_clock;
    using boost::date_time::day;

/*    date d = day_clock::universal_day();
    insert_website_visited("word1", d.);*/

    return 0;
}


// 检测黑名单相关的函数
int test_blasklisted_word() {
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

int test_whitelisted_dns() {
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

int test_blasklisted_dns() {
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
// 删除数据文件，创建表等
int init_db() {
    TCHAR workdir[MAX_PATH], dbpath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, workdir);
    _sntprintf(dbpath, MAX_PATH, TEXT("%s\\%s"), workdir, dbfilename);
    DeleteFile(dbpath);
    int a = GetLastError();
    load_db(dbfilename);

    initialize_db();
    return 0;
}

