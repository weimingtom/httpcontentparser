#pragma once


// CContentList
#include <Guilib1.5\OnTextChanged.h>
#include <set>
#include <string>

class CBaseDlg;

struct RuleChanged {
	virtual void OnAddItem(const CString &str) = 0;
	virtual void OnDelItem(const CString &str) = 0;
	virtual bool ValidateItem(const CString & str, CString &output) = 0;		// ���ַ������ܱ��޸�
};

class RulesList : public OnTextChanged {
public:
	RulesList(CBaseDlg * dlg, RuleChanged * changed);
public:
	virtual void OnDelete(const CString &str);
	virtual void OnBeginEdit(const CString &strOld);
	virtual bool OnEndEdit(const CString &strNew);
	virtual bool OnAdd(const CString &str);

	// Ӧ��
	void Apply();
	// �ظ��޸�ǰ������
	void Reset();

protected:
	void addItem(const CString &str);
	void removeItem(const CString &str);
	bool validateItem(const CString &str, CString &output);
protected:
	CString m_strOld;

	typedef std::set<std::string> STRING_SET;
	STRING_SET added_items;
	STRING_SET remove_items;
	STRING_SET current_items; // ��ǰ�б��е�����DNS

protected:
	RulesList();
	RuleChanged * const changed_;
	CBaseDlg	* dlg_;
};