#ifndef _DBLOGICAL_LAYER_H__
#define _DBLOGICAL_LAYER_H__

#include <boost/function.hpp>


int load_db(const char * dbname);


// 检测
bool check_white_dns(const char* dns);
bool check_black_dns(const char* dns);
bool check_black_searchword(const char* word, const char * engine);

// 增加删除websites
int insert_white_dns(const char* dns);
int insert_black_dns(const char* dns);
int insert_black_searchword(const char* word, const char* engine);
int del_white_dns(const char* dns);
int del_black_dns(const char* dns);
int del_black_searchword(const char* word, const char* engine);

// 历史记录
int insert_website_visited(const char*  website);
int insert_word_searched(const char*  word);
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

int set_error_msg_callback(boost::function<void (const int , const char*)> errfun);

#endif  // _DBLOGICAL_LAYER_H__