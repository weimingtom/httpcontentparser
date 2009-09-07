#include "stdafx.h"
#include "sqliteutility.h"
#include <sqlite3.h>
#include <assert.h>


int report_error(const char  * errmsg, int code) {
    printf("error messsage : %s", errmsg);
    return 0;
}

boost::function<void (const int , const std::string&)> g_err_function = report_error;
int set_error_msg_callback(boost::function<void (const int , const std::string&)> errfun) {
    g_err_function  = errfun;
}

//===============================
// class sqlite_connection
sqlite_connection::sqlite_connection() {
    database_ = 0;
}

sqlite_connection::~sqlite_connection() {
    // 释放所有基于此链接的查询
    close();
}

int sqlite_connection::open(const char * name) {
    int rc = SQLITE_OK;
    rc = sqlite3_open("record.data", &database_);
    if (rc ) {
        // 将errmsg写入日志
        rc = sqlite3_errcode(database_);
        report_error(sqlite3_errmsg(database_), sqlite3_errcode(database_));
        goto exit;
    }

    db_name_ = name;
exit:
    return rc;
}

int sqlite_connection::close() {
    if (0 != database_) {
        sqlite3_close(database_);
        database_ = 0;
    }

    return 0;
}

int sqlite_connection::execute_no_result(const char * statement) {
    assert(database_ != 0);
    char *errmsg = NULL;
    int rc = sqlite3_exec(database_,  statement,
                                            NULL,  NULL,  &errmsg);
    if (rc) {
        goto exit;
    }

exit:
    if (NULL != errmsg) {
        report_error(errmsg, rc);
        sqlite3_free(errmsg);
        errmsg = NULL;
    }

    return rc;
}

sqlite_query * sqlite_connection::create_query(const char * statement) {
    assert(database_ != 0);
    sqlite_query * pQuery = new sqlite_query(statement, database_);
    return pQuery;
}


//===============================================
//
//

sqlite_query::sqlite_query(const char * statement, sqlite3  *database) 
{
    database_ = database;
    statement_ = statement;
    stmt_ = NULL;
}

sqlite_query::~sqlite_query() {
    uninitialize();
}


// 准备执行
// 获取结果的列数, 并对table进行初始化
int sqlite_query::prepare(sqlite_table * table) {
    const char * pbinary_stmt = NULL;
    int columns = 0;
    int rc = sqlite3_prepare(database_, statement_.c_str(), statement_.length(), &stmt_, &pbinary_stmt);
    if (rc) {
        goto exit;
    }

    table_ = table;

    if (NULL != table) {
        // 列数
        columns = sqlite3_column_count(stmt_);

    // 获取每一列的类型
        for (int i = 0; i < columns; ++i) {
            const int col_type = sqlite3_column_type(stmt_, i);
            const char * col_name = sqlite3_column_name(stmt_, i);
            table_->add_column(new sqlite_column(col_type, col_name));
        }
    }
exit:
    if (rc) {
        report_error(NULL, rc);
    }

    return rc;
}

int sqlite_query::execute() {
    return 0;
}

int sqlite_query::uninitialize() {
    if (NULL != stmt_) {
        sqlite3_finalize(stmt_);
        stmt_ = NULL;
    }
    return 0;
}

int sqlite_query::fetch(sqlite_row * row) {
    assert (NULL != table_);

    int columns = sqlite3_column_count(stmt_);
    fecth_value(row);
    return 0;
}

// 获取一行数据
int sqlite_query::fecth_value(sqlite_row * row) {
    int columns = sqlite3_column_count(stmt_);

    sqlite_item * item = NULL;
    for (int i = 0; i < columns; ++i) {
        int type = sqlite3_column_type(stmt_, i);
        switch(type) {
            case SQLITE_INTEGER:
                {
                int value = sqlite3_column_int(stmt_, i);
                item = new sqlite_item(value);
                }
                break;
            case SQLITE_FLOAT:
                {
                    float value = (float)sqlite3_column_double(stmt_, i);
                    item = new sqlite_item(value);
                }
                break;
            case SQLITE_TEXT:
                {
                const unsigned char * value= sqlite3_column_text(stmt_, i);
                item = new sqlite_item((const char *)value);
                }
                break;
            default:
                item = NULL;
                break;
        }
         
        row->append_item(item);
    }

    return 0;
}

int sqlite_query::step() {
    assert(NULL != stmt_);
    return sqlite3_step(stmt_);
}

sqlite_table * sqlite_query::execute_at_one_time(sqlite_table * table) {
    int rc = prepare(table);
    execute();

    while (step() == SQLITE_ROW) {
        sqlite_row * row = table->new_row();
        fetch(row);
    }
    return NULL;
}

//================================
// class sqlite_row
sqlite_row::sqlite_row() {
    tab_ = NULL;
}

sqlite_row::sqlite_row(sqlite_table * tab) : tab_(tab){
}

sqlite_row::~sqlite_row() {
}



int sqlite_row::append_item(sqlite_item *item) {
    items_.push_back(item);
    return (int)items_.size();
}



sqlite_item * sqlite_row::operator[] (const int index) {
    return get_item(index);
}

sqlite_item* sqlite_row::operator[] (const std::string & name) {
    if (tab_ != NULL) {
        int index  =  tab_->get_column_index(name);
        if (-1 != index) {
            return get_item(index);
        }
    }
    return NULL;
}

sqlite_item * sqlite_row::get_item(const int index) {
    if (index < (int)items_.size()) {
        return items_.at(index);
    } else {
        return NULL;
    }
}

//================================
// class sqlite_column
sqlite_column::sqlite_column(const int type, const std::string &name) 
{
    type_ = type;
    name_ = name;
}

sqlite_column::~sqlite_column()
{
}

//=================================
//class sqlite_table
sqlite_table::sqlite_table() {
}

sqlite_table::~sqlite_table(){
    free_rows();
    free_columns();
 }

sqlite_row * sqlite_table::new_row() {
    sqlite_row * newrow =  new sqlite_row(this);
    return newrow;
}

void sqlite_table::add_column(sqlite_column * column) {
    m_cols_.push_back(column);
}

void sqlite_table::free_columns() {
    COLUMNS::iterator iter = m_cols_.begin();
    for (; iter != m_cols_.end(); ++iter) {
        delete *iter;
    }
    m_cols_.clear();
}

void sqlite_table::free_rows() {
    ROWS::iterator iter = m_rows_.begin();
    for (; iter != m_rows_.end(); ++iter) {
        delete *iter;
    }
    m_rows_.clear();
}

int sqlite_table::get_column_index(const std::string &colname) {
    int index = 0;
    COLUMNS::iterator iter  = m_cols_.begin();
    for (; iter != m_cols_.end(); ++iter) {
        if (colname == (*iter)->get_name()) {
            return index;
        } else {
            index++;
        }
    }

    return -1;
}

