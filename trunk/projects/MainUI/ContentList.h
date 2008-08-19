#pragma once


// CContentList
#include <Guilib1.5\OnTextChanged.h>
#include <set>
#include <string>


class RulesList : public OnTextChanged {
public:
	RulesList();
public:
	virtual void OnDelete(const CString &str);
	virtual void OnBeginEdit(const CString &strOld);
	virtual bool OnEndEdit(const CString &strNew);
	virtual bool OnAdd(const CString &str);


	// ”¶”√
	void OnApply();

protected:
	void addDNSRule(const CString &str);
	void removeDNSRule(const CString &str);
	bool validateDNS(const CString &str);
protected:
	CString m_strOld;

	typedef std::set<std::string> STRING_SET;
	STRING_SET DNSSet;
	STRING_SET addedDNS;
	STRING_SET removedDNS;
};

