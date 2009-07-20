#pragma once

class CppSQLiteDB;

// 内存数据库
// 此数据库会通过文件加载，但是只加载一次
// 之后再运行过程当中会将不断的将数据库存储到文件当中
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
