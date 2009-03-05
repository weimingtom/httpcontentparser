#ifndef _SETTING_SEARCHRULE_H__
#define _SETTING_SEARCHRULE_H__

//#include <string>
//#include <set>
//#include <map>
#include <Enumerate.h>
#include <settingitem.h>
#include <configitem.h>
#include <xmldefined.h>

// 用来记录Search Rule的实现
class SearchRule : public SettingItem , public ConfigItem {
public:
	SearchRule(void);
	~SearchRule(void);
public:
	int enableCheck(const std::string &search_host, const bool checked);
	void addBlackSearchWord(const char *word) {
		SettingItem::setModified(true);
		word_set_.insert(word);
	}

	void removeBlackSeachWord(const char * word) {
		WORD_SET::iterator iter = word_set_.find(word);
		if (word_set_.end() != iter) {
			SettingItem::setModified(true);
			word_set_.erase(iter);
		}
	}

	void addSearchHost(const std::string &search_host) {
		SettingItem::setModified(true);
		search_host_.insert(std::make_pair(search_host, true));
	}

	bool check(const std::string &host_name, const std::string &search_word) const;

	bool shouldCheck(const std::string &search_host) const;
	bool setting_shouldCheck(const std::string &search_host) const;
	// enumerate
	void enumBlackWord(Enumerator1<std::string> * enumerator);
	void enumSearchEngine(Enumerator2<std::string, bool> *enumerator);
protected:
	typedef std::set<std::string> WORD_SET;
	WORD_SET word_set_;

	typedef std::map<std::string, bool> SEARCH_HOST;
	SEARCH_HOST search_host_;

	bool checkWord(const std::string &word) const;

	// XML文件
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * item_root);
private:
	// 搜索规则
	int getSearchRule(TiXmlElement * ele);
	int setSearchEngineCheck(const TCHAR *word);
	int getSearchBlackWord(TiXmlElement * ele);
	int getSearchEngineSetting(TiXmlElement * ele);
	int setSearchEngineCheck(const TCHAR *search_engine, const TCHAR *enable);

	TiXmlElement *  saveSearchRule(TiXmlElement *rules_root);
};

#endif  // _SETTING_SEARCHRULE_H__
