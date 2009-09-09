#include "StdAfx.h"
#include ".\fileinfotest.h"
#include <apputility\fileinfo.h>
#include <iostream>

FileInfoTest::FileInfoTest(void) {
}

FileInfoTest::~FileInfoTest(void) {
}

void FileInfoTest::testSVCHOST() {
	using namespace std;

	CFileInfo fileinfo("C:\\WINDOWS\\system32\\svchost.exe");
	cout<<"C:\\WINDOWS\\system32\\svchost.exe"<<endl;
	cout<<"\tProduct name : " << fileinfo.getProductName()<<endl;
	cout<<"\tCompany name : " << fileinfo.getCompanyName()<<endl;
	cout<<"\tDescription : " << fileinfo.getDescription()<<endl;
}
