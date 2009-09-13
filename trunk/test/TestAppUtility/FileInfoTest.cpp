#include "StdAfx.h"
#include ".\fileinfotest.h"
#include <apputility\fileinfo.h>
#include <iostream>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


void testSVCHOST() {
	using namespace std;

	CFileInfo fileinfo("C:\\WINDOWS\\system32\\svchost.exe");
	cout<<"C:\\WINDOWS\\system32\\svchost.exe"<<endl;
	cout<<"\tProduct name : " << fileinfo.getProductName()<<endl;
	cout<<"\tCompany name : " << fileinfo.getCompanyName()<<endl;
	cout<<"\tDescription : " << fileinfo.getDescription()<<endl;
}
