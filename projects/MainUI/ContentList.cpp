// ContentList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "ContentList.h"
#include "globalvariable.h"

#include <comdef.h>
#include <comutil.h>

//===================================
// constructors
RulesList::RulesList() {
}

//==================================
void RulesList::OnDelete(const CString &str) {
	TRACE("RulesList::OnDelete\n");
	removeDNSRule(str);
	m_strOld = "";
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

	if (validateDNS(strNew)) {
		addDNSRule(strNew);
		// ���ܷ��أ���Ҫִ���������
	} else {
		// Ӧ��ɾ����ǰ��
		// AfxMessageBox("The DNS exists in list!");
		return false;
	}

	// ɾ��ԭ�й���
	if (m_strOld.GetLength() != 0) {
		removeDNSRule(m_strOld);
	}

	m_strOld = "";
	return true;
}

bool RulesList::OnAdd(const CString &strNew) {
	TRACE("RulesList::OnAdd\n");
	if (validateDNS(strNew)) {
		addDNSRule(strNew);
		m_strOld = "";
		return true;
	} else {
		return false;
	}
}

// �˺�����������ӵ�COM�������
void RulesList::OnApply() {
	// ����
	STRING_SET::iterator iterDel =	removedDNS.begin();
	for (; iterDel != removedDNS.end(); ++iterDel) {
		TRACE("remove ");
		TRACE(iterDel->c_str());
		TRACE("\n");
		g_dnssetting->removeBlackDNS(_bstr_t(iterDel->c_str()));
	}
	removedDNS.clear();

	STRING_SET::iterator iterAdd =	addedDNS.begin();
	for (; iterAdd != addedDNS.end(); ++iterAdd) {
		TRACE("Add ");
		TRACE(iterAdd->c_str());
		TRACE("\n");
		g_dnssetting->addBlackDNS(_bstr_t(iterAdd->c_str()));
	}
	addedDNS.clear();
}

//====================================
//
void RulesList::addDNSRule(const CString &str) {
	if (str.GetLength() == 0)
		return;

	// �����ɾ���б��д��ڣ���ɾ����
	STRING_SET::iterator iterDel =	removedDNS.find((LPCTSTR)str);
	if (iterDel != removedDNS.end()) {
		removedDNS.erase(iterDel);
	}

	// ��ӵ��б�
	ASSERT(addedDNS.find((LPCTSTR)str) == addedDNS.end());
	addedDNS.insert((LPCTSTR)str);

	// 
	ASSERT(currentDNS.find((LPCTSTR)str) == currentDNS.end());
	currentDNS.insert((LPCTSTR)str);
}

// �Ƴ�һ��
void RulesList::removeDNSRule(const CString &str) {
	if (str.GetLength() == 0)
		return;

	// ����ӱ�����ɾ��
	STRING_SET::iterator iterAdd =	addedDNS.find((LPCTSTR)str);
	if (iterAdd != addedDNS.end()) {
		addedDNS.erase(iterAdd);
	}

	// ��ӵ�ɾ���б�
	ASSERT( removedDNS.find((LPCTSTR)str) == removedDNS.end());
	removedDNS.insert((LPCTSTR)str);

	// ��������ڵ�ǰ���б��У���ɾ����
	STRING_SET::iterator cur =  currentDNS.find((LPCTSTR)str);
	ASSERT( cur != currentDNS.end());
	currentDNS.erase(cur);
}

bool RulesList::validateDNS(const CString &str) {
	// ����Ѿ����ڹ�����
	ASSERT(str.GetLength() != 0);

	// �������б����Ѿ�������....
	if (currentDNS.find((LPCTSTR)str) != currentDNS.end()) {
		return false;
	}

	// ��Ҫ��֤���Ƿ���һ����ȷ��DNS
	return true;
}