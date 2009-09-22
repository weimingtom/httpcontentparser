#ifndef _SQLITE_UTILITY_H__
#define _SQLITE_UTILITY_H__

#include<sqlite3.h>
#include <string>
#include <vector>
#include <map>
#include <assert.h>

namespace sqllite_utility {

class sqlite_query;

class sqlite_connection {
public:
    sqlite_connection();
    ~sqlite_connection();
public:
    int open(const char * name);
    int execute_no_result(const char * statement);

    sqlite_query * create_query(const char * statement);
    int close();
private:
      sqlite3  *database_;
      std::string db_name_;
};

class sqlite_table;
class sqlite_column;

class sqlite_item {
public:
    sqlite_item(const sqlite_item &item) ;
    sqlite_item(const int value);
    sqlite_item(const float value) ;
    sqlite_item(const char * value) ;

public:
    int get_type() const {  return type_;}
    int get_i_value() const { assert(get_type() == INTEGER);return i_value;}
    float get_f_value() const { assert(get_type() == FLOAT);return f_value;}
    const std::string & get_s_value()  const { assert(get_type() == STRING);return s_value;}

    enum {
        INTEGER,
        FLOAT,
        STRING
    };
private:
    int i_value;
    float f_value;
    std::string s_value;
    int type_;
};

class sqlite_row {
private:
    // 应该被table创建
    friend class sqlite_table;
public:
    sqlite_row();
    sqlite_row(sqlite_table * tab);
    sqlite_row(const sqlite_row &row);
public:
    ~sqlite_row();

public:
    int get_col_count() const { return (int)items_.size();}
    int append_item(sqlite_item & item);
public:
    sqlite_item  operator[] (const int index);
    sqlite_item  operator[] (const std::string &name);

private:
    sqlite_item  get_item(const int index);
private:
    typedef std::vector<sqlite_item> SUBITEMS;
    SUBITEMS items_;

    sqlite_table * tab_;
};

class sqlite_column {
public:
    sqlite_column(const int type, const std::string &name);
    ~sqlite_column();

    sqlite_column(const sqlite_column &col);
public:
    const std::string & get_name() const { return name_;}
    int get_type() const { return type_;}
private:
    std::string name_;
    int type_;
};

class sqlite_table {
public:
    sqlite_table();
    ~sqlite_table();

public:
    int get_row_count() const { return (int)m_rows_.size();}
    void add_row(sqlite_row & row) {m_rows_.push_back(row); }
private:
    void add_column(sqlite_column & column);
    int get_column_index(const std::string &colname);
private:
    typedef std::vector<sqlite_row> ROWS;
    typedef std::vector<sqlite_column> COLUMNS;
    ROWS m_rows_;
    COLUMNS m_cols_;
    friend class sqlite_query;
    friend class sqlite_row;
};


class sqlite_query {
public:
    ~sqlite_query();
public:
    int prepare();
    int execute();
    int step();
    int fetch(sqlite_row * row);

    // 一次性执行， 返回一个表
    int execute_at_one_time(sqlite_table * table);
private:
    int fecth_value(sqlite_row * row);
private:
    // 只能由类sqlite_connection生成
    sqlite_query(const char * statement, sqlite3  *database_);
    sqlite_query();
    friend class sqlite_connection;

    int uninitialize();
private:
    std::string statement_;

    sqlite3_stmt *stmt_;

    // 这里应该注意，其实应该使用smart_pointer
    // 如果直接使用指针，就有一个基本的限制就是
    // sqlite_query长于sqlite_connection以至于
    // 能够保证database_总是存在的
    sqlite3  *database_;
};


// some utility functions
int get_sql_select_count(sqlite_connection * conn, const char * statement, int * count);

}

#endif  // _SQLITE_UTILITY_H__