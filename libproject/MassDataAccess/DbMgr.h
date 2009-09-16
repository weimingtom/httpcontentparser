#ifndef _MASSDATAACCESS_H__
#define _MASSDATAACCESS_H__

#include <string>

// �����������ݿ�Ĳ���
// 1. ����ͳһ�ĳ�ʼ��
// 2. ά��һ��Ψһ��״̬�����Ƿ���dirty data��
// 3. �����ݿ��ܹ�ͳһ�Ľ���dump����
class DBMgr {
public:
    DBMgr();
    ~DBMgr();

public:
    // ��ʼ��һ�����ݿ�
    int initialize(const std::string &path);

    // �������ݿ�
    // �˺������⺯��״̬�����û�������ݣ��������dump����
    int dump_db();

    // ǿ�ƽ���dump����
    // �����Ƿ��������ݣ� dump�����������
    int force_dump();

public:
    //==========================
    // һЩ���ú���

    // һ�º������ڽ��������뵽һ���൱��
    // ��ʼ��Website list
    int initialize_while_websites();
    int initialize_black_websites();

    // ��ʼ�������б�
    int initialize_application_controlled();

    // ��ʼ���û���¼��Ϣ
    int initialize_su_logon();

    // �Զ�������
    int auto_clean_websites_record();
    int auto_clean_searchword_record();
private:
     void set_dirty();
    // ���Ϊ��0����ʾ����������
    int dirty_data_;
};

#endif  // _MASSDATAACCESS_H__