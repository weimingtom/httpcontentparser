#include "StdAfx.h"
#include ".\registerinfo.h"
#include ".\globalvariable.h"
#include <utility\timeutility.h>
#include <time.h>

RegisterInfo::RegisterInfo(void)
{
}

RegisterInfo::~RegisterInfo(void)
{
}

void RegisterInfo::initialize() {
	getInstallTime();
}


bool RegisterInfo::registerSoft(const std::string & register_info) {
	return false;
}

bool RegisterInfo::trialEdition() {
	return false;
}

// ��ȡ��װʱ��
void RegisterInfo::getInstallTime() {
}

bool RegisterInfo::trial_ended() {
	return false;
}