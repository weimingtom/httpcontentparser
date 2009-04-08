#include "stdafx.h"
#include "baseEncrypt.h"
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <time.h>

char getChar(int i) {
	if (i >= 0 && i < 10) {
		return i + '0';
	} else if ( i >=10 && i <=15) {
		return i - 10 + 'A';
	} else if (i > 16) {
		i  = i %16;
		return getChar(i);
	} else if (i < 0) {
		return getChar(-i);
	} else {
		assert(false);
		return 0;
	}
}

int getNum(char i) {
	if (i >='0' && i <='9') {
		return i - '0';
	} else if (i >='A' && i <='F') {
		return i - 'A' + 10;
	} else {
		assert(false);
		return 0;
	}
}

// 生成注册码
// 随机生成1， 8， 7， 
std::string generateSN() {
	const int SN_BIT_COUNT= 20;
	TCHAR sn[SN_BIT_COUNT+1] = {0};
	
	srand(time(NULL));
	int r1 = rand() % 10;	 // 控制10
	int r3 = rand() %16; // 控制 6, 13
	int r7 = rand() % 16;  // 控制 11, 18
	int r9 = rand() % 10;		// 控制5
	int r12 = rand() % 16; // 控制 4, 15
	int r16 = rand() % 10; // 控制 8
	int r19 = rand() % 10; // 控制2
	int r20 = rand() % 16; // 控制14, 17, 

	sn[0] = getChar(r1);//
	sn[1] = getChar(r1 + r12+r20 + 16);
	sn[2] = getChar(r3);//
	sn[3] = getChar(2*r12 - r16 + 32);
	sn[4] = getChar(2*r9 + r7 - r16 + 32);
	sn[5] = getChar(2*r3 - r9 + r19 + 10);
	sn[6] = getChar(r7);//
	sn[7] = getChar(r20 + r1 + r3 + r12 - r16 + 16);
	sn[8] = getChar(r9);//
	sn[9] = getChar(r9 * 3 + r1);
	sn[10] = getChar(r9 * 3 + r12);
	sn[11] = getChar(r12);//
	sn[12] = getChar(r12 - r1 - r12 - r19);
	sn[13] = getChar(r1 + r16 + r20);
	sn[14] = getChar(r1 * 3 - r20);
	sn[15] = getChar(r16);//
	sn[16] = getChar(r9 + r7 + r9 + r20);
	sn[17] = getChar(r12 - r7 + r9 - r20);
	sn[18] = getChar(r19);//
	sn[19] = getChar(r20);//


	return std::string(sn);
}

// 简单加密算啦
bool validateSN(const std::string &serialnumber) {
	int r1 = getNum(serialnumber.c_str()[0]);
	int r3 = getNum(serialnumber.c_str()[0]);
	int r7 = getNum(serialnumber.c_str()[0]);
	int r9 = getNum(serialnumber.c_str()[0]);
	int r12 = getNum(serialnumber.c_str()[0]);
	int r16 = getNum(serialnumber.c_str()[0]);
	int r19 = getNum(serialnumber.c_str()[0]);
	int r20 = getNum(serialnumber.c_str()[0]);

	int x = getNum(serialnumber.c_str()[1]);
	if (x != (getNum(serialnumber.c_str()[0]) + getNum(serialnumber.c_str()[11]) + getNum(serialnumber.c_str()[19]) +16) % 16) {
		return false;
	}

	int x4 = getNum(serialnumber.c_str()[3]);
	if (x4 != (2 * getNum(serialnumber.c_str()[11]) - getNum(serialnumber.c_str()[15]) +32) % 16) {
		return false;
	}

	int x5 = getNum(serialnumber.c_str()[4]);
	if (x5 != (2 * getNum(serialnumber.c_str()[8]) - getNum(serialnumber.c_str()[15]) +32) % 16) {
		return false;
	}

	return true;
}