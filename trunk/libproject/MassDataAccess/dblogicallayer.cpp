#include "stdafx.h"
#include "dblogicallayer.h"
#include "sqliteutility.h"

sqlite_connection g_conn_;


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
    g_conn_.execute_no_result("create table sulogon  (logon integer,  visit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP )");
    return 0;
}

// 超级用户登录
int su_user_logon() {
    return g_conn_.execute_no_result("insert into sulogon(logon) values (1)");
}
int su_user_logoff() {
    return g_conn_.execute_no_result("insert into sulogon(logon) values (0)");
}


// 自动清理
int auto_clean_website_list(const int days) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "drop from webhistory where julianday('now') -  visit_time> %d", days);
    return g_conn_.execute_no_result(buffer);
}
int auto_clean_wordsearched_list(const int days) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "drop from wordhistory where julianday('now') -  visit_time> %d", days);
    return g_conn_.execute_no_result(buffer);
}

// 检测
bool check_white_dns(const char*dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "select count(*) from wdns where website= '%s'", dns);
    sqlite_query * query = g_conn_.create_query(buffer);

    if (NULL != query) {
        sqlite_table t;
        query->execute_at_one_time(&t);
        delete query;
        return t.get_row_count() > 0 ? true : false;
    } else {
        // 记录log
        return false;
    }
}

bool check_black_dns(const char * dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "select count(*) from bdns where website= '%s'", dns);
    sqlite_query * query = g_conn_.create_query(buffer);

    if (NULL != query) {
        sqlite_table t;
        query->execute_at_one_time(&t);
        delete query;
        return t.get_row_count() > 0 ? true : false;
    } else {
        // 记录log
        return false;
    }
}
bool check_black_searchword(const char *word, const char *engine) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "select count(*) from bwords where word= '%s' and engine = '%s'", word, engine);
    sqlite_query * query = g_conn_.create_query(buffer);

    if (NULL != query) {
        sqlite_table t;
        query->execute_at_one_time(&t);
        delete query;
        return t.get_row_count() > 0 ? true : false;
    } else {
        // 记录log
        return false;
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
    _sntprintf(buffer, 1024, "insert into bwords(word, engine) values ('%s')", word, engine);
    return g_conn_.execute_no_result(buffer);
}

// 删除数据
int del_white_dns(const char*dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "del from wdns where website = '%s'", dns);
    return g_conn_.execute_no_result(buffer);
}
int del_black_dns(const char*dns) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "del from bdns where website = '%s'", dns);
    return g_conn_.execute_no_result(buffer);
}
int del_black_searchword(const char*word, const char*engine) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "del from bdns where word = '%s' and engine = '%s'", word, engine);
    return g_conn_.execute_no_result(buffer);
}