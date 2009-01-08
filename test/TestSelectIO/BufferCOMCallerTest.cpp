#include "StdAfx.h"
#include ".\buffercomcallertest.h"
#include <BufferCallCOM.h>
#include <typeconvert.h>
#include <comdef.h>
#include <webcontenttype.h>

BufferCOMCallerTest::BufferCOMCallerTest(void)
{
}

BufferCOMCallerTest::~BufferCOMCallerTest(void)
{
}


const char * packet1_data = "HTTP/1.1 200 OK\r\n"
"Content-Type: image/gif\r\n"
"Content-Length: 3072\r\n\r\n";
const int data1_size = 3072;
char data1[data1_size] = {0};

const char * packet2_data = "HTTP/1.1 200 OK\r\n"
"Content-Type: image/gif\r\n"
"Content-Length: 10241\r\n\r\n";
const int data2_size = 10241;
char data2[data2_size] = {0};

const char * packet3_data = "HTTP/1.1 200 OK\r\n"
"Content-Type: image/jpeg\r\n"
"Content-Length: 3072\r\n\r\n";
const int data3_size = 3072;
char data3[data3_size] = {0};

const char * packet4_data = "HTTP/1.1 200 OK\r\n"
"Content-Type: image/jpeg\r\n"
"Content-Length: 10241\r\n\r\n";
const int data4_size = 10241;
char data4[data4_size] = {0};


void BufferCOMCallerTest::WebContentRecordCallerTest() {
	// set.
	try {
		AutoInitInScale _auto_com_init;
		IWebHistoryRecorder *pRecorder;
		HRESULT hr = CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_LOCAL_SERVER, IID_IWebHistoryRecorder, (LPVOID*)&pRecorder);
		if (FAILED(hr)) {
			return;
		}

		const int buffer_cnt = 20;
		pRecorder->put_RecordAllImage(convert(true));
		pRecorder->put_RecordPornImage(convert(true));
		pRecorder->put_RecordPornPages(convert(true));
		pRecorder->put_RecordAllPages(convert(true));


		// buffer caller
		BufferCaller<WebContentRecordCaller, buffer_cnt> record_caller_;
		WebContentRecordCaller recorder_;

		for (int i = 0; i < buffer_cnt; ++i) {
			record_caller_.Call(recorder_);

			CPPUNIT_ASSERT(true == recorder_.shouldRecord(CONTENT_CHECK_PORN, IMAGE_TYPE_JPEG));
			CPPUNIT_ASSERT(true == recorder_.shouldRecord(CONTENT_CHECK_NORMAL, IMAGE_TYPE_JPEG));
			CPPUNIT_ASSERT(true == recorder_.shouldRecord(CONTENT_CHECK_PORN, CONTYPE_HTML));
			CPPUNIT_ASSERT(true == recorder_.shouldRecord(CONTENT_CHECK_NORMAL, CONTYPE_HTML));

			if (i == 15) {
				pRecorder->put_RecordAllImage(convert(false));
				pRecorder->put_RecordPornImage(convert(false));
				pRecorder->put_RecordPornPages(convert(false));
				pRecorder->put_RecordAllPages(convert(false));
			}
		}

		// it happens.
		record_caller_.Call(recorder_);
		CPPUNIT_ASSERT(false == recorder_.shouldRecord(CONTENT_CHECK_PORN, IMAGE_TYPE_JPEG));
		CPPUNIT_ASSERT(false == recorder_.shouldRecord(CONTENT_CHECK_NORMAL, IMAGE_TYPE_JPEG));
		CPPUNIT_ASSERT(false == recorder_.shouldRecord(CONTENT_CHECK_PORN, CONTYPE_HTML));
		CPPUNIT_ASSERT(false == recorder_.shouldRecord(CONTENT_CHECK_NORMAL, CONTYPE_HTML));
	} catch (_com_error &) {
	}

}
void BufferCOMCallerTest::WebContentCheckCallerTest() {
	try {
		AutoInitInScale _auto_com_init;

		//======================================
		// 设置COM
		IWebContentCheck *pCheck;
		HRESULT hr = CoCreateInstance(CLSID_WebContentCheck, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentCheck, (LPVOID*)&pCheck);
		if (FAILED(hr)) {
			return;
		}

		const LONG tight_ness = 0;
		const long c_minScope = 1, c_maxScope = 11;
		pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_JPEG);
		pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_GIF);
		pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_PNG);
		pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_BMP);
		pCheck->enableCheck(VARIANT_TRUE, CONTYPE_HTML);
		pCheck->put_ImageCheckTightness(tight_ness);
		pCheck->setCheckScope(c_minScope, c_maxScope);

		// 初始化几个包
		int bytes;
		HTTPPacket packet1, packet2, packet3, packet4;
		packet1.addBuffer(packet1_data, strlen(packet1_data), &bytes);
		packet1.addBuffer(data1, data1_size, &bytes);
		packet2.addBuffer(packet2_data, strlen(packet2_data), &bytes);
		packet2.addBuffer(data2, data2_size, &bytes);
		packet3.addBuffer(packet3_data, strlen(packet3_data), &bytes);
		packet3.addBuffer(data3, data3_size, &bytes);
		packet4.addBuffer(packet4_data, strlen(packet4_data), &bytes);
		packet4.addBuffer(data4, data4_size, &bytes);


		BufferCaller<WebContentCheckCaller, BUFFER_CALL_CNT> check_caller_;
		WebContentCheckCaller checker_;

		for (int i = 0; i < BUFFER_CALL_CNT; ++i) {
			check_caller_.Call(checker_);
			CPPUNIT_ASSERT(true == checker_.shouldCheck(&packet1));
			CPPUNIT_ASSERT(true == checker_.shouldCheck(&packet2));
			CPPUNIT_ASSERT(true == checker_.shouldCheck(&packet3));
			CPPUNIT_ASSERT(true == checker_.shouldCheck(&packet4));

			// 修改设置
			if (i == 1) {
				pCheck->setCheckScope(1, 10);
				pCheck->enableCheck(VARIANT_FALSE, IMAGE_TYPE_JPEG);
			}
		}

		check_caller_.Call(checker_);
		CPPUNIT_ASSERT(true == checker_.shouldCheck(&packet1));	
		CPPUNIT_ASSERT(false == checker_.shouldCheck(&packet2));	// 应该大于10240
		CPPUNIT_ASSERT(false == checker_.shouldCheck(&packet3));	// 因为是jpeg
		CPPUNIT_ASSERT(false == checker_.shouldCheck(&packet4));
	} catch (_com_error&) {
	}
}