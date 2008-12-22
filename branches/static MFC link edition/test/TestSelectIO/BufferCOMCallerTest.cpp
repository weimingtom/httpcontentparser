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
		BufferCaller<WebContentCheckCaller, BUFFER_CALL_CNT> check_caller_;
		WebContentCheckCaller checker_;
	} catch (...) {
	}
}