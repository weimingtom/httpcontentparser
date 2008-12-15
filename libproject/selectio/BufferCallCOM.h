#ifndef _SELECTIO_BUFFERCALLCOM_H__
#define _SELECTIO_BUFFERCALLCOM_H__

#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <typeconvert.h>

// TEXT
class ContentSetting {
public:
	bool shouldSave(bool porned) const {
		if (porned) {
			return should_save_porn_;
		} else {
			return should_save_all_;
		}
	}
	bool shouldCheck() const { return should_check_;}

	void operator() () {
		VARIANT_BOOL result;
		IWebHistoryRecorder *record = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&record);

		// �Ƿ�Ӧ�ñ�������ͼƬ
		record->get_RecordAllWebsite(&result);
		should_save_all_ = convert(result);

		// �Ƿ�Ӧ�ñ����ɫͼƬ
		record->get_RecordPornWebsite(&result);
		should_save_porn_ = convert(result);
		
		record->Release();
	}
private:
	bool should_save_all_;
	bool should_save_porn_;
	bool should_check_;
};

// Image Save
class ImageSetting {
public:
	// �Ƿ�Ӧ�ñ���
	bool shouldSave(bool porned) const {
		if (porned) {
			return should_save_pron_;
		} else {
			return should_save_all_;
		}
	}
	bool shouldCheck() const { return should_check_;}
	
	void operator()() {
		VARIANT_BOOL result;
		IWebHistoryRecorder *record = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&record);

		// �Ƿ�Ӧ�ñ�������ͼƬ
		record->get_RecordAllImage(&result);
		should_save_all_ = convert(result);

		// �Ƿ�Ӧ�ñ����ɫͼƬ
		record->get_RecordPornImage(&result);
		should_save_pron_ = convert(result);
		
		record->Release();
	}
private:
	bool should_save_all_;
	bool should_save_pron_;
	bool should_check_;
};

#endif  // _SELECTIO_BUFFERCALLCOM_H__
