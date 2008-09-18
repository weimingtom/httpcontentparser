#include "StdAfx.h"
#include ".\SearchRule.h"
#include <assert.h>

SearchRule::SearchRule(void) {
	enabled_ = true;
}

SearchRule::~SearchRule(void) {
}

// �˺����������ö�Ӧ�����������Ƿ���Ҫ�����
int SearchRule::enableCheck(const std::string &search_host, const bool checked) {
	if (search_host_.find(search_host) == search_host_.end()) {
		return -1;
	} else {
		search_host_[search_host] = checked;
		return 0;
	}
}

// ���ȼ��host_name, �������Ҫ���ֱ�ӷ���
// Ȼ�����������Ƿ���word_set����
bool SearchRule::check(const std::string &host_name,  const std::string &search_word) const {
	if (isEnabled() == false) {
		return true; 
	} else if (false == shouldCheck(host_name)) {
		return true;
	} else {
		return checkWord(search_word);
	}
}


// ���Ȳ鿴host_name, �Ƿ������ǵ�host_map����, ���������ֱ�ӷ���false
// ���� �����û����÷���
bool SearchRule::shouldCheck(const std::string &search_host) const {
	SEARCH_HOST::const_iterator iter = search_host_.find(search_host);
	if (search_host_.end() == iter) {
		return false;
	} else {
		return iter->second;
	}
}

//========================================================
// enumerator
void SearchRule::enumBlackWord(Enumerator1<std::string> * enumerator) {
	assert (NULL != enumerator);
	WORD_SET::const_iterator iter = word_set_.begin();
	for (; iter != word_set_.end(); ++iter) {
		enumerator->Enum(*iter);
	}
}
void SearchRule::enumSearchEngine(Enumerator2<std::string, bool> *enumerator) {
	assert (NULL != enumerator);
	SEARCH_HOST::const_iterator iter = search_host_.begin();
	for (; iter != search_host_.end(); ++iter) {
		enumerator->Enum(iter->first, iter->second);
	}
}
//=========================================================
// private members
// ���word�Ƿ�Ϸ�
// ���word�������ǵ�set���У������ǺϷ���, ����true
// ���򷵻�false
bool SearchRule::checkWord(const std::string &word) const {
	if (word_set_.find(word) == word_set_.end()) {
		return true;
	} else {
		return false;
	}
}
