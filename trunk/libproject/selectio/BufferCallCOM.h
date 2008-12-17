#ifndef _SELECTIO_BUFFERCALLCOM_H__
#define _SELECTIO_BUFFERCALLCOM_H__

#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <typeconvert.h>
#include <comdef.h>
#include <webcontenttype.h>

// 缓冲COM调用
// 是否需要保存
class WebContentRecordCaller {
public:
	WebContentRecordCaller() {
		defaultSetting();
	}

	void operator() () {
		try {
			AutoInitInScale _auto_com_init;
			IWebHistoryRecorder *pRecorder;
			HRESULT hr = CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_LOCAL_SERVER, IID_IWebHistoryRecorder, (LPVOID*)&pRecorder);
			if (FAILED(hr)) {
				return;
			}

			VARIANT_BOOL should_recorded;
			pRecorder->get_RecordAllImage(&should_recorded);
			all_image = convert(should_recorded);

			pRecorder->get_RecordPornImage(&should_recorded);
			porn_image = convert(should_recorded);

			pRecorder->get_RecordPornPages(&should_recorded);
			porn_webpage = convert(should_recorded);

			pRecorder->get_RecordAllPages(&should_recorded);
			all_webpage = convert(should_recorded);
		} catch (_com_error &) {
		} catch (...) {
		}
	}

public:
	bool shouldRecord(const int result, const int type) {
		if (isImage(type)) {
			if (result == CONTENT_CHECK_PORN) {
				return porn_image;
			} else {
				return all_image;
			}
		} else if (isText(type)) {
			if (result == CONTENT_CHECK_PORN) {
				return porn_webpage;
			} else {
				return all_webpage;
			}
		} else {
			return false;
		}
	}
private:
	void defaultSetting() {
		porn_image = true;
		all_image = true;
		porn_webpage = true;
		all_webpage = true;
	}

	bool porn_image;
	bool all_image;
	bool porn_webpage;
	bool all_webpage;

};

// 是否需要检查
class WebContentCheckCaller {
public:
	WebContentCheckCaller() {
		defaultSetting();
	}

	void operator()() {
		try {
			AutoInitInScale _auto_com_init;
			IWebContentCheck *pCheck;
			HRESULT hr = CoCreateInstance(CLSID_WebContentCheck, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentCheck, (LPVOID*)&pCheck);
			if (FAILED(hr)) {
				return;
			}
			
			VARIANT_BOOL should_checked;
			pCheck->shouldCheck(IMAGE_TYPE_JPEG, &should_checked);
			checkJPEG = convert(should_checked);

			pCheck->shouldCheck(IMAGE_TYPE_GIF, &should_checked);
			checkGIF = convert(should_checked);

			pCheck->shouldCheck(IMAGE_TYPE_PNG, &should_checked);
			checkPNG = convert(should_checked);

			pCheck->shouldCheck(IMAGE_TYPE_BMP, &should_checked);
			checkBMP= convert(should_checked);

			pCheck->shouldCheck(CONTYPE_HTML, &should_checked);
			checkHTML= convert(should_checked);
		} catch (_com_error &) {
		} catch (...) {
		}
	}

public:
	bool shouldCheck(const int contenttype) {
		switch (contenttype) {
			case CONTYPE_HTML:
				return checkHTML;
			case IMAGE_TYPE_BMP:
				return checkBMP;
			case IMAGE_TYPE_GIF:
				return checkGIF;
			case IMAGE_TYPE_PNG:
				return checkPNG;
			case IMAGE_TYPE_JPEG:
				return checkJPEG;
			default:
				return false;
		}
	}
private:
	// 默认设置
	void defaultSetting() {
		checkPNG = true;
		checkJPEG = true;
		checkBMP = true;
		checkGIF = true;
		checkHTML = true;
	}

	// setting members
	bool checkPNG;
	bool checkJPEG;
	bool checkBMP;
	bool checkGIF;
	bool checkHTML;
};

#endif  // _SELECTIO_BUFFERCALLCOM_H__
