#ifndef _WORDLIST_LIST_H__
#define _WORDLIST_LIST_H__

#include <map>
#include <set>
#include <boost/function.hpp>

// ��������վ��ص�����
class WordList {
public:
	WordList(void);
	~WordList(void);
public:
    bool is_in_set(const std::string &dns_name, const std::string &search_engine) const;

	// ���ɾ��DNS
    int add_word(const std::string &word, const std::string &engine);
	int remote_word(const std::string &word, const std::string &engine);

	// enumerate
	int enum_words(boost::function<int (const char *, const char *)> enum_fun);

	// ��ȡDNS
	// ֮���Բ������ַ�ʽ������Ϊmap����ʹ���±���з���
	int get_first_word(std::string * word, std::string * search_engine);
    int get_next_word(const std::string &name, std::string * word, std::string * search_engine);
protected:
    // �ʻ㼰��������
    typedef std::multimap<std::string, std::string> WORDS_SET;
	WORDS_SET words_set_;;
};

#endif  // _WORDLIST_LIST_H__