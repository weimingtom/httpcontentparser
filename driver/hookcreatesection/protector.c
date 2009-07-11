
#include "ntddk.h"

struct SYS_SERVICE_TABLE { 
	void **ServiceTable; 
	unsigned long CounterTable; 
	unsigned long ServiceLimit; 
	void **ArgumentsTable; 
}; 

// ϵͳ·����ϵͳ·������
// �����޷��������API, 
// ��װ�����ڼ�����������ʱ������ز���
const int PATH_BUF_MAX = 260;
char SystemDir[260];
int  LenSystemDir = 0;

const WCHAR devicename[]=L"\\Device\\Protector";
const WCHAR devicelink[]=L"\\DosDevices\\PROTECTOR";

// ע�����INDEXֻ��һ��˳�� �����������CHAR����
// ��ʵ�ʱ������ݵ���DWORD���ͣ���Ϊ���Ǳ���Ҫ�ڳ�4
const int INDEX_INPUT_DATA_NTCREATESECTION = 0;
const int INDEX_INPUT_DATA_EXCHANGE_BUFFER = 1;
const int INDEX_INPUT_DATA_SYSDIR          = 2;
const int INDEX_INPUT_DATA_SENDTHREADMSG   = 3;
const int INDEX_INPUT_DATA_HWND			   = 4;
#define  WM_MSG_CHECKAPP				(0x0400 + 0x100)

typedef ULONG (__stdcall *SENDMESSAGE)(ULONG hWnd, ULONG Msg, ULONG wParam, ULONG lParam);
SENDMESSAGE Proc_SendMessage = 0;
ULONG g_hWnd = 0;

// ��֤�ܹ��������Check
KEVENT g_mutex_event; 
ULONG Index;
ULONG RealCallee;

// ���ϲ���򽻻��ĳ���
char * exchange_buffer;
extern struct SYS_SERVICE_TABLE *KeServiceDescriptorTable; 

int checkfilepath(ANSI_STRING *str) {
	const char * DOTEXT = ".exe";
	const int DOTEXE_LENGTH = 4;
	
	// ���������ʵ���ó��֣���������
	if (NULL == str) {
		goto passed;
	} 

	// �Ƚ�����ַ��ַ��ǲ���.exe
	if(_strnicmp(&(str->Buffer[str->Length - DOTEXE_LENGTH]), DOTEXT, DOTEXE_LENGTH)) { 
		DbgPrint("[Protector] [NOT EXE]%s passed", str->Buffer);
		goto passed;
	}
	
	// �����{systemdir}��ͷ�򷵻�Ϊ��
	if(0 == _strnicmp(str->Buffer, SystemDir, LenSystemDir)) { 
		DbgPrint("[Protector] [IN SYSTEM DIR] %s passed", str->Buffer);
		goto passed;
	}

	DbgPrint("[Protector] Need to check %s Failed", str->Buffer);
	return 0;
passed:
	RtlFreeAnsiString(str);
	return 1;
}


//this function decides whether we should allow NtCreateSection() call to be successfull
ULONG __stdcall check(PULONG arg)
{
	HANDLE hand=0;
	PFILE_OBJECT file=0;
	POBJECT_HANDLE_INFORMATION info;
	ULONG notify = 0;
	ULONG result = 0;
	ULONG notcheck = 0;
	const int max_check_num = 5;
	int cnt = 0;
	char*buff;
	ANSI_STRING str; 
	
	//check the flags. If PAGE_EXECUTE access to the section is not requested,
	//it does not make sense to be bothered about it	
	if((arg[4]&0xf0)==0)
		return 1;
	if((arg[5]&0x01000000)==0)
		return 1;


	//get the file name via the file handle
	hand=(HANDLE)arg[6];		// ���������������п�ִ���ļ��ľ��
	ObReferenceObjectByHandle(hand,0,0,KernelMode,&file,(POBJECT_HANDLE_INFORMATION)&info);
	if(!file)
		return 1;

	RtlUnicodeStringToAnsiString(&str,&file->FileName,1);


	//  ���Ӧ�ó���
	buff=str.Buffer;
	if (checkfilepath(&str)) {
		return 1;
	}

	// �ͷž��
	ObDereferenceObject(file);
	

	//now we are going to ask user's opinion. Write file name to the buffer, and wait until
	//the user indicates the response (1 as a first DWORD means we can proceed)

	//synchronize access to the buffer
	KeWaitForSingleObject(&g_mutex_event,Executive,KernelMode,0,0);


	// ���ļ�·����·�����ȷ��뵽������֮��
	// ͨ�����ַ�ʽ�ϴ���Ӧ�ó���
	strcpy(&exchange_buffer[8],buff);
	RtlFreeAnsiString(&str);
	notify = 1;
	memmove(&exchange_buffer[0],&notify,4);

	// �ȴ�Ӧ�ó���������Ӧ
	while(1)
	{
		// �ȴ�200ms, ��Ȼ���ܻ���;ֹͣ
		LARGE_INTEGER li;
		li.QuadPart=-200;
		KeDelayExecutionThread(KernelMode, FALSE, &li);
		
		// checked�����˿ͻ�Ӧ�ó����Ƿ���������Ӧ
		memmove(&notcheck,&exchange_buffer[0],4);
		
		// Ϊ�˱��⵱���û�������������ٳٵò���������µ�����
		// �������������ȴ�5��
		if (cnt > max_check_num) {
			result = 1;
			break;
		}
		if(!notcheck) {
			memmove(&result,&exchange_buffer[4],4);
			break;
		}
		
		cnt++;
	}


	// ʹ���������������
	KeSetEvent(&g_mutex_event,0,0);
	return result;
}


//just saves execution contect and calls check() 
_declspec(naked) Proxy()
{
	DbgPrint("[Protector] Proxy");
	_asm{
		//save execution contect and calls check() -the rest depends upon the value check() returns
		// if it is 1, proceed to the actual callee. Otherwise,return STATUS_ACCESS_DENIED
		    pushfd
			pushad
			mov ebx,esp
			add ebx,40
			push ebx
			call check				// ����check
			cmp eax,1
			jne block

			//proceed to the actual callee
			popad
			popfd
			jmp RealCallee			// ����ԭ���ĺ���

			//return STATUS_ACCESS_DENIED
block:popad
	  mov ebx, dword ptr[esp+8]
	  mov dword ptr[ebx],0
		  mov eax,0xC0000022L
		  popfd
		  ret 32
	}
}


NTSTATUS DrvDispatch(IN PDEVICE_OBJECT device,IN PIRP Irp)
{
	UCHAR * buff = NULL; 
	UCHAR * tmp = NULL;
	ULONG a;
	ULONG base;

	PIO_STACK_LOCATION loc=IoGetCurrentIrpStackLocation(Irp);

	DbgPrint("[Protector] DrvDispatch");
	if(loc->Parameters.DeviceIoControl.IoControlCode==1000)
	{
		buff=(UCHAR*)Irp->AssociatedIrp.SystemBuffer;

		// hook service dispatch table
		memmove(&Index,&(buff[INDEX_INPUT_DATA_NTCREATESECTION*4]),4);
		a=4*Index+(ULONG)KeServiceDescriptorTable->ServiceTable;
		base=(ULONG)MmMapIoSpace(MmGetPhysicalAddress((void*)a),4,0);
		a=(ULONG)&Proxy;

		_asm
		{
			mov eax,base
			mov ebx,dword ptr[eax]
			mov RealCallee,ebx
			mov ebx,a
			mov dword ptr[eax],ebx
		}

		MmUnmapIoSpace((char*)base,4);

		// ��ȡ����������
		memmove(&a,&buff[INDEX_INPUT_DATA_EXCHANGE_BUFFER*4],4);
		exchange_buffer=(char*)MmMapIoSpace(MmGetPhysicalAddress((void*)a),256,0);
		
		// ��ȡϵͳ·��
		// ע����ڴ˴����ڴ���˵�����clientʹ����ʳ�ڴ�ᵼ�´���
		// �������������������������
		// ������Ϊ�ڴ��ͷŶ�����Ĵ���
		memmove(&a,&buff[INDEX_INPUT_DATA_SYSDIR*4],4);
		tmp=(char*)MmMapIoSpace(MmGetPhysicalAddress((void*)a),256,0);
		memcpy(SystemDir, tmp, 256);
		LenSystemDir = strlen(SystemDir);
	}



	Irp->IoStatus.Status=0;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return 0;
}



// nothing special
NTSTATUS DrvCreateClose(IN PDEVICE_OBJECT device,IN PIRP Irp)
{
	DbgPrint("[Protector] CreateClose");
	Irp->IoStatus.Information=0;
	Irp->IoStatus.Status=0;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return 0;
}



// nothing special -just a cleanup
void DrvUnload(IN PDRIVER_OBJECT driver)
{
	UNICODE_STRING devlink;
	ULONG a,base;

	DbgPrint("[Protector] DrvUnload");
	//unhook dispatch table
	a=4*Index+(ULONG)KeServiceDescriptorTable->ServiceTable;
	base=(ULONG)MmMapIoSpace(MmGetPhysicalAddress((void*)a),4,0);

	_asm
	{
		mov eax,base
			mov ebx,RealCallee
			mov dword ptr[eax],ebx
	}

	MmUnmapIoSpace((char*)base,4);
	MmUnmapIoSpace(exchange_buffer,256);

	RtlInitUnicodeString(&devlink,devicelink);
	IoDeleteSymbolicLink(&devlink);
	IoDeleteDevice(driver->DeviceObject);
}


//DriverEntry just creates our device - nothing special here
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver,IN PUNICODE_STRING path)
{
	PDEVICE_OBJECT devobject=0;
	UNICODE_STRING devlink,devname;
	ULONG a,b;

	DbgPrint("[Protector] DriverEntry");
	RtlInitUnicodeString(&devname,devicename);
	RtlInitUnicodeString(&devlink,devicelink);

	IoCreateDevice(driver,256,&devname,FILE_DEVICE_UNKNOWN,0,TRUE,&devobject);
	IoCreateSymbolicLink(&devlink,&devname);



	driver->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DrvDispatch;
	driver->MajorFunction[IRP_MJ_CREATE]=DrvCreateClose;
	driver->MajorFunction[IRP_MJ_CLOSE]=DrvCreateClose;
	driver->DriverUnload=DrvUnload;
	KeInitializeEvent(&g_mutex_event,SynchronizationEvent,1);

	return 0;
}