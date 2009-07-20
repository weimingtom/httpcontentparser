#pragma once

class CppSQLiteDB;

// �ڴ����ݿ�
// �����ݿ��ͨ���ļ����أ�����ֻ����һ��
// ֮�������й��̵��лὫ���ϵĽ����ݿ�洢���ļ�����
class MemoryDB {
public:
	MemoryDB(void);
	~MemoryDB(void);

public:
	int initialize(const char * filedb_path);
	
private:
	int create_memory_db();
	int create_mem_tables();

private:
	CppSQLiteDB * memDB_;
};
