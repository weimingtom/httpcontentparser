#include "StdAfx.h"
#include ".\SearchRule.h"

SearchRule::SearchRule(void) {
}

SearchRule::~SearchRule(void) {
}

// 此函数负责设置对应的搜索引擎是否需要被检测
int SearchRule::enableCheck(const std::string &search_host, const bool checked) {
	if (search_host_.find(search_host) == search_host_.end()) {
		return -1;
	} else {
		search_host_[search_host] = checked;
		return 0;
	}
}

// 首先检测host_name, 如果不需要检测直接返回
// 然后检测搜索词是否在word_set当中
bool SearchRule::check(const std::string &host_name,
					   const std::string &search_word) const {
	if (false == shouldCheck(host_name)) {
		return true;
	} else {
		return checkWord(search_word);
	}
}

// 检测word是否合法
// 如果word不在我们的set当中，则他是合法的, 返回true
// 否则返回false
bool SearchRule::checkWord(const std::string &word) const {
	if (word_set_.find(word) == word_set_.end()) {
		return true;
	} else {
		return false;
	}
}

// 首先查看host_name, 是否在我们的host_map当中, 如果不存在直接返回false
// 否则， 根据用户设置返回
bool SearchRule::shouldCheck(const std::string &search_host) const {
	SEARCH_HOST::const_iterator iter = search_host_.find(search_host);
	if (search_host_.end() == iter) {
		return false;
	} else {
		return iter->second;
	}
}