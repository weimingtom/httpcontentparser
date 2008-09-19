#include "StdAfx.h"
#include ".\eyecaretest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>

EyecareTest::EyecareTest(void) {
}

EyecareTest::~EyecareTest(void) {
}

void EyecareTest::getTimeLeft() {
	IEyecare *pEyeCare = NULL;

	CoInitialize(NULL);
	CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
	pEyeCare->setEnterTime(10);
	pEyeCare->setEyecareTime(10);

	LONG timeLeft ;
	pEyeCare->getTimeLeft(&timeLeft);

	pEyeCare->Release();
	CoUninitialize();
}