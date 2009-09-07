#ifndef _DBLOGICAL_LAYER_H__
#define _DBLOGICAL_LAYER_H__

#include <boost/function.hpp>


int load_db(const std::string &dbname);


// ���
bool check_white_dns(const std::string &dns);
bool check_black_dns(const std::string &dns);
bool check_black_searchword(const std::string &dns);

// ����ɾ��websites
int insert_white_dns(const std::string &dns);
int insert_black_dns(const std::string &dns);
int insert_black_searchword(const std::string &word, const std::string &engine);
int del_white_dns(const std::string &dns);
int del_black_dns(const std::string &dns);
int del_black_searchword(const std::string &word, const std::string &engine);

// ��ʷ��¼
int insert_website_visited(const std::string & website);
int insert_word_searched(const std::string & word);
int auto_clean_website_list(const int days);
int auto_clean_wordsearched_list(const int days);

// ��¼�����û���¼��ʱ��
int su_user_logon();
int su_user_logoff();

// 
int verify_db();             // ��֤���ݿ�
int initialize_db();         // ��ʼ�����ݿ�
int backup_db();           // �������ݿ�
int revert_db();             // ��backup�лָ�����

int set_error_msg_callback(boost::function<void (const int , const std::string&)> errfun);

#endif  // _DBLOGICAL_LAYER_H__