#ifndef _WORDLIST_LIST_H__
#define _WORDLIST_LIST_H__

#include <map>
#include <set>
#include <boost/function.hpp>

// 保存于网站相关的数据
class WordList {
public:
	WordList(void);
	~WordList(void);
public:
    bool is_in_set(const std::string &dns_name, const std::string &search_engine) const;

	// 添加删除DNS
    int add_word(const std::string &word, const std::string &engine);
	int remote_word(const std::string &word, const std::string &engine);

	// enumerate
	int enum_words(boost::function<int (const char *, const char *)> enum_fun);

	// 获取DNS
	// 之所以采用这种方式，是因为map不能使用下表进行访问
	int get_first_word(std::string * word, std::string * search_engine);
    int get_next_word(const std::string &name, std::string * word, std::string * search_engine);
protected:
    // 词汇及搜索引擎
    typedef std::multimap<std::string, std::string> WORDS_SET;
	WORDS_SET words_set_;;
};

#endif  // _WORDLIST_LIST_H__