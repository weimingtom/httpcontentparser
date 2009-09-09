#include "stdafx.h"
#include "sqliteutility.h"
#include <sqlite3.h>
#include <assert.h>


int report_error(const char  * errmsg, int code) {
    printf("error messsage : %s\n", errmsg);
    return 0;
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
int sqlite_query::prepare() {
    const char * pbinary_stmt = NULL;
    int columns = 0;
    int rc = sqlite3_prepare(database_, statement_.c_str(), statement_.length(), &stmt_, &pbinary_stmt);
    if (rc) {
        goto exit;
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
    fecth_value(row);
    return 0;
}

// 获取一行数据
int sqlite_query::fecth_value(sqlite_row * row) {
    int columns = sqlite3_column_count(stmt_);

    for (int i = 0; i < columns; ++i) {
        int type = sqlite3_column_type(stmt_, i);
        switch(type) {
            case SQLITE_INTEGER:
                {
                int value = sqlite3_column_int(stmt_, i);
                row->append_item(sqlite_item(value));
                }
                break;
            case SQLITE_FLOAT:
                {
                    float value = (float)sqlite3_column_double(stmt_, i);
                    row->append_item(sqlite_item(value));
                }
                break;
            case SQLITE_TEXT:
                {
                const unsigned char * value= sqlite3_column_text(stmt_, i);
                row->append_item(sqlite_item((const char *)value));
                }
                break;
            default:
                break;
        }
         
    }

    return 0;
}

int sqlite_query::step() {
    assert(NULL != stmt_);
    return sqlite3_step(stmt_);
}

int sqlite_query::execute_at_one_time(sqlite_table * table) {
    assert(NULL != table);
    int columns = 0;
    int rc = prepare();
    if (rc) {
        goto exit;
    }

    rc = execute();
    if (rc) {
        goto exit;
    }

    // 列数
     columns = sqlite3_column_count(stmt_);

    // 获取每一列的类型
    for (int i = 0; i < columns; ++i) {
        const int col_type = sqlite3_column_type(stmt_, i);
        const char * col_name = sqlite3_column_name(stmt_, i);
        table->add_column(sqlite_column(col_type, col_name));
    }

    while (step() == SQLITE_ROW) {
        sqlite_row  row;
        int rc = fetch(&row);
        if (rc) {
            goto exit;
        }
        table->add_row(row);
    }
exit:
    return rc;
}

//================================
// class sqlite_row
sqlite_row::sqlite_row() {
    tab_ = NULL;
}

sqlite_row::sqlite_row(sqlite_table * tab) : tab_(tab){
}

sqlite_row::sqlite_row(const sqlite_row &row) {
    this->tab_ = row.tab_;
    
    SUBITEMS::const_iterator iter = row.items_.begin();
    for (; iter != row.items_.end(); ++iter) {
        this->items_.push_back(*iter);
    }
}

sqlite_row::~sqlite_row() {
}



int sqlite_row::append_item(sqlite_item & item) {
    items_.push_back(item);
    return (int)items_.size();
}



sqlite_item  sqlite_row::operator[] (const int index) {
    return get_item(index);
}

sqlite_item sqlite_row::operator[] (const std::string & name) {
    if (tab_ != NULL) {
        int index  =  tab_->get_column_index(name);
        if (-1 != index) {
            return get_item(index);
        }
    }
    return NULL;
}

sqlite_item  sqlite_row::get_item(const int index) {
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

sqlite_column::sqlite_column(const sqlite_column &col) {
    this->type_ = col.get_type();
    this->name_ = col.get_name();
}
sqlite_column::~sqlite_column()
{
}

//=================================
//class sqlite_table
sqlite_table::sqlite_table() {
}

sqlite_table::~sqlite_table(){
 }

void sqlite_table::add_column(sqlite_column & column) {
    m_cols_.push_back(column);
}


int sqlite_table::get_column_index(const std::string &colname) {
    int index = 0;
    COLUMNS::iterator iter  = m_cols_.begin();
    for (; iter != m_cols_.end(); ++iter) {
        if (colname == (*iter).get_name()) {
            return index;
        } else {
            index++;
        }
    }

    return -1;
}

//================================
// class sqlite_item
sqlite_item::sqlite_item(const int value) {
    type_ = INTEGER;
    i_value = value;
}

sqlite_item::sqlite_item(const float value) {
    type_ =  FLOAT;
    f_value = value;
}

sqlite_item::sqlite_item(const char * value) {
    type_ = STRING;
    s_value = value;
}

sqlite_item::sqlite_item(const sqlite_item &item) {
    type_ = item.get_type();
    if (type_ == INTEGER) {
        i_value = item.i_value;
    } else if (type_ == FLOAT) {
        f_value = item.f_value;
    } else if (type_ == STRING) {
        s_value = item.s_value;
    }
}

