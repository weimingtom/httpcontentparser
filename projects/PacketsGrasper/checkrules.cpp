#include "stdafx.h"
#include <com\Rules_management_exe.h>
#include <com\Rules_management_exe_i.c>
#include "debug.h"

// 2008.6.8
// ���spi��firefox�г�ʼ������ ��ôdllMain�� DLL_PROCESS_ATTACH�г�ʼ��ʱ����
// CoCreateInstance�ǻ���������IEǡǡ�෴....
// ֻע�������������ˣ����˿�����������
// *** ���ԣ����ǿ����ֹcom exe, �᲻��ֱ�ӵ�������Ӧ�ó���Ƿ������أ�������

namespace {

IExeRulesChecker * pRulesChecker_ = NULL;

const TCHAR IE_PROCESS_NAME[] = _T("iexplore");
const TCHAR FIREFOX_PROCESS_NAME[] = _T("firefox");

};
