#include "StdAfx.h"
#include ".\memorydb.h"
#include ".\CPPSQLite.h"
#include <assert.h>

namespace {
const char *SQL_CREATE_TABLE_WDNS_LIST = "CREATE TABLE WDNS(DNSNAME TEXT(255) PRIMARY KEY); ";
const char *SQL_CREATE_TABLE_BDNS_LIST = "CREATE TABLE BDNS(DNSNAME TEXT(255) PRIMARY KEY); ";
const char *SQL_CREATE_TABLE_SEARCH_LIST = "CREATE TABLE SWORDS(WORDS TEXT(255) PRIMARY KEY, SEARCHENG CHAR(100), SRDATE CHAR(50)); ";
};

MemoryDB::MemoryDB(void)
{
	memDB_ = NULL;
}

MemoryDB::~MemoryDB(void)
{
	if (NULL != memDB_) {
		delete memDB_;
		memDB_ = NULL;
	}
}


int MemoryDB::initialize(const char * filedb_path) {
	try {
	create_memory_db();

	} catch (...) {
	}

	return 0;
}

int MemoryDB::create_mem_tables() {
	assert (NULL != memDB_);
	memDB_->execDML(SQL_CREATE_TABLE_WDNS_LIST);
	memDB_->execDML(SQL_CREATE_TABLE_BDNS_LIST);
	memDB_->execDML(SQL_CREATE_TABLE_SEARCH_LIST);

	return 0;
}

int MemoryDB::create_memory_db() {
	// 创建内存数据库
	memDB_ = new CppSQLiteDB();
	memDB_->open(":memory:");

	// 创建相应的表
	create_mem_tables();
	return 0;
}