#include "StdAfx.h"
#include ".\SearchRule.h"
#include <assert.h>
#include <utility/strutility.h>

SearchRule::SearchRule(void) {
	defaultSetting();
}

SearchRule::~SearchRule(void) {
}

// �˺����������ö�Ӧ�����������Ƿ���Ҫ�����
int SearchRule::enableCheck(const std::string &search_host, const bool checked) {
	setModified(true);

	// �������.com�ȣ�Ҫȥ��������������
	assert(search_host.find(".") == -1);

	search_host_[search_host] = checked;
	return 0;
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
	SEARCH_HOST::const_iterator iter = search_host_.begin();
	for (; iter != search_host_.end(); ++iter) {
		if (std::string::npos != search_host.find(iter->first)) {
			return iter->second;
		}
	}

	return false;
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


//============================================================
// XML
int SearchRule::parseConfig(TiXmlElement * item_root) {
	getSearchRule(item_root);
	return 0;
}
TiXmlElement * SearchRule::saveConfig(TiXmlElement * item_root) {
	return saveSearchRule(item_root);	// ����Search rules
}

//========================================================
// Search Rules
int SearchRule::setSearchEngineCheck(const TCHAR *search_engine, const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	addSearchHost(search_engine);
	enableCheck(search_engine, enabled);
	return 0;
}


int SearchRule::getSearchRule(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement * ele = node->ToElement();
		if (_tcscmp(node->Value(), CONFIG_NODE_SEARCH_ENGINES) == 0) {
			assert (NULL != ele);
			getSearchEngineSetting(ele);
		} else if (_tcscmp(node->Value(), CONFIG_NODE_BLACK_SEARCHWORD) == 0) {
			assert (NULL != ele);
			getSearchBlackWord(ele);
		} else {
		}

		node = node->NextSibling();
	}
	return 0;
}

// ��ȡSearch  ����
// Search�����漰�� ��������� Blacksearch word��
// ��������������в�ͬ
int SearchRule::getSearchBlackWord(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			addBlackSearchWord(ele->GetText());
		}

		node = node->NextSibling();
	}
	return 0;
}

int SearchRule::getSearchEngineSetting(TiXmlElement * rule_root) {
	TiXmlNode * node = rule_root->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele) {
			setSearchEngineCheck(ele->Attribute(CONFIG_CONST_NAME),
				ele->Attribute(CONFIG_CONST_ENABLE));
		}

		node = node->NextSibling();
	}
	return 0;
}

//==========================================================
// search rules
namespace {
class EnumBlackWord : public Enumerator1<std::string> {
public:
	virtual int Enum(const std::string &data1) {
		TiXmlElement * blackword = new TiXmlElement(CONFIG_NODE_BLACK_SEARCHWORD);
		TiXmlText * word = new TiXmlText(data1);
		blackword->LinkEndChild(word);
		rule_root_->LinkEndChild(blackword);

		return 0;
	}
public:
	EnumBlackWord(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
	}
private:
	TiXmlElement * rule_root_;
};

class EnumSearchEngine : public Enumerator2<std::string, bool> {
public:
	virtual int Enum(const std::string &data1, const bool enabled) {
		TiXmlElement * searchengine_item = new TiXmlElement(CONDIG_NODE_SEARCH_ENGINE_ITEM);
		searchengine_item->SetAttribute(CONFIG_CONST_NAME, data1);
		searchengine_item->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(enabled));
		rule_root_->LinkEndChild(searchengine_item);

		return 0;
	}
public:
	EnumSearchEngine(TiXmlElement * rule_root) {
		rule_root_ = rule_root;
	}
private:
	TiXmlElement * rule_root_;
};
};
TiXmlElement *  SearchRule::saveSearchRule(TiXmlElement *root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_NODE_RULE_ITEM);
	if (NULL == rule_root) {
		return NULL;
	}

	// ��������
	rule_root->SetAttribute(CONFIG_CONST_NAME, CONFIG_NODE_NAME_SEARCH);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(enabled_));

	// ����black word
	TiXmlElement * blackword = new TiXmlElement(CONFIG_NODE_BLACK_SEARCHWORD);
	enumBlackWord(&EnumBlackWord(blackword));
	rule_root->LinkEndChild(blackword);

	TiXmlElement *search_engine = new TiXmlElement(CONFIG_NODE_SEARCH_ENGINES);
	enumSearchEngine(&EnumSearchEngine(search_engine));
	rule_root->LinkEndChild(search_engine);

	root->LinkEndChild(rule_root);
	return rule_root;
}