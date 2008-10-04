#ifndef _SETTING_SEARCHRULE_H__
#define _SETTING_SEARCHRULE_H__

#include <string>
#include <set>
#include <map>
#include <Enumerate.h>
#include <settingitem.h>

// 用来记录Search Rule的实现
class SearchRule : public SettingItem {
public:
	SearchRule(void);
	~SearchRule(void);
public:
	int enableCheck(const std::string &search_host, const bool checked);
	void addBlackSearchWord(const char *word) {
		word_set_.insert(word);
	}

	void addSearchHost(const std::string &search_host) {
		search_host_.insert(std::make_pair(search_host, true));
	}

	bool check(const std::string &host_name, const std::string &search_word) const;

	bool shouldCheck(const std::string &search_host) const;
	// enumerate
	void enumBlackWord(Enumerator1<std::string> * enumerator);
	void enumSearchEngine(Enumerator2<std::string, bool> *enumerator);
protected:
	typedef std::set<std::string> WORD_SET;
	WORD_SET word_set_;

	typedef std::map<std::string, bool> SEARCH_HOST;
	SEARCH_HOST search_host_;

	bool checkWord(const std::string &word) const;
};

#endif  // _SETTING_SEARCHRULE_H__
