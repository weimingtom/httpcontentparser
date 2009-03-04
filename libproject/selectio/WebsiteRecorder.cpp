#include "StdAfx.h"
#include ".\websiterecorder.h"
#include <webcontenttype.h>
#include <apputility.h>
#include <com\FilterSetting.h>
#include <com\FilterSetting_i.c>
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>
#include <fstream>


WebsiteRecorder::WebsiteRecorder(void)
{
	memset(porn_path, 0, sizeof(porn_path));
	memset(normal_path, 0, sizeof(normal_path));

	save_porn_url_ = false;
	save_url_ = false;
}

WebsiteRecorder::~WebsiteRecorder(void)
{
}

void WebsiteRecorder::initialize() {
	getServiceSetting();
}
// �˺������ں���updateWebsites()�е���
// ֮���Բ���saveWebsites�е��ã� ����Ϊ��DLLж��ʱ
// COM��ʼ�����ܻ�ʧ��
void WebsiteRecorder::getServiceSetting() {
	// �˺���֮����һ��
	try {
		AutoInitInScale _auto_com_init;

		// ��ȡ·��
		if (_tcslen(normal_path) == 0 || _tcslen(porn_path) == 0) {
			OutputDebugString("get porn");

			BSTR retVal;
			IAppSetting * appSetting = NULL;
			HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
			appSetting->GetInstallPath((BSTR*)&retVal);
			
			GetPornWebSiteFile(porn_path, MAX_PATH, (TCHAR*)_bstr_t(retVal));
			GetWebSiteFile(normal_path, MAX_PATH, (TCHAR*)_bstr_t(retVal));
		}

		// �Ƿ�Ӧ�ñ���
		VARIANT_BOOL recorded;
		IWebHistoryRecorder * webHistory = NULL;
		CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&webHistory);

		webHistory->get_RecordAllURLs(&recorded);
		save_url_ = convert(recorded);

		webHistory->get_RecordPornURLs(&recorded);
		save_porn_url_ = convert(recorded);
	} catch(...) {
		porn_path[0] = '\0';
		normal_path[0] = '\0';
	}
}

// 
void WebsiteRecorder::updateWebsites(const std::string &main_dns, const int score) {
	if (score != CONTENT_CHECK_PORN) {
		ADDRESS_SCORE::iterator iter = address_score_.find(main_dns);
		if (iter == address_score_.end()) {
			address_score_.insert(std::make_pair(main_dns, 0));
		}
	} else {
		// ������ǣ����뵽
		ADDRESS_SCORE::iterator iter = address_score_.find(main_dns);
		if (iter != address_score_.end()) {
			iter->second += 1;	// ��1
		} else {
			// ����һ��
			address_score_.insert(std::make_pair(main_dns, 1));
		}
	}
}

void WebsiteRecorder::saveWebsites() {
	// ��ȡ����
	// getServiceSetting();
	if (_tcslen(normal_path) == 0 || _tcslen(porn_path) == 0)
		return;

	std::fstream porn, normal;
	porn.open(porn_path, std::ios::out | std::ios::app );
	normal.open(normal_path, std::ios::out | std::ios::app);

	// д���ļ�
	ADDRESS_SCORE::iterator iter = address_score_.begin();
	for (; iter != address_score_.end(); ++iter) {
		if (iter->second  > PORN_SCORE) {
			if (savePornURLs()) {
				saveDNSItem(iter->first, porn);
			}
		} else {
			if (saveURLs()) {
				saveDNSItem(iter->first, normal);
			}
		}
	}

	porn.close();
	normal.close();

	address_score_.clear();
}

void WebsiteRecorder::saveDNSItem(const std::string &main_dns, std::fstream &s) {
	FULL_DNS_MAP::iterator iter = fullDNS.lower_bound(main_dns);
	FULL_DNS_MAP::iterator iterEnd = fullDNS.upper_bound(main_dns);

	TCHAR info[MAX_PATH];
	sprintf(info, "main dns : %s", main_dns.c_str());
	OutputDebugString(info);

	for (; iter != iterEnd; ++iter) {
		OutputDebugString(iter->second.c_str());
		s.write(iter->second.c_str(), static_cast<std::streamsize>(iter->second.length()));
		s.write("\r\n", static_cast<std::streamsize>(strlen("\r\n")));
	}
}
void WebsiteRecorder::addDNS(const std::string &main_dns, const std::string &full) {
	fullDNS.insert(make_pair(main_dns, full));

	// ��������������
	ADDRESS_SCORE::iterator iter = address_score_.find(main_dns);
	if (iter == address_score_.end()) {
		address_score_.insert(std::make_pair(main_dns, 0));
	}
}
