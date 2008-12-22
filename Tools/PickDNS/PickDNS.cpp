// PickDNS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

map<string, string> DNSs;

void addtoMap(const string &dns, const string &main_dns)
{
	map<string, string>::iterator iter = DNSs.find(main_dns);
	if (DNSs.end() != iter) {
		if (iter->second.length() > dns.length()) {
			iter->second = dns;
		}
	} else {
		DNSs.insert(make_pair(main_dns, dns));
	}
}

void writeToFile(const char * filename) {
	fstream f(filename, ios::out);

	map<string, string>::iterator iter = DNSs.begin();
	for (; iter != DNSs.end(); ++iter) {
		f.write(iter->second.c_str(), iter->second.length());
		f.write("\n", 1);
	}

	f.close();
}
char * getBrief(char *buffer) {
	char * result = buffer;
	if (buffer == strstr(buffer, "http://")) {
		result += strlen("http://");
	}

	char * p = strstr(result, "/");
	if (NULL != p) {
		result[p - result] = '\0';
	}

	return result;
}
int _tmain(int argc, _TCHAR* argv[])
{
	const char * filename = ".\\data\\url_english.txt";
	ifstream infile(filename);

	char buffer[1024];
	char full[1024];
	string line;
	while(std::getline(infile, line, '\n')) {
		get_main_dns_name(buffer, 1024, line.c_str());

		strcpy(full, line.c_str());
		addtoMap(getBrief(full), buffer);
	}

	writeToFile(".\\tmp.txt");

	return 0;
}

