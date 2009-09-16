#include "stdafx.h"
#include "WordList.h"
#include <assert.h>

WordList::WordList(void) {
}

WordList::~WordList(void) {
}

// 获取搜索词汇
int WordList::get_first_word(std::string * word) const {
    assert (word != NULL);
	if (words_set_.size() == 0) {
		return -1;
	} else {
        *word =  (*words_set_.begin());
        return 0;
	}
}

int WordList::get_next_word(std::string * word,  const std::string &cur_word) const {
    assert(NULL != word);
    assert(cur_word.length() > 0);

    WORDS_SET::const_iterator iter = words_set_.find(cur_word);
    if (iter == words_set_.end()) {
        *word = "";
        return -1;
    }
    if (++iter == words_set_.end()) {
        *word = "";
        return -1;
    }

    *word = *iter;
    return 0;
}

//==================================
// 测试search word是否在黑白名单当中
bool WordList::is_in_set(const std::string &word) const {
    WORDS_SET::const_iterator iter = words_set_.find(word);
    if (iter != words_set_.end()) {
            return true;
    } else {
        return false;
    }
}

//=====================================
// 从search word中移除
int WordList::remote_word(const std::string &word) {
    assert(word.length() != 0);
    WORDS_SET::iterator iter = words_set_.find(word);
    if (iter != words_set_.end()) {
        words_set_.erase(iter);
        return 0;
    } else {
        return 1;
    }
}

int WordList::add_word(const std::string &word) {
    assert(word.length() != 0);
    words_set_.insert(word);
    return 0;
}


int WordList::enum_words(boost::function<int (const char *)> enum_fun) {
	WORDS_SET::const_iterator iter = words_set_.begin();
	for (; iter != words_set_.end(); ++iter) {
        enum_fun((*iter).c_str());
	}

    return 0;
}

