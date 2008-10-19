// ContentList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\ContentList.h"
#include ".\globalvariable.h"
#include ".\basedlg.h"
#include <comdef.h>
#include <comutil.h>
#include <assert.h>


//===================================
// constructors
RulesList::RulesList(CBaseDlg * dlg, RuleChanged * changed) : dlg_(dlg), changed_(changed) {
	ASSERT (changed != NULL);
	ASSERT( dlg  != NULL);
}
RulesList::RulesList() : dlg_(NULL), changed_(NULL) {
}

//==================================
void RulesList::OnDelete(const CString &str) {
	TRACE("RulesList::OnDelete\n");
	removeItem(str);
	m_strOld = "";
	dlg_->SetModify(true);
}

void RulesList::OnBeginEdit(const CString &strOld) {
	TRACE("RulesList::OnBeginEdit �� %s\n", strOld);
	m_strOld = strOld;
}

bool RulesList::OnEndEdit(const CString &strNew) {
	TRACE("RulesList::OnEndEdit\n");
	// ���������Ӧ�÷�������Ӧ�õ���onDelete
	//if (strNew.GetLength() == 0 && m_strOld.GetLength() != 0) {
	//	removeDNSRule(m_strOld);
	//	return true;
	//}

	if (m_strOld == strNew) {
		m_strOld = ""; // ��ֵ
		return true;
	} else if (strNew.GetLength() == 0) {
		ASSERT(false);
		return false;
	}

	CString result_item;
	if (validateItem(strNew, result_item)) {
		addItem(result_item);
		// ���ܷ��أ���Ҫִ���������
	} else {
		// Ӧ��ɾ����ǰ��
		// AfxMessageBox("The DNS exists in list!");
		return false;
	}

	// ɾ��ԭ�й���
	if (m_strOld.GetLength() != 0) {
		removeItem(m_strOld);
	}

	m_strOld = "";
	dlg_->SetModify(true);
	return true;
}

bool RulesList::OnAdd(const CString &strNew) {
	TRACE("RulesList::OnAdd\n");
	CString result_item;
	if (validateItem(strNew, result_item)) {
		addItem(result_item);
		m_strOld = "";
		return true;
	} else {
		return false;
	}
}

void RulesList::Reset() {
	remove_items.clear();
	added_items.clear();
	current_items.clear();
}
// �˺�����������ӵ�COM�������
void RulesList::Apply() {
	// ����
	STRING_SET::iterator iterDel =	remove_items.begin();
	for (; iterDel != remove_items.end(); ++iterDel) {
		TRACE("remove ");
		TRACE(iterDel->c_str());
		TRACE("\n");
		changed_->OnDelItem(iterDel->c_str());
	}
	remove_items.clear();

	STRING_SET::iterator iterAdd =	added_items.begin();
	for (; iterAdd != added_items.end(); ++iterAdd) {
		TRACE("Add ");
		TRACE(iterAdd->c_str());
		TRACE("\n");
		changed_->OnAddItem(iterAdd->c_str());
	}
	added_items.clear();
}

//====================================
//
void RulesList::addItem(const CString &str) {
	if (str.GetLength() == 0)
		return;

	// �����ɾ���б��д��ڣ���ɾ����
	STRING_SET::iterator iterDel =	remove_items.find((LPCTSTR)str);
	if (iterDel != remove_items.end()) {
		remove_items.erase(iterDel);
	}

	// ��ӵ��б�
	ASSERT(added_items.find((LPCTSTR)str) == added_items.end());
	added_items.insert((LPCTSTR)str);

	// 
	ASSERT(current_items.find((LPCTSTR)str) == current_items.end());
	current_items.insert((LPCTSTR)str);
}

// �Ƴ�һ��
void RulesList::removeItem(const CString &str) {
	if (str.GetLength() == 0)
		return;

	// ����ӱ�����ɾ��
	STRING_SET::iterator iterAdd =	added_items.find((LPCTSTR)str);
	if (iterAdd != added_items.end()) {
		added_items.erase(iterAdd);
	}

	// ��ӵ�ɾ���б�
	ASSERT( remove_items.find((LPCTSTR)str) == remove_items.end());
	remove_items.insert((LPCTSTR)str);

	// ��������ڵ�ǰ���б��У���ɾ����
	STRING_SET::iterator cur =  current_items.find((LPCTSTR)str);
	ASSERT( cur != current_items.end());
	current_items.erase(cur);
}

bool RulesList::validateItem(const CString &str, CString &output) {
	// ����Ѿ����ڹ�����
	ASSERT(str.GetLength() != 0);

	// �������б����Ѿ�������....
	if (current_items.find((LPCTSTR)str) != current_items.end()) {
		return false;
	}

	// ��Ҫ��֤���Ƿ���һ����ȷ��DNS
	return changed_->ValidateItem(str, output);
}