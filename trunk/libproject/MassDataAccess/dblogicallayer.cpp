#include "stdafx.h"
#include "dblogicallayer.h"
#include "sqliteutility.h"

sqlite_connection g_conn_;

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

int enum_su_logon(boost::function<int (int, const char *)> f) {
    int rc = 0;
    char buffer[1024];
     sqlite_table t;
    _sntprintf(buffer, 1024, "select logon_type, logon_tm from sulogon");
    sqlite_query * query = g_conn_.create_query(buffer);

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

        f(row[0].get_i_value(), row[1].get_s_value().c_str());
    }

exit:
    if (query != NULL) {
        delete query;
        query  = NULL;
    }
    return rc;
}

// 自动清理
int auto_clean_website_list(const int days) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "delete from webhistory where julianday('now') -  visit_time> %d", days);
    return g_conn_.execute_no_result(buffer);
}
int auto_clean_wordsearched_list(const int days) {
    char buffer[1024];
    _sntprintf(buffer, 1024, "delete from wordhistory where julianday('now') -  visit_time> %d", days);
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
    char buffer[1024];
    _sntprintf(buffer, 1024, "select website from wdns where website= '%s'", dns);
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
    _sntprintf(buffer, 1024, "select website from bdns where website= '%s'", dns);
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
bool check_black_searchword(const char* word, const char * engine){
    char buffer[1024];
    _sntprintf(buffer, 1024, "select word from bwords where word= '%s' and engine = '%s'", word, engine);
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