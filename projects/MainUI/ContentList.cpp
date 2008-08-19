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
	removeDNSRule(str);
}

void RulesList::OnBeginEdit(const CString &strOld) {
	m_strOld = strOld;
}

bool RulesList::OnEndEdit(const CString &strNew) {
	// 此种情况不应该发生，他应该调用onDelete
	//if (strNew.GetLength() == 0 && m_strOld.GetLength() != 0) {
	//	removeDNSRule(m_strOld);
	//	return true;
	//}

	if (m_strOld == strNew) {
		return true;
	} else if (strNew.GetLength() == 0) {
		ASSERT(false);
		return false;
	}

	if (validateDNS(strNew)) {
		addDNSRule(strNew);
		// 不能返回，还要执行下面代码
	} else {
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
	if (validateDNS(strNew)) {
		addDNSRule(strNew);
		return true;
	} else {
		return false;
	}
}

// 此函数将规则添加到COM组件当中
void RulesList::OnApply() {
}

//====================================
//
void RulesList::addDNSRule(const CString &str) {
	ASSERT(DNSSet.find((LPCTSTR)str) == DNSSet.end());
	DNSSet.insert((LPCTSTR)str);

	ASSERT (NULL != g_globalSetting);
	g_globalSetting->addBlackDNS(_bstr_t(str));
}

// 移除一个
void RulesList::removeDNSRule(const CString &str) {
	if (str.GetLength() == 0)
		return;

	STRING_SET::iterator iter = DNSSet.find((LPCTSTR)str);
	ASSERT( iter != DNSSet.end());
	DNSSet.erase(iter);


	ASSERT (NULL != g_globalSetting);
	g_globalSetting->removeBlackDNS(_bstr_t(str));
}

bool RulesList::validateDNS(const CString &str) {
	// 如果已经存在规则了
	if (DNSSet.find((LPCTSTR)str) != DNSSet.end()) {
		return false;
	}

	// 还要验证他是否是一个正确的DNS
	return true;
}