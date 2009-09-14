#include "StdAfx.h"
#include ".\iaccessnetworktest.h"
#include ".\comtestutility.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <typeconvert.h>
#include <time.h>
#include <stdio.h>

#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


namespace {
void unsetBlocktime(const int day, const int hour);
void setBlocktime(const int day, const int hour) ;
bool accessNetword();
};


// �ڸ�������ģʽ������
void TestTwoModel() {
	GetInChildMode();
	time_t t;
	struct tm * local;

	// ��ȡʱ��
	time(&t);
	local= localtime(&t);


	unsetBlocktime(local->tm_wday, local->tm_hour);
	bool accessable = accessNetword();
	BOOST_ASSERT (true == accessable);

	time(&t);
	local= localtime(&t);
	setBlocktime(local->tm_wday, local->tm_hour);
	accessable = accessNetword();
	BOOST_ASSERT (false == accessable);

	GetInParentModel();
	accessable = accessNetword();
	BOOST_ASSERT (true == accessable);
	GetInChildMode();
	accessable = accessNetword();
	BOOST_ASSERT (false == accessable);
}
void TestSetAndGetBlockTime() {
	GetInChildMode();
	time_t t;
	struct tm * local;

	// ��ȡʱ��
	time(&t);
	local= localtime(&t);


	unsetBlocktime(local->tm_wday, local->tm_hour);
	bool accessable = accessNetword();
	BOOST_ASSERT (true == accessable);

	time(&t);
	local= localtime(&t);
	setBlocktime(local->tm_wday, local->tm_hour);
	accessable = accessNetword();
	BOOST_ASSERT (false == accessable);


	time(&t);
	local= localtime(&t);
	unsetBlocktime(local->tm_wday, local->tm_hour);
	accessable = accessNetword();
	BOOST_ASSERT (true == accessable);
}


namespace {
bool accessNetword() {
	bool accessable;
	try {
		CoInitialize(NULL);

		// ��ʼ��
		IAccessNetwork *accessNetword = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER, IID_IAccessNetwork, (LPVOID*)&accessNetword);
		if (FAILED(hr)) {
			BOOST_ASSERT(false);
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

		// ��ʼ��
		IAccessNetwork *accessNetword = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER, IID_IAccessNetwork, (LPVOID*)&accessNetword);
		if (FAILED(hr)) {
			BOOST_ASSERT(false);
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

		// ��ʼ��
		IAccessNetwork *accessNetword = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER, IID_IAccessNetwork, (LPVOID*)&accessNetword);
		if (FAILED(hr)) {
			BOOST_ASSERT(false);
			return;
		}

		accessNetword->removeBlockTime(day, hour);
		CoUninitialize(); 

	} catch (_com_error &) {
		CoUninitialize(); 
	}

}

};  // namespace