#include "stdafx.h"
#include "dblogicallayer.h"
#include "sqliteutility.h"

sqlite_connection g_conn_;

namespace {
int enum_data(const char * sql, boost::function<int (const char *, const char *, const char *)>& enum_fun) ;
 int enum_data(const char * sql, boost::function<int (const char*, const char *)> & enum_fun);
 int enum_data(const char * sql, boost::function<int (int, const char *)> & enum_fun) ;
 int enum_data(const char * sql, boost::function<int ( const char *)> & enum_fun);
};

const int  LOG_ON = 0;
const int  LOG_OFF = 1;

int load_db(const char * dbname) {
    return g_conn_.open(dbname);
}

int verify_db() {
    return 0;
}

int initialize_db() {
    g_conn_.execute_no_result("create table wdns      (website char(50), visit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP )");
    g_conn_.execute_no_result("create table bdns      (website char(50), visit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP )");
    g_conn_.execute_no_result("create table bwords (word char(50),  engine char (50), visit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP )");

    // 创建具有历史记录的表
    g_conn_.execute_no_result("create table wordhistory  (word char(50), engine char (50), visit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP )");
    g_conn_.execute_no_result("create table webhistory  (website char(50),  visit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP )");

    // 超级用户登录
    g_conn_.execute_no_result("create table appcontrol  (appname char(255))");

    // 超级用户登录
    g_conn_.execute_no_result("create table sulogon  (logon_type integer,  logon_tm TIMESTAMP DEFAULT CURRENT_TIMESTAMP )");
    return 0;
}

// 超级用户登录
int su_user_logon() {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into sulogon(logon_type) values (%d)", LOG_ON);
    return g_conn_.execute_no_result(buffer);
}
int su_user_logoff() {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into sulogon(logon_type) values (%d)", LOG_OFF);
    return g_conn_.execute_no_result(buffer);
}

// 返回
int get_website_visited_count(int * count) {
    return get_sql_select_count(&g_conn_, "select website from webhistory", count);
}
int get_word_searched_count(int * count) {
    return get_sql_select_count(&g_conn_, "select word from wordhistory", count);
}

//====================================
//  枚举函数
int enum_website_visited(boost::function<int (const char*, const char *)> enum_fun) {
    return enum_data("select website, visit_time from webhistory", enum_fun);
}
int enum_word_searched(boost::function<int  (const char*, const char *, const char * )> enum_fun) {
    return enum_data("select word, engine, visit_time from wordhistory", enum_fun);
}

int enum_su_logon(boost::function<int (int, const char *)> enum_fun) {
    return enum_data( "select logon_type, logon_tm from sulogon", enum_fun);
}

int enum_white_dns(boost::function<int ( const char*)> enum_fun) {
     return enum_data( "select website from wdns", enum_fun);
}
int enum_black_dns(boost::function<int( const char*)> enum_fun) {
     return enum_data( "select website  from bdns", enum_fun);
}
int enum_blacksearch_word(boost::function<int (const char*, const char *)> enum_fun) {
    return enum_data( "select word, engine, visit_time from bwords", enum_fun);
}
// 自动清理
int auto_clean_website_list(const int days) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "delete from webhistory where julianday('now') -  julianday(visit_time)> %d", days);
    return g_conn_.execute_no_result(buffer);
}
int auto_clean_wordsearched_list(const int days) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "delete from wordhistory where julianday('now') -  julianday(visit_time)> %d", days);
    return g_conn_.execute_no_result(buffer);
}

int insert_website_visited(const char*  website) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into webhistory(website) values('%s')", website);
    return g_conn_.execute_no_result(buffer);
}

int insert_website_visited(const char * website, const char * timestamp) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into webhistory(website, visit_time) values('%s', '%s')", website, timestamp);
    return g_conn_.execute_no_result(buffer);
}

int insert_word_searched(const char*  word, const char * engine) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into wordhistory(word, engine) values('%s', '%s')", word, engine);
    return g_conn_.execute_no_result(buffer);
}

int insert_word_searched(const char*  word, const char * engine, const char * timestamp) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into wordhistory(word, engine, visit_time) values('%s', '%s', '%s')", word, engine, timestamp);
    return g_conn_.execute_no_result(buffer);
}

// 检测
bool check_white_dns(const char*dns) {
    int count;
    char buffer[1024];
    _sntprintf(buffer, 1024, "select website from wdns where website= '%s'", dns);
    int rc =  get_sql_select_count(&g_conn_, buffer, &count);
    if (rc) {
        return false;
    } else {
        return count > 0;
    }
}

bool check_black_dns(const char * dns) {
    int count;
    char buffer[1024];
    _sntprintf(buffer, 1024, "select website from bdns where website= '%s'", dns);
    int rc =  get_sql_select_count(&g_conn_, buffer, &count);
    if (rc) {
        return false;
    } else {
        return count > 0;
    }
}

bool check_black_searchword(const char* word, const char * engine){
    int count;
    char buffer[1024];
    _sntprintf(buffer, 1024, "select word from bwords where word= '%s' and engine = '%s'", word, engine);
    int rc =  get_sql_select_count(&g_conn_, buffer, &count);
    if (rc) {
        return false;
    } else {
        return count > 0;
    }
}

// 插入数据
int insert_white_dns(const char *dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into wdns(website) values ('%s')", dns);
    return g_conn_.execute_no_result(buffer);
}
int insert_black_dns(const char *dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into bdns(website) values ('%s')", dns);
    return g_conn_.execute_no_result(buffer);
}
int insert_black_searchword(const char *word, const char *engine) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "insert into bwords(word, engine) values ('%s', '%s')", word, engine);
    return g_conn_.execute_no_result(buffer);
}

// 删除数据
int del_white_dns(const char*dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "delete from wdns where website = '%s'", dns);
    return g_conn_.execute_no_result(buffer);
}
int del_black_dns(const char*dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "delete from bdns where website = '%s'", dns);
    return g_conn_.execute_no_result(buffer);
}
int del_black_searchword(const char*word, const char*engine) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "delete from bwords where word = '%s' and engine = '%s'", word, engine);
    return g_conn_.execute_no_result(buffer);
}

//===========================
// 重复代码
namespace {
int enum_data(const char * sql, boost::function<int (const char *, const char *, const char *)>& enum_fun) {
    int rc = 0;
    sqlite_table t;
    sqlite_query * query = g_conn_.create_query(sql);

    if (NULL == query) {
        rc = -1;
        goto exit;
    }

    rc = query->prepare();
    if (rc) {
        goto exit;
    }

    rc = query->execute();
    if (rc) {
        sqlite_row row;
        goto exit;
    }

    while (query->step() == SQLITE_ROW) {
        sqlite_row  row;
        int rc = query->fetch(&row);
        if (rc) {
            goto exit;
        }

        enum_fun(row[0].get_s_value().c_str(), row[1].get_s_value().c_str(), row[2].get_s_value().c_str());
    }

exit:
    if (query != NULL) {
        delete query;
        query  = NULL;
    }
    return rc;
}
int enum_data(const char * sql, boost::function<int (int, const char *)>& enum_fun) {
    int rc = 0;
    sqlite_table t;
    sqlite_query * query = g_conn_.create_query(sql);

    if (NULL == query) {
        rc = -1;
        goto exit;
    }

    rc = query->prepare();
    if (rc) {
        goto exit;
    }

    rc = query->execute();
    if (rc) {
        sqlite_row row;
        goto exit;
    }

    while (query->step() == SQLITE_ROW) {
        sqlite_row  row;
        int rc = query->fetch(&row);
        if (rc) {
            goto exit;
        }

        enum_fun(row[0].get_i_value(), row[1].get_s_value().c_str());
    }

exit:
    if (query != NULL) {
        delete query;
        query  = NULL;
    }
    return rc;
}

int enum_data(const char * sql, boost::function<int (const char*, const char *)> & enum_fun) {
    int rc = 0;
    sqlite_table t;
    sqlite_query * query = g_conn_.create_query(sql);

    if (NULL == query) {
        rc = -1;
        goto exit;
    }

    rc = query->prepare();
    if (rc) {
        goto exit;
    }

    rc = query->execute();
    if (rc) {
        sqlite_row row;
        goto exit;
    }

    while (query->step() == SQLITE_ROW) {
        sqlite_row  row;
        int rc = query->fetch(&row);
        if (rc) {
            goto exit;
        }

        enum_fun(row[0].get_s_value().c_str(), row[1].get_s_value().c_str());
    }

exit:
    if (query != NULL) {
        delete query;
        query  = NULL;
    }
    return rc;
}

int enum_data(const char * sql, boost::function<int ( const char *)> & enum_fun) {
    int rc = 0;
    sqlite_table t;
    sqlite_query * query = g_conn_.create_query(sql);

    if (NULL == query) {
        rc = -1;
        goto exit;
    }

    rc = query->prepare();
    if (rc) {
        goto exit;
    }

    rc = query->execute();
    if (rc) {
        sqlite_row row;
        goto exit;
    }

    while (query->step() == SQLITE_ROW) {
        sqlite_row  row;
        int rc = query->fetch(&row);
        if (rc) {
            goto exit;
        }

        enum_fun(row[0].get_s_value().c_str());
    }

exit:
    if (query != NULL) {
        delete query;
        query  = NULL;
    }
    return rc;
}
}