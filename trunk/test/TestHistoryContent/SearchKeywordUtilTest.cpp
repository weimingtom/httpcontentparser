#include "StdAfx.h"
#include ".\searchkeywordutiltest.h"

SearchKeywordUtilTest::SearchKeywordUtilTest(void) {
}

SearchKeywordUtilTest::~SearchKeywordUtilTest(void) {
}


// ���Դ�����ļ���ȡ
void SearchKeywordUtilTest::testReadSearchWordsFileOper() {
	SeachKeywordUtil util;
	util.load("testcase1.txt");
	util.save("textcase2.txt");
}


void SearchKeywordUtilTest::testReadSearcEnumerator() {
}


void SearchKeywordUtilTest::testReadSearcGetNext() {
}

