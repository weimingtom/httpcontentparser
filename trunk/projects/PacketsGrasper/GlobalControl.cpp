#include "stdafx.h"
#include ".\globalcontrol.h"
#include <utility\HTTPPacket.h>

//===============================
// ��̬��Ա
GlobalControl * GlobalControl::pInstance_ = NULL;
GlobalControl * GlobalControl::getInstance() {
	static GlobalControl inst;
	return &inst;
}

//=================================
// ���켰��������
GlobalControl::GlobalControl(void) {
	update_ = false;
}

GlobalControl::~GlobalControl(void) {
}

// ��ʼ��
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