// tinyXML_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#ifndef _DEBUG
#pragma comment(lib, "tinyxml_STL.lib")
#else
#pragma comment(lib, "tinyxmld_STL.lib")
#endif

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	TiXmlDocument doc("e:\\workspace\\httpcontent\\debug\\config.xml");
	if (!doc.LoadFile()) {
		cout<<doc.ErrorDesc()<<endl;
		return 1;
	}
	
	TiXmlElement * root = doc.RootElement();
	if (NULL == root) {
		return 0;
	}

	TiXmlNode *node = root->FirstChild();
	while (node != NULL) {
		//node->a
		// ��ȡ������һ���ڵ�
		node = node->NextSibling();
	}


	return 0;
}

