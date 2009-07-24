
#ifndef  _DRIVER_CONST_H__
#define _DRIVER_CONST_H__

// 注意这个INDEX只是一个顺序， 传入的数据是CHAR类型
// 而实际保存数据的是DWORD类型，因为我们必须要在乘4
const int INDEX_INPUT_DATA_NTCREATESECTION = 0;
const int INDEX_INPUT_DATA_EXCHANGE_BUFFER = 1;
const int INDEX_INPUT_DATA_SYSDIR          = 2;

// 注意当NOTIFY_APP的值为1的时候，程序作出相应，在完成之后将APP_COMP制为0
const int ADDR_EXCHANGE_APP_COMP = 0; 	// 路径已经防止
const int ADDR_EXCHANGE_NOTIFY_APP = 0;  // 应用程序已经完成验证
const int ADDR_EXCHANGE_APP_RESULT = 4;
const int ADDR_EXCHANGE_FILEPATH = 8;	// 路径

#define PATH_BUF_MAX  260
#define EXCHANGE_BUFFER_SIZE  512


#define IO_CONTROL_BUFFER_INIT		1000

const wchar_t devicename[]=L"\\Device\\FPTECTORDRV";
const wchar_t devicelink[]=L"\\DosDevices\\FPTECTORDRV";

#ifdef TEXT
#define  APPCONTROL_SERVICE				TEXT("FPTECTORDRV")
#define  APPCONTROL_FILE						TEXT("\\\\.\\FPTECTORDRV")
#define  APPCONTROL_DRIVER_FILE		TEXT("FPTECTORDRV.sys")
#else
#define  APPCONTROL_SERVICE				("FPTECTORDRV")
#define  APPCONTROL_FILE						("\\\\.\\FPTECTORDRV")
#define  APPCONTROL_DRIVER_FILE		("FPTECTORDRV.sys")
#endif

#endif // _DRIVER_CONST_H__