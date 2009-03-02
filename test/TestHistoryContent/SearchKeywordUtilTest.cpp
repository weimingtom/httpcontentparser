#include "StdAfx.h"
#include ".\searchkeywordutiltest.h"

SearchKeywordUtilTest::SearchKeywordUtilTest(void) {
}

SearchKeywordUtilTest::~SearchKeywordUtilTest(void) {
}


// 测试此类的文件读取
void SearchKeywordUtilTest::testReadSearchWordsFileOper() {
	SeachKeywordUtil util;
	util.load("testcase1.txt");
	util.save("textcase2.txt");
}


void SearchKeywordUtilTest::testReadSearcEnumerator() {
}


void SearchKeywordUtilTest::testReadSearcGetNext() {
}

