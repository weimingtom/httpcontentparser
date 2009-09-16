#ifndef _DBLOGICAL_LAYER_H__
#define _DBLOGICAL_LAYER_H__

#include <boost/function.hpp>


int load_db(const char * dbname);


// 检测
bool check_white_dns(const char* dns);
bool check_black_dns(const char* dns);
bool check_black_searchword(const char* word);

// 增加删除websites
int insert_white_dns(const char* dns);
int insert_black_dns(const char* dns);
int insert_black_searchword(const char* word);
int del_white_dns(const char* dns);
int del_black_dns(const char* dns);
int del_black_searchword(const char* word);

// 枚举
int enum_white_dns(boost::function<int ( const char*)> enum_fun);
int enum_black_dns(boost::function<int( const char*)> enum_fun);
int enum_blacksearch_word(boost::function<int (const char*)> enum_fun);

// 历史记录
int insert_website_visited(const char*  website);
int insert_word_searched(const char*  word, const char * engine);
int auto_clean_website_list(const int days);
int auto_clean_wordsearched_list(const int days);
int enum_website_visited(boost::function<int (const char*, const char *)> enum_fun);
int enum_word_searched(boost::function<int (const char*, const char *)> enum_fun);

// 记录超级用户登录的时间
int su_user_logon();
int su_user_logoff();
int enum_su_logon(boost::function<int (int, const char *)> f);

// 应用程序
int add_program(const std::string &product_name);
int remove_program(const std::string &product_name);
int enum_program(boost::function<int (const char*)> enum_fun);

// 
int verify_db();             // 验证数据库
int initialize_db();         // 初始化数据库
int backup_db();           // 备份数据库
int revert_db();             // 从backup中恢复数据

// for test
int insert_website_visited(const char * website, const char * timestamp);
int insert_word_searched(const char * website, const char * engine, const char * timestamp);
int get_website_visited_count(int * count);
int get_word_searched_count(int * count);

int set_error_msg_callback(boost::function<void (const int , const char*)> errfun);

#endif  // _DBLOGICAL_LAYER_H__