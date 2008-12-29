#include "StdAfx.h"
#include ".\iaccessnetworktest.h"
#include ".\comtestutility.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <typeconvert.h>
#include <time.h>
#include <stdio.h>

namespace {
void unsetBlocktime(const int day, const int hour);
void setBlocktime(const int day, const int hour) ;
bool accessNetword();
};

IAccessNetworkTest::IAccessNetworkTest(void) {
}

IAccessNetworkTest::~IAccessNetworkTest(void) {
}

// 在父子两种模式下运行
void IAccessNetworkTest::TestTwoModel() {
	GetInChildMode();
	time_t t;
	struct tm * local;

	// 获取时间
	time(&t);
	local= localtime(&t);


	unsetBlocktime(local->tm_wday, local->tm_hour);
	bool accessable = accessNetword();
	CPPUNIT_ASSERT (true == accessable);

	time(&t);
	local= localtime(&t);
	setBlocktime(local->tm_wday, local->tm_hour);
	accessable = accessNetword();
	CPPUNIT_ASSERT (false == accessable);

	GetInParentModel();
	accessable = accessNetword();
	CPPUNIT_ASSERT (true == accessable);
	GetInChildMode();
	accessable = accessNetword();
	CPPUNIT_ASSERT (false == accessable);
}
void IAccessNetworkTest::TestSetAndGetBlockTime() {
	GetInChildMode();
	time_t t;
	struct tm * local;

	// 获取时间
	time(&t);
	local= localtime(&t);


	unsetBlocktime(local->tm_wday, local->tm_hour);
	bool accessable = accessNetword();
	CPPUNIT_ASSERT (true == accessable);

	time(&t);
	local= localtime(&t);
	setBlocktime(local->tm_wday, local->tm_hour);
	accessable = accessNetword();
	CPPUNIT_ASSERT (false == accessable);


	time(&t);
	local= localtime(&t);
	unsetBlocktime(local->tm_wday, local->tm_hour);
	accessable = accessNetword();
	CPPUNIT_ASSERT (true == accessable);
}


namespace {
bool accessNetword() {
	bool accessable;
	try {
		CoInitialize(NULL);

		// 初始化
		IAccessNetwork *accessNetword = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER, IID_IAccessNetwork, (LPVOID*)&accessNetword);
		if (FAILED(hr)) {
			CPPUNIT_ASSERT(false);
			return false;
		}

		VARIANT_BOOL varbool_accessable;
		accessNetword->accessNetwork(&varbool_accessable);
		accessable = convert(varbool_accessable);
		CoUninitialize(); 

	} catch (_com_error &) {
		CoUninitialize(); 
		return false;
	}

	return accessable;
}

void setBlocktime(const int day, const int hour) {
	try {
		CoInitialize(NULL);

		// 初始化
		IAccessNetwork *accessNetword = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER, IID_IAccessNetwork, (LPVOID*)&accessNetword);
		if (FAILED(hr)) {
			CPPUNIT_ASSERT(false);
			return;
		}

		accessNetword->setBlockTime(day, hour);
		CoUninitialize(); 

	} catch (_com_error &) {
		CoUninitialize(); 
	}

}

void unsetBlocktime(const int day, const int hour) {
	try {
		CoInitialize(NULL);

		// 初始化
		IAccessNetwork *accessNetword = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER, IID_IAccessNetwork, (LPVOID*)&accessNetword);
		if (FAILED(hr)) {
			CPPUNIT_ASSERT(false);
			return;
		}

		accessNetword->removeBlockTime(day, hour);
		CoUninitialize(); 

	} catch (_com_error &) {
		CoUninitialize(); 
	}

}

};  // namespace