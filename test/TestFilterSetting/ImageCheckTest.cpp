#include "StdAfx.h"
#include ".\imagechecktest.h"
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <typeconvert.h>
#include <comdef.h>
#include <webcontenttype.h>

ImageCheckTest::ImageCheckTest(void)
{
}

ImageCheckTest::~ImageCheckTest(void)
{
}

// 注意此测试在父模式下可能失效
void ImageCheckTest::TestImageCheck() {
	AutoInitInScale _auto_com_init;

	{
	IWebContentCheck *pCheck;
	HRESULT hr = CoCreateInstance(CLSID_WebContentCheck, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentCheck, (LPVOID*)&pCheck);
	if (FAILED(hr)) {
		return;
	}

	const LONG tight_ness = 0;
	const long c_minScope = 1, c_maxScope = 10;
	pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_JPEG);
	pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_GIF);
	pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_PNG);
	pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_BMP);
	pCheck->enableCheck(VARIANT_TRUE, CONTYPE_HTML);
	pCheck->put_ImageCheckTightness(tight_ness);
	pCheck->setCheckScope(c_minScope, c_maxScope);

	VARIANT_BOOL should_checked;
	pCheck->shouldCheck(IMAGE_TYPE_JPEG, &should_checked);
	bool checkJPEG = convert(should_checked);
	CPPUNIT_ASSERT(true == checkJPEG);

	pCheck->shouldCheck(IMAGE_TYPE_GIF, &should_checked);
	bool checkGIF = convert(should_checked);
	CPPUNIT_ASSERT(true == checkGIF);

	pCheck->shouldCheck(IMAGE_TYPE_PNG, &should_checked);
	bool checkPNG = convert(should_checked);
	CPPUNIT_ASSERT(true == checkPNG);

	pCheck->shouldCheck(IMAGE_TYPE_BMP, &should_checked);
	bool checkBMP= convert(should_checked);
	CPPUNIT_ASSERT(true == checkBMP);

	pCheck->shouldCheck(CONTYPE_HTML, &should_checked);
	bool checkHTML= convert(should_checked);
	CPPUNIT_ASSERT(true == checkHTML);

	long imageCheckTightness;
	long minScope, maxScope;
	pCheck->get_ImageCheckTightness(&imageCheckTightness);
	pCheck->getCheckScope(&minScope, &maxScope);
	
	CPPUNIT_ASSERT(tight_ness == imageCheckTightness);
	CPPUNIT_ASSERT(c_minScope == minScope);
	CPPUNIT_ASSERT(c_maxScope == maxScope);
	pCheck->Release();
	}

		{
	IWebContentCheck *pCheck;
	HRESULT hr = CoCreateInstance(CLSID_WebContentCheck, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentCheck, (LPVOID*)&pCheck);
	if (FAILED(hr)) {
		return;
	}

	const LONG tight_ness = 4;
	const long c_minScope = 30, c_maxScope = 100;
	pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_JPEG);
	pCheck->enableCheck(VARIANT_FALSE, IMAGE_TYPE_GIF);
	pCheck->enableCheck(VARIANT_TRUE, IMAGE_TYPE_PNG);
	pCheck->enableCheck(VARIANT_FALSE, IMAGE_TYPE_BMP);
	pCheck->enableCheck(VARIANT_TRUE, CONTYPE_HTML);
	pCheck->put_ImageCheckTightness(tight_ness);
	pCheck->setCheckScope(c_minScope, c_maxScope);

	VARIANT_BOOL should_checked;
	pCheck->shouldCheck(IMAGE_TYPE_JPEG, &should_checked);
	bool checkJPEG = convert(should_checked);
	CPPUNIT_ASSERT(true == checkJPEG);

	pCheck->shouldCheck(IMAGE_TYPE_GIF, &should_checked);
	bool checkGIF = convert(should_checked);
	CPPUNIT_ASSERT(false == checkGIF);

	pCheck->shouldCheck(IMAGE_TYPE_PNG, &should_checked);
	bool checkPNG = convert(should_checked);
	CPPUNIT_ASSERT(true == checkPNG);

	pCheck->shouldCheck(IMAGE_TYPE_BMP, &should_checked);
	bool checkBMP= convert(should_checked);
	CPPUNIT_ASSERT(false == checkBMP);

	pCheck->shouldCheck(CONTYPE_HTML, &should_checked);
	bool checkHTML= convert(should_checked);
	CPPUNIT_ASSERT(true == checkHTML);

	long imageCheckTightness;
	long minScope, maxScope;
	pCheck->get_ImageCheckTightness(&imageCheckTightness);
	pCheck->getCheckScope(&minScope, &maxScope);
	
	CPPUNIT_ASSERT(tight_ness == imageCheckTightness);
	CPPUNIT_ASSERT(c_minScope == minScope);
	CPPUNIT_ASSERT(c_maxScope == maxScope);
	pCheck->Release();
	}
}