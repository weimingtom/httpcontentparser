// ContentList.cpp : 实现文件
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
	TRACE("RulesList::OnBeginEdit ： %s\n", strOld);
	m_strOld = strOld;
}

bool RulesList::OnEndEdit(const CString &strNew) {
	TRACE("RulesList::OnEndEdit\n");
	// 此种情况不应该发生，他应该调用onDelete
	//if (strNew.GetLength() == 0 && m_strOld.GetLength() != 0) {
	//	removeDNSRule(m_strOld);
	//	return true;
	//}

	if (m_strOld == strNew) {
		m_strOld = ""; // 充值
		return true;
	} else if (strNew.GetLength() == 0) {
		ASSERT(false);
		return false;
	}

	if (validateDNS(strNew)) {
		addDNSRule(strNew);
		// 不能返回，还要执行下面代码
	} else {
		// 应该删除当前项
		// AfxMessageBox("The DNS exists in list!");
		return false;
	}

	// 删除原有规则
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

// 此函数将规则添加到COM组件当中
void RulesList::OnApply() {
	// 喊出
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

	// 如果在删除列表中存在，则删除它
	STRING_SET::iterator iterDel =	removedDNS.find((LPCTSTR)str);
	if (iterDel != removedDNS.end()) {
		removedDNS.erase(iterDel);
	}

	// 添加到列表
	ASSERT(addedDNS.find((LPCTSTR)str) == addedDNS.end());
	addedDNS.insert((LPCTSTR)str);

	// 
	ASSERT(currentDNS.find((LPCTSTR)str) == currentDNS.end());
	currentDNS.insert((LPCTSTR)str);
}

// 移除一个
void RulesList::removeDNSRule(const CString &str) {
	if (str.GetLength() == 0)
		return;

	// 从添加表列中删除
	STRING_SET::iterator iterAdd =	addedDNS.find((LPCTSTR)str);
	if (iterAdd != addedDNS.end()) {
		addedDNS.erase(iterAdd);
	}

	// 添加到删除列表
	ASSERT( removedDNS.find((LPCTSTR)str) == removedDNS.end());
	removedDNS.insert((LPCTSTR)str);

	// 如果存在于当前的列表当中，则删除它
	STRING_SET::iterator cur =  currentDNS.find((LPCTSTR)str);
	ASSERT( cur != currentDNS.end());
	currentDNS.erase(cur);
}

bool RulesList::validateDNS(const CString &str) {
	// 如果已经存在规则了
	ASSERT(str.GetLength() != 0);

	// 如果添加列表中已经存在了....
	if (currentDNS.find((LPCTSTR)str) != currentDNS.end()) {
		return false;
	}

	// 还要验证他是否是一个正确的DNS
	return true;
}