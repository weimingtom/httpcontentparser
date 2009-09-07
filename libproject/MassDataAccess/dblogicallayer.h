#ifndef _DBLOGICAL_LAYER_H__
#define _DBLOGICAL_LAYER_H__

#include <boost/function.hpp>


int load_db(const std::string &dbname);


// 检测
bool check_white_dns(const std::string &dns);
bool check_black_dns(const std::string &dns);
bool check_black_searchword(const std::string &dns);

// 增加删除websites
int insert_white_dns(const std::string &dns);
int insert_black_dns(const std::string &dns);
int insert_black_searchword(const std::string &word, const std::string &engine);
int del_white_dns(const std::string &dns);
int del_black_dns(const std::string &dns);
int del_black_searchword(const std::string &word, const std::string &engine);

// 历史记录
int insert_website_visited(const std::string & website);
int insert_word_searched(const std::string & word);
int auto_clean_website_list(const int days);
int auto_clean_wordsearched_list(const int days);

// 记录超级用户登录的时间
int su_user_logon();
int su_user_logoff();

// 
int verify_db();             // 验证数据库
int initialize_db();         // 初始化数据库
int backup_db();           // 备份数据库
int revert_db();             // 从backup中恢复数据

int set_error_msg_callback(boost::function<void (const int , const std::string&)> errfun);

#endif  // _DBLOGICAL_LAYER_H__