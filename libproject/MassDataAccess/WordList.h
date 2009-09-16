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
    bool is_in_set(const std::string &word) const;

	// ���ɾ��DNS
    int add_word(const std::string &word);
	int remote_word(const std::string &word);

	// enumerate
	int enum_words(boost::function<int (const char *)> enum_fun);

	// ��ȡDNS
	// ֮���Բ������ַ�ʽ������Ϊmap����ʹ���±���з���
	int get_first_word(std::string * word) const ;
    int get_next_word(std::string * word,  const std::string &cur_word) const;
protected:
    // �ʻ㼰��������
    typedef std::set<std::string> WORDS_SET;
	WORDS_SET words_set_;;
};

#endif  // _WORDLIST_LIST_H__