// TestMassiveData.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <boost\test\included\unit_test.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/time.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp> 
using namespace boost::unit_test;

int init_db();
int test_whitelisted_dns();
int test_blasklisted_dns();
int test_blasklisted_word();
int test_auto_searchword_clean();
int test_auto_website_clean();
int test_sulogon();

const char * website1 = "www.sina.com";
const char * website2 = "www.baidu.com";
const char * website3 = "www.zhidao.com";
const char * website4 = "www.google.com";
const char * website5 = "www.not.com";
const char * dbfilename = "hello.db";
const char * memdb = ":memory:";
const char * word = "word";

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

namespace {
std::string format_ptime_to_timestamp( boost::posix_time::ptime & pt) {
    boost::format formatter("%04d-%02d-%02d %02d:%02d:%02d ");

    formatter % pt.date().year() % pt.date().month() % pt.date().day() 
        % pt.time_of_day().hours() % pt.time_of_day().minutes() % pt.time_of_day().seconds();
    return formatter.str();
}

int print_words(const char * data,  const char * timestamp) {
    using namespace std;
    cout<<data << "  "<< timestamp<<endl;
    return 0;
}

int print_info(int type, const char * timestamp) {
    using namespace std;
    cout<<(type == 0? "logon " : "logoff ") << timestamp<<endl;
    return 0;
}

};

int test_auto_website_clean() {
    // 设置环境
    using namespace boost::posix_time;
    using namespace boost::gregorian;
    using namespace boost::date_time;

    using boost::posix_time::ptime;
    using boost::date_time::second_clock;
    boost::posix_time::ptime pt(second_clock<ptime>::universal_time());
    boost::posix_time::time_duration td(24, 0, 0);
    // 为最近30天，每天插入两个词汇并设置不同的auto_clear day
    // 对结果进行分析

    int cnt = 0;
    for (int i = 0; i < 30; ++i)  {
        pt -= td;
        BOOST_CHECK(0 == insert_word_searched(word, "google", format_ptime_to_timestamp(pt).c_str()));
        cnt ++;
    }

    int count = 0;
    BOOST_CHECK(0 ==get_word_searched_count(&count));
    BOOST_CHECK(count == cnt);

   // enum_website_visited(&print_words);

    int cnt2 = 1;
    for (int i = 30; i > 0; --i) {
        // 自动清理
        BOOST_CHECK(0 == auto_clean_wordsearched_list(i));
        BOOST_CHECK(0 ==get_word_searched_count(&count));
        BOOST_CHECK(count == (cnt - cnt2));
        cnt2++;
    }

    return 0;
}

// 自从清理
int test_auto_searchword_clean() {
    // 设置环境
    using namespace boost::posix_time;
    using namespace boost::gregorian;
    using namespace boost::date_time;

    using boost::posix_time::ptime;
    using boost::date_time::second_clock;
    boost::posix_time::ptime pt(second_clock<ptime>::universal_time());
    boost::posix_time::time_duration td(24, 0, 0);
    // 为最近30天，每天插入两个词汇并设置不同的auto_clear day
    // 对结果进行分析

    int cnt = 0;
    for (int i = 0; i < 30; ++i)  {
        pt -= td;
        BOOST_CHECK(0 == insert_website_visited(word, format_ptime_to_timestamp(pt).c_str()));
        cnt ++;
    }

    int count = 0;
    BOOST_CHECK(0 ==get_website_visited_count(&count));
    BOOST_CHECK(count == cnt);

   // enum_website_visited(&print_words);

    int cnt2 = 1;
    for (int i = 30; i > 0; --i) {
        // 自动清理
        BOOST_CHECK(0 == auto_clean_website_list(i));
        BOOST_CHECK(0 ==get_website_visited_count(&count));
        BOOST_CHECK(count == (cnt - cnt2));
        cnt2++;
    }

    return 0;
}

//=====================
// 超级用户登录记录

int test_sulogon() {
    su_user_logon();
    su_user_logon();

    su_user_logoff();
    su_user_logoff();
    su_user_logoff();

    enum_su_logon(print_info);

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
    load_db(memdb);

    initialize_db();
    return 0;
}

