#ifndef _DBLOGICAL_LAYER_H__
#define _DBLOGICAL_LAYER_H__

#include <boost/function.hpp>


int load_db(const char * dbname);


// ���
bool check_white_dns(const char* dns);
bool check_black_dns(const char* dns);
bool check_black_searchword(const char* word, const char * engine);

// ����ɾ��websites
int insert_white_dns(const char* dns);
int insert_black_dns(const char* dns);
int insert_black_searchword(const char* word, const char* engine);
int del_white_dns(const char* dns);
int del_black_dns(const char* dns);
int del_black_searchword(const char* word, const char* engine);

// ��ʷ��¼
int insert_website_visited(const char*  website);
int insert_word_searched(const char*  word);
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

int set_error_msg_callback(boost::function<void (const int , const char*)> errfun);

#endif  // _DBLOGICAL_LAYER_H__