
#ifndef  _DRIVER_CONST_H__
#define _DRIVER_CONST_H__

// ע�����INDEXֻ��һ��˳�� �����������CHAR����
// ��ʵ�ʱ������ݵ���DWORD���ͣ���Ϊ���Ǳ���Ҫ�ڳ�4
const int INDEX_INPUT_DATA_NTCREATESECTION = 0;
const int INDEX_INPUT_DATA_EXCHANGE_BUFFER = 1;
const int INDEX_INPUT_DATA_SYSDIR          = 2;

// ע�⵱NOTIFY_APP��ֵΪ1��ʱ�򣬳���������Ӧ�������֮��APP_COMP��Ϊ0
const int ADDR_EXCHANGE_APP_COMP = 0; 	// ·���Ѿ���ֹ
const int ADDR_EXCHANGE_NOTIFY_APP = 0;  // Ӧ�ó����Ѿ������֤
const int ADDR_EXCHANGE_APP_RESULT = 4;
const int ADDR_EXCHANGE_FILEPATH = 8;	// ·��

#define PATH_BUF_MAX  260
#define EXCHANGE_BUFFER_SIZE  512


#define IO_CONTROL_BUFFER_INIT		1000

#endif // _DRIVER_CONST_H__