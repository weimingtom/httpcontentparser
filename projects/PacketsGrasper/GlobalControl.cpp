#include "stdafx.h"
#include ".\globalcontrol.h"
#include <utility\HTTPPacket.h>

//===============================
// 静态成员
GlobalControl * GlobalControl::pInstance_ = NULL;
GlobalControl * GlobalControl::getInstance() {
	static GlobalControl inst;
	return &inst;
}

//=================================
// 构造及西沟函数
GlobalControl::GlobalControl(void) {
	update_ = false;
}

GlobalControl::~GlobalControl(void) {
}

// 初始化
void GlobalControl::Update() {
	if (update_ == true) {
		return ;
	}

	update_ = true;
}

bool GlobalControl::checkHTTPHeader(HTTP_RESPONSE_HEADER *header) {
	return true;
}

bool GlobalControl::checkHTTPContent(HTTPPacket *packet) {
	return true;
}

bool GlobalControl::checkIp(unsigned int ip, short port) {
	return true;
}