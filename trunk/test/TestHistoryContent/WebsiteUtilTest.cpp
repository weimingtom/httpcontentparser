#include "StdAfx.h"
#include ".\websiteutiltest.h"

WebsiteUtilTest::WebsiteUtilTest(void) {
}

WebsiteUtilTest::~WebsiteUtilTest(void) {
}


namespace {
	void printDataItem(const std::string &name, const WebsitesUtil::WEBSITE_DATA &data) {
		using namespace std;
		TCHAR buf[MAX_PATH];
		
		cout<<"website :" << name << endl
			<<"\tvisit count : " <<data.visit_count << endl
			<<"\tvisit seach time: " << timeutility::USFormatTime(data.latest_visit, buf, MAX_PATH)<<endl;
	}	
};



void WebsiteUtilTest::testReadWebisitesGetNext() {
	WebsitesUtil util;
	util.addWebsite("www.sina.com");
	util.addWebsite("www.google.com");
	util.addWebsite("www.sina.com");
	util.addWebsite("www.baidu.com");
	util.addWebsite("www.sohu.com");
	util.addWebsite("www.sina.com");
	util.addWebsite("www.sohu.com");
	util.addWebsite("www.yahoo.com");
	util.addWebsite("www.google.cn");
	util.addWebsite("www.163.com");
	util.save(".\\textcase1.txt");
}

void WebsiteUtilTest::testReadWebisitesEnumerator() {
	WebsitesUtil util;
	util.load(".\\textcase1.txt");

	using namespace std;
	string str, next;
	WebsitesUtil::WEBSITE_DATA data;
	util.getFirst(&str, &data);
	printDataItem(str, data);

	while (util.getNext(str, &next, &data) != 0) {
		printDataItem(str, data);
		str = next;
	}
}
void WebsiteUtilTest::testReadWebisitesWordsFileOper() {
}