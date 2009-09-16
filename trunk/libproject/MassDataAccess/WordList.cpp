#include "stdafx.h"
#include "WordList.h"
#include <assert.h>

WordList::WordList(void) {
}

WordList::~WordList(void) {
}

// 获取DNS列表
/*int WordList::get_first_word(std::string * word, std::string * search_engine) {
	if (words_set_.size() == 0) {
		return -1;
	} else {
        *word =  words_set_.begin()->first;
        *search_engine = words_set_.begin()->second;
	}
}

std::string WordList::get_next_website(const std::string &name) {
	assert (name.length() != 0);
	if (name.length() == 0) {
		return name;
	} else {
		WORDS_SET::iterator iter = words_set_.upper_bound(name);
		if (iter == words_set_.end()) {
			return std::string("");
		} else {
			return iter->second;
		}
	}
}
*/

//==================================
// 测试DNS是否在黑白名单当中
bool WordList::is_in_set(const std::string &word, const std::string &search_engine) const {
    WORDS_SET::const_iterator iter = words_set_.lower_bound(word);
    WORDS_SET::const_iterator iter_end = words_set_.upper_bound(word);
    if (iter != iter_end) {
        if (iter->second == search_engine) {
            return true;
        }

        iter++;
    }
    return false;
}

//=====================================
// 从DNS中移除
int WordList::remote_word(const std::string &word, const std::string &engine) {
    WORDS_SET::iterator iter = words_set_.lower_bound(word);
    WORDS_SET::iterator iter_end = words_set_.upper_bound(word);
	if (iter != iter_end) {
        if (iter->second == engine) {
            words_set_.erase(iter);
		    return 0;
        }

        iter++;
	}
	return 1;
}

int WordList::add_word(const std::string &word, const std::string &engine) {
	// 去除DNS MAIN name
	words_set_.insert(std::make_pair(word, engine));
    return 0;
}


int WordList::enum_words(boost::function<int (const char *, const char *)> enum_fun) {
	assert (NULL != enumerator);

	WORDS_SET::const_iterator iter = words_set_.begin();
	for (; iter != words_set_.end(); ++iter) {
        enum_fun(iter->first.c_str(), iter->second.c_str());
	}

    return 0;
}

