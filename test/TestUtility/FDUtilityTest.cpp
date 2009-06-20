#include "StdAfx.h"
#include ".\fdutilitytest.h"
#include <utility\fd_set_utility.h>

FDUtilityTest::FDUtilityTest(void) {
}

FDUtilityTest::~FDUtilityTest(void) {
}

// �˺���������ԣ��������д���NULL�����
void FDUtilityTest::testNone() {
	{
		fd_set *s1 = NULL, s2;
		SOCKET s = 0;
		FD_ZERO(&s2);
		CPPUNIT_ASSERT(NULL == (FDSET_Add(s1, &s2)));
		CPPUNIT_ASSERT(NULL == (FDSET_Add(&s2, s1)));
		CPPUNIT_ASSERT(NULL == (FDSET_Add(s1, s)));
		CPPUNIT_ASSERT(NULL == (FDSET_Set(s1, &s2)));
		CPPUNIT_ASSERT(NULL == (FDSET_Set(&s2, s1)));
		CPPUNIT_ASSERT(NULL == (FDSET_Del(s1, &s2)));
		CPPUNIT_ASSERT(NULL == (FDSET_Del(&s2, s1)));
		CPPUNIT_ASSERT(NULL == (FDSET_Del(s1, s)));
	}
}
void FDUtilityTest::testFDAdd() {
	

	{ // ���Ե��������
		const int num_of_socket = 5;
		SOCKET socks1[num_of_socket] = {28, 3829, 832,392, 801}; 
		SOCKET socks2[num_of_socket] = {28, 3829, 832, 913, 13};
		fd_set s1, s2;
		FD_ZERO(&s1);FD_ZERO(&s2);

		for (int i = 0; i < num_of_socket; ++i) {
			FD_SET(socks1[i], &s1);
		}
		CPPUNIT_ASSERT(s1.fd_count == num_of_socket);
		for (int i = 0; i < num_of_socket; ++i) {
			FD_SET(socks2[i], &s2);
		}
		FDSET_Add(&s1, &s2);
		
		CPPUNIT_ASSERT(s1.fd_count == num_of_socket + 2);
		CPPUNIT_ASSERT(s2.fd_count == num_of_socket);

		for(int i = 0; i < (int)s2.fd_count; ++i) {
			CPPUNIT_ASSERT(FD_ISSET(s2.fd_array[i], &s1));
		}
	}

	// �����ظ����
	{
		const int num_of_socket = 5;
		SOCKET socks1[num_of_socket] = {28, 3829, 832,392, 801};
		fd_set s1;
		FD_ZERO(&s1);
		for (int i = 0; i < num_of_socket; ++i) {
			FDSET_Add(&s1, socks1[i]);
		}

		CPPUNIT_ASSERT(s1.fd_count == num_of_socket);
		for (int i = 0; i < num_of_socket; ++i) {
			FDSET_Add(&s1, socks1[i]);
		}

		CPPUNIT_ASSERT(s1.fd_count == num_of_socket);
	}
}
void FDUtilityTest::testFDSet() {
	{
	SOCKET socks1[5] = {28, 3829, 832,392, 801}; 
	SOCKET socks2[5] = {28, 3829, 832, 913, 13};
	fd_set s1, s2;
	FD_ZERO(&s1);FD_ZERO(&s2);
	for (int i = 0; i < 5; ++i) {
		FD_SET(socks1[i], &s1);
	}
	for (int i = 0; i < 5; ++i) {
		FD_SET(socks2[i], &s2);
	}
	FDSET_Set(&s1, &s2);
	CPPUNIT_ASSERT(s2.fd_count == 5);
	for(int i = 0; i < (int)s2.fd_count; ++i) {
		CPPUNIT_ASSERT(FD_ISSET(s2.fd_array[i], &s1));
	}
	}
}
void FDUtilityTest::testFDDel() {
	// ����
	fd_set s1, s2;
	const int num_of_socket = 5;
	SOCKET socks1[num_of_socket] = {28, 3829, 832,392, 801}; 

	// ���뵽s1
	FD_ZERO(&s1);FD_ZERO(&s2);
	for (int i = 0; i < num_of_socket; ++i) {
		FDSET_Add(&s1, socks1[i]);
	}

	// �ڿ�״̬��ɾ��
	FDSET_Del(&s1, &s2);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket);


	// ɾ��һ�������ڵ�
	FDSET_Del(&s1, 1111);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket);
	// ɾ��һ�����ڵ�socket
	FDSET_Del(&s1, socks1[3]);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket-1);
	// ɾ��һ�������ڵ�
	FDSET_Del(&s1, 1111);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket-1);

	// ��ֵs1
	for (int i = 0; i < num_of_socket; ++i) {
		FDSET_Add(&s1, socks1[i]);
	}

	CPPUNIT_ASSERT(s1.fd_count == num_of_socket);
	//ɾ���հ�s2
	FD_ZERO(&s2);
	FDSET_Del(&s1, &s2);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket);
	// ����������ڵ�
	FD_SET(socks1[1], &s2);
	FDSET_Del(&s1, &s2);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket-1);

	FD_SET(socks1[2], &s2);
	FDSET_Del(&s1, &s2);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket-2);

	// �ظ�S1�� ���˴�
	for (int i = 0; i < num_of_socket; ++i) {
		FDSET_Add(&s1, socks1[i]);
	}
	FDSET_Del(&s1, &s2);
	CPPUNIT_ASSERT(s1.fd_count == num_of_socket-2);
	
}