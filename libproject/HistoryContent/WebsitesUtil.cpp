#include "stdafx.h"
#include ".\websitesUtil.h"
#include <apputility\apputility.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// ===================
const char * WebsitesUtil::SEPERATOR = "&";
const char * WebsitesUtil::NEW_LINE = "\n";

WebsitesUtil::WebsitesUtil(void) {
}

WebsitesUtil::~WebsitesUtil(void) {
}


void WebsitesUtil::clear() {
	SEARCH_WORD_DATA::iterator iter = data_.begin();
	data_.clear();
}

// 专门用于枚举数据对象
int WebsitesUtil::enumerate(DataEnumerator * const enumerator) {
	assert (NULL != enumerator);

	SEARCH_WORD_DATA::iterator iter = data_.begin();
	for (; iter != data_.end(); ++iter) {
		enumerator->DealItemData(iter->first, iter->second);
	}
	return 0;
}

int WebsitesUtil::getSize() const {
	return static_cast<int>(data_.size());
}
int WebsitesUtil::getFirst(std::string *name, WEBSITE_DATA * data) const {
	assert (NULL != name);
	SEARCH_WORD_DATA::const_iterator iter = data_.begin();
	if (data_.end() != iter) {
		*name = iter->first;
		*data = iter->second;
		return 1;
	} else {
		return 0;
	}
}
int WebsitesUtil::getNext(const std::string &cur, std::string * name, WEBSITE_DATA * data) const {
	SEARCH_WORD_DATA::const_iterator iter = data_.upper_bound(cur);
	if (iter != data_.end()) {
		*name = iter->first;
		*data = iter->second;
		return -1;
	} else {
		return 0;
	}
}

int WebsitesUtil::addWebsite(const std::string &website) {
	// 保存为FILETIME, 由于SYSTEMTIME站16字节，而FILETIME只需要8字节
	// 为了方便读取这里使用将SYSTEMTIME转换为FILETIME
	SYSTEMTIME tm;
	GetLocalTime(&tm);

	SEARCH_WORD_DATA::iterator iter = data_.find(website);
	if (data_.end() == iter) {
		// 如果不存在
		WEBSITE_DATA item;
		SystemTimeToFileTime(&tm, &item.latest_visit);
		item.visit_count = 1;
		data_.insert(std::make_pair(website, item));
	} else {
		// 如果存在则更改最近一次的搜索时间及使用的搜索引擎
		iter->second.visit_count += 1;
		SystemTimeToFileTime(&tm, &iter->second.latest_visit);
	}
	return 0;
}

int WebsitesUtil::insertItem(const std::string &website, const std::string & last_time , const std::string &times ) {
	// 将字符传转化为
	WEBSITE_DATA item;
	
	TCHAR *p;
	item.latest_visit.dwHighDateTime= static_cast<DWORD>(strtol(last_time.c_str(), &p, 10));
	item.latest_visit.dwLowDateTime  = static_cast<DWORD>(strtol(p, &p, 10));	
	item.visit_count = atoi(times.c_str());					// 搜索次数

	// 加入到map当中
	data_[website] = item;
	return 0;
}

// 解析一行
// 格式为  keyword&1&&23
int WebsitesUtil::parseString(const std::string &line) {
	int firstSep = static_cast<int>(line.find(SEPERATOR));
	if (-1 == firstSep) return -1;

	int secSep = static_cast<int>(line.find(SEPERATOR,  firstSep + 1));
	if (-1 == secSep) return -1;

	std::string keyword = line.substr(0, firstSep );		// 关键字
	std::string lasttime = line.substr(firstSep + 1, secSep - firstSep -1);		// 上次访问时间
	std::string  times = line.substr(secSep + 1, line.length());	// 搜索次数

	insertItem(keyword, lasttime, times);
	return 0;
}

// 读取配置文件
int WebsitesUtil::load(const std::string &filename) {
	try {
		// 获取名称
		using namespace std;
		ifstream  file(filename.c_str(), std::ios::out);
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

// 将现有数据保存到配置文件当中
int WebsitesUtil::save(const std::string &filename) {
	try {
		// 获取名称
		std::fstream frecord(filename.c_str(), std::ios::out);
		if (frecord.is_open()) {
			DataRecorder record(frecord);
			std::for_each(data_.begin(), data_.end(), record);

			frecord.close();
		}
	} catch(...) {
	}
	return 0;
}


