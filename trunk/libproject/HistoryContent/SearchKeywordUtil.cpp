#include "StdAfx.h"
#include ".\searchkeywordutil.h"
#include <apputility.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// ===================
const char * SeachKeywordUtil::SEPERATOR = "&";
const char * SeachKeywordUtil::NEW_LINE = "\n";

SeachKeywordUtil::SeachKeywordUtil(void) {
}

SeachKeywordUtil::~SeachKeywordUtil(void) {
}


int SeachKeywordUtil::addKeyword(const std::string &keyword, const int seach_engine) {
	// ����ΪFILETIME, ����SYSTEMTIMEվ16�ֽڣ���FILETIMEֻ��Ҫ8�ֽ�
	// Ϊ�˷����ȡ����ʹ�ý�SYSTEMTIMEת��ΪFILETIME
	SYSTEMTIME tm;
	GetLocalTime(&tm);

	SEARCH_WORD_DATA::iterator iter = data_.find(keyword);
	if (data_.end() == iter) {
		// ���������
		KEYWORD_DATA item;
		item.engine_type = seach_engine;
		SystemTimeToFileTime(&tm, &item.last_seach);
		item.seach_count = 1;
		data_.insert(std::make_pair(keyword, item));
	} else {
		// ���������������һ�ε�����ʱ�估ʹ�õ���������
		iter->second.engine_type = seach_engine;
		iter->second.seach_count += 1;
		SystemTimeToFileTime(&tm, &iter->second.last_seach);
	}
	return 0;
}

int SeachKeywordUtil::insertItem(const std::string &keyword, const std::string & search_engine, const std::string & last_time , const std::string &times ) {
	// ���ַ���ת��Ϊ
	KEYWORD_DATA item;
	item.engine_type = atoi(search_engine.c_str());
	unsigned __int64 value = static_cast<unsigned __int64>(atoi(times.c_str()));
	item.last_seach.dwHighDateTime = static_cast<unsigned int>(value>>32);
	item.last_seach.dwLowDateTime = static_cast<unsigned int>(value);
	data_[keyword] = item;
	return 0;
}

// ����һ��
int SeachKeywordUtil::parseString(const std::string &line) {
	int firstSep = static_cast<int>(line.find(SEPERATOR));
	if (-1 == firstSep) return -1;

	int secSep = static_cast<int>(line.find(SEPERATOR,  firstSep + 1));
	if (-1 == secSep) return -1;

	int thrSep = static_cast<int>(line.find(SEPERATOR, secSep + 1));
	if (-1 == thrSep) return -1;

	std::string keyword = line.substr(0, firstSep );		// �ؼ���
	std::string searchengine = line.substr(firstSep + 1, secSep - firstSep -1);		// ��������
	std::string  lasttime = line.substr(secSep + 1, thrSep - secSep -1);	// �ϴη���ʱ��
	std::string times = line.substr(thrSep + 1, line.length());	// ��������

	insertItem(keyword, searchengine, lasttime, times);
	return 0;
}

// ��ȡ�����ļ�
int SeachKeywordUtil::load() {
	try {
		// ��ȡ����
		using namespace std;
		TCHAR filename[MAX_PATH];
		GetSeachWordFile(filename, MAX_PATH);

		ifstream  file(filename);
		if (file.is_open()) {
			const int BUF_SIZE = 1024;
			TCHAR line[BUF_SIZE];

			while (file.good())
			{
				file.getline(line, BUF_SIZE);
				parseString(line);
			}
			file.close();
		} else {
			// file can't be opened
		}
	} catch (...) {
	}
	return 0;
}

// ���������ݱ��浽�����ļ�����
int SeachKeywordUtil::save() {
	try {
		// ��ȡ����
		TCHAR filename[MAX_PATH];
		GetSeachWordFile(filename, MAX_PATH);

		std::fstream frecord(filename);
		if (frecord.is_open()) {
			DataRecorder record(frecord);
			std::for_each(data_.begin(), data_.end(), record);

			frecord.close();
		}
	} catch(...) {
	}
	return 0;
}


