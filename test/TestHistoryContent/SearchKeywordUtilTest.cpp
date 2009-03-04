#include "StdAfx.h"
#include ".\searchkeywordutiltest.h"
#include <searchengine_define.h>
#include <string>
#include <iostream>
#include <utility/timeutility.h>

SearchKeywordUtilTest::SearchKeywordUtilTest(void) {
}

SearchKeywordUtilTest::~SearchKeywordUtilTest(void) {
}

namespace {
	void printDataItem(const std::string &name, const SeachKeywordUtil::KEYWORD_DATA &data) {
		using namespace std;
		TCHAR buf[MAX_PATH], *seachengine;
	
		cout<<"name :" << name << endl
			<<"\tsearch engine : " << GetSearchEngineName(data.engine_type) <<endl
			<<"\tsearch count : " <<data.seach_count << endl
			<<"\tlast seach time: " << timeutility::USFormatTime(data.last_seach, buf, MAX_PATH)<<endl;
	}	
};


// 测试此类的文件读取
void SearchKeywordUtilTest::testReadSearchWordsFileOper() {
	SeachKeywordUtil util;
	util.addKeyword("hello1", SEARCHENGINE_GOOGLE);
	util.addKeyword("hello2", SEARCHENGINE_YAHOO);
	util.addKeyword("hello3", SEARCHENGINE_BAIDU);
	util.addKeyword("hello4", SEARCHENGINE_YAHOO);
	util.addKeyword("hello4", SEARCHENGINE_YAHOO);
	util.addKeyword("hello1", SEARCHENGINE_BAIDU);
	util.addKeyword("hello3", SEARCHENGINE_GOOGLE);
	util.addKeyword("hello4", SEARCHENGINE_YAHOO);
	util.addKeyword("hello2", SEARCHENGINE_BAIDU);
	util.addKeyword("hello4", SEARCHENGINE_YAHOO);
	util.save(".\\textcase2.txt");
}


void SearchKeywordUtilTest::testReadSearcEnumerator() {
	SeachKeywordUtil util;
	util.load(".\\textcase2.txt");

	using namespace std;
	string str, next;
	SeachKeywordUtil::KEYWORD_DATA data;
	util.getFirst(&str, &data);
	printDataItem(str, data);

	while (util.getNext(str, &next, &data) != 0) {
		printDataItem(str, data);
		str = next;
	}
}


void SearchKeywordUtilTest::testReadSearcGetNext() {
}

