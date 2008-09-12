#ifndef _SELECTIO_BUFFERCALLCOM_H__
#define _SELECTIO_BUFFERCALLCOM_H__

#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>

// this object will buffer the operation.
// we call the COM object throught this class
// so that we can reduce much operation inter-process.
template <int BUFFER_COUNT = 10>
class BufferImageCOMObject {
public:
	BufferImageCOMObject() {
	}

	~BufferImageCOMObject() {
	}

	// 是否应该check Image content
	bool checkImage(const unsigned type) {
		if (save_porn_cnt_ < BUFFER_COUNT) {
			return type & checktype_;
		} else {
			return checkImagedirect(type);
		}
	}

	// 保存图片
	bool saveImage(const bool porned) {
		if (porned == true) {
			if (save_all_cnt < BUFFER_COUNT) {
				save_porn_ = saveImageDirect(porned);
				return save_porn_;
			} else {
				save_all_cnt++;
				return save_porn_;
			}
		} else {
			if (save_porn_cnt_ < BUFFER_COUNT) {
				save_porn_ = saveImageDirect(porned);
				return save_porn_;
			} else {
				save_porn_cnt_++;
				return save_porn_;
			}
		}
	}
private:
	bool save_porn_;
	int save_all_cnt;
	int save_porn_cnt_;
	bool save_all_;
	unsigned  checktype_;
private:
	// call COM
	bool checkImagedirect(const bool type) {
		VARIANT_BOOL result;
		CoInitialize(NULL);
		try {
		} catch(_com_error&) {
			CoUninitialize();
			return false;
		}
	}

	// 是否应该保存图片
	bool saveImageDirect(const int proned) {
		VARIANT_BOOL result;
		CoInitialize(NULL);
		try {
			// 如果不是porn Image, 我们只需要检查是否需要保存所有图片
			if (porned == false) {
				IWebHistoryRecorder *record = NULL;
				HRESULT hr = CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&record);
				record->get_RecordAllImage(&result);
				if (VARIANT_TRUE == result) {
					record->Release();
					CoUninitialize();
					return true;
				} else {
					return false;
				}
			} else {
				// 如果是黄色图片的话
				record->get_RecordPornImage(result);
				CoUninitialize();
				if (VARIANT_TRUE == result) {
					record->Release();
					return true;
				} else {
					return false;
				}
			}
		} catch (_com_error &e) {
			CoUninitialize();
			return false;
		}
	}
};

#endif  // _SELECTIO_BUFFERCALLCOM_H__
