#include "StdAfx.h"
#include ".\websiterecorder.h"
#include <webcontenttype.h>
#include <sysutility.h>
#include <com\FilterSetting.h>
#include <com\FilterSetting_i.c>
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>
#include <fstream>


WebsiteRecorder::WebsiteRecorder(void)
{
	porn_path[0] = '\0';
	normal_path[0] = '\0';

	save_porn_url_ = false;
	save_url_ = false;
	initialized_ = false;
}

WebsiteRecorder::~WebsiteRecorder(void)
{
}

// 此函数会在函数updateWebsites()中调用
// 之所以不再saveWebsites中调用， 是因为在DLL卸载时
// COM初始化可能会失败
void WebsiteRecorder::getServiceSetting() {
	// 此函数之调用一次
	if (initialized_)
		return;
	else {
		initialized_ = true;
	}

	try {
		AutoInitInScale _auto_com_init;

		// 是否应该保存
		VARIANT_BOOL recorded;
		IWebHistoryRecorder * webHistory = NULL;
		CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&webHistory);

		webHistory->get_RecordAllURLs(&recorded);
		save_url_ = convert(recorded);

		webHistory->get_RecordPornURLs(&recorded);
		save_porn_url_ = convert(recorded);

		// 获取路径
		if (porn_path[0] == '\0' || normal_path[0] == '\0') {
			BSTR retVal;
			IAppSetting * appSetting = NULL;
			HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
			appSetting->GetInstallPath((BSTR*)&retVal);
			
			GetPornWebSiteFile(porn_path, MAX_PATH, (TCHAR*)_bstr_t(retVal));
			GetWebSiteFile(normal_path, MAX_PATH, (TCHAR*)_bstr_t(retVal));
		}
	} catch(...) {
		porn_path[0] = '\0';
		normal_path[0] = '\0';
	}
}

// 
void WebsiteRecorder::updateWebsites(const std::string &main_dns, const int score) {
	getServiceSetting();

	if (score != CONTENT_CHECK_PORN) {
		ADDRESS_SCORE::iterator iter = address_score_.find(main_dns);
		if (iter == address_score_.end()) {
			address_score_.insert(std::make_pair(main_dns, 0));
		}
	} else {
		// 如果不是，放入到
		ADDRESS_SCORE::iterator iter = address_score_.find(main_dns);
		if (iter != address_score_.end()) {
			iter->second += 1;	// 加1
		} else {
			// 新增一个
			address_score_.insert(std::make_pair(main_dns, 1));
		}
	}
}

void WebsiteRecorder::saveWebsites() {
	// 获取设置
	// getServiceSetting();

	if (normal_path[0] != '\0' || porn_path[0] != '\0')
		return;

	std::fstream porn, normal;
	porn.open(porn_path, std::ios::out | std::ios::app );
	normal.open(normal_path, std::ios::out | std::ios::app);

	// 写入文件
	ADDRESS_SCORE::iterator iter = address_score_.begin();
	for (; iter != address_score_.end(); ++iter) {
		if (iter->second  > PORN_SCORE) {
			if (savePornURLs()) {
				porn.write(iter->first.c_str(), (std::streamsize)iter->first.length());
				porn.write("\r\n", (std::streamsize)strlen("\r\n"));
			}
		} else {
			if (saveURLs()) {
				normal.write(iter->first.c_str(), (std::streamsize)iter->first.length());
				normal.write("\r\n", (std::streamsize)strlen("\r\n"));
			}
		}
	}

	porn.close();
	normal.close();

	address_score_.clear();
}
