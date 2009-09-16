#ifndef _MASSDATAACCESS_H__
#define _MASSDATAACCESS_H__

#include <string>

// 控制所有数据库的操作
// 1. 进行统一的初始化
// 2. 维护一个唯一的状态（如是否有dirty data）
// 3. 是数据库能够统一的进行dump操作
class DBMgr {
public:
    DBMgr();
    ~DBMgr();

public:
    // 初始化一个数据库
    int initialize(const std::string &path);

    // 保存数据库
    // 此函数会检测函数状态，如果没有脏数据，不会进行dump操作
    int dump_db();

    // 强制进行dump操作
    // 无论是否有脏数据， dump操作都会进行
    int force_dump();

public:
    //==========================
    // 一些常用函数

    // 一下函数用于将数据填入到一个类当中
    // 初始话Website list
    int initialize_while_websites();
    int initialize_black_websites();

    // 初始化程序列表
    int initialize_application_controlled();

    // 初始化用户登录信息
    int initialize_su_logon();

    // 自动清理共能
    int auto_clean_websites_record();
    int auto_clean_searchword_record();
private:
     void set_dirty();
    // 如果为非0，表示存在脏数据
    int dirty_data_;
};

#endif  // _MASSDATAACCESS_H__