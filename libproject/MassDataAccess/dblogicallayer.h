#ifndef _DBLOGICAL_LAYER_H__
#define _DBLOGICAL_LAYER_H__

#include <boost/function.hpp>


int load_db(const char * dbname);


// ���
bool check_white_dns(const char* dns);
bool check_black_dns(const char* dns);
bool check_black_searchword(const char* word);

// ����ɾ��websites
int insert_white_dns(const char* dns);
int insert_black_dns(const char* dns);
int insert_black_searchword(const char* word);
int del_white_dns(const char* dns);
int del_black_dns(const char* dns);
int del_black_searchword(const char* word);

// ö��
int enum_white_dns(boost::function<int ( const char*)> enum_fun);
int enum_black_dns(boost::function<int( const char*)> enum_fun);
int enum_blacksearch_word(boost::function<int (const char*)> enum_fun);

// ��ʷ��¼
int insert_website_visited(const char*  website);
int insert_word_searched(const char*  word, const char * engine);
int auto_clean_website_list(const int days);
int auto_clean_wordsearched_list(const int days);
int enum_website_visited(boost::function<int (const char*, const char *)> enum_fun);
int enum_word_searched(boost::function<int (const char*, const char *)> enum_fun);

// ��¼�����û���¼��ʱ��
int su_user_logon();
int su_user_logoff();
int enum_su_logon(boost::function<int (int, const char *)> f);

// Ӧ�ó���
int add_program(const std::string &product_name);
int remove_program(const std::string &product_name);
int enum_program(boost::function<int (const char*)> enum_fun);

// 
int verify_db();             // ��֤���ݿ�
int initialize_db();         // ��ʼ�����ݿ�
int backup_db();           // �������ݿ�
int revert_db();             // ��backup�лָ�����

// for test
int insert_website_visited(const char * website, const char * timestamp);
int insert_word_searched(const char * website, const char * engine, const char * timestamp);
int get_website_visited_count(int * count);
int get_word_searched_count(int * count);

int set_error_msg_callback(boost::function<void (const int , const char*)> errfun);

#endif  // _DBLOGICAL_LAYER_H__