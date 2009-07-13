
#include "ntddk.h"
#include "driver_const.h"

struct SYS_SERVICE_TABLE { 
	void **ServiceTable; 
	unsigned long CounterTable; 
	unsigned long ServiceLimit; 
	void **ArgumentsTable; 
}; 

const WCHAR devicename[]=L"\\Device\\Protector";
const WCHAR devicelink[]=L"\\DosDevices\\PROTECTOR";

// ϵͳ·����ϵͳ·������
// �����޷��������API, 
// ��װ�����ڼ�����������ʱ������ز���

char SystemDir[PATH_BUF_MAX];
int  LenSystemDir = 0;


// ��֤�ܹ��������Check
KEVENT g_mutex_event; 
ULONG Index;
ULONG RealCallee;
ULONG disable_driver = 0; // ��������̽��������Ƚ��н�ֹ"���̴�������"
const int max_check_num = 10; // ������һ��ʱ�䣬�ϲ����û�з�Ӧ����ֱ�ӷ���true

// ���ϲ���򽻻��ĳ���
char * exchange_buffer;
extern struct SYS_SERVICE_TABLE *KeServiceDescriptorTable; 

int checkfilepath(const char *str) {
	const char * DOTEXT = ".exe";
	const int DOTEXE_LENGTH = 4;
	int len = 0;
	
	// ���������ʵ���ó��֣���������
	if (NULL == str) {
		goto passed;
	} 
	
	len = strlen(str);
	if (len < DOTEXE_LENGTH) {
		// ̫���˰�
		goto passed;
	}

	// �Ƚ�����ַ��ַ��ǲ���.exe
	if(_strnicmp(&(str[len - DOTEXE_LENGTH]), DOTEXT, DOTEXE_LENGTH)) { 
		DbgPrint("[Protector] [NOT EXE]%s passed", str);
		goto passed;
	}
	
	// �����{systemdir}��ͷ�򷵻�Ϊ��
	if(0 == _strnicmp(str, SystemDir, LenSystemDir)) { 
		DbgPrint("[Protector] [IN SYSTEM DIR] %s passed", str);
		goto passed;
	}

	DbgPrint("[Protector] Need to check %s Failed", str);
	return 0;
passed:
	return 1;
}


//this function decides whether we should allow NtCreateSection() call to be successfull
ULONG __stdcall check(PULONG arg)
{
	NTSTATUS status;
	HANDLE hand=0;
	PFILE_OBJECT fileObject=0;
	POBJECT_HANDLE_INFORMATION info;
	ULONG notify = 0;
	ULONG result = 0;
	ULONG notcheck = 0;
	int cnt = 0;
	ANSI_STRING deviceVolumn_a = {0};
	UNICODE_STRING deviceVolumn_u = {0};
	ANSI_STRING filepath_withoutV = {0};
	char filepath[PATH_BUF_MAX] = {0};
	
	
	//check the flags. If PAGE_EXECUTE access to the section is not requested,
	//it does not make sense to be bothered about it	
	if((arg[4]&0xf0)==0)
		return 1;
	if((arg[5]&0x01000000)==0)
		return 1;
	
	// ����������򱻽���
	if (disable_driver == 1)
		return 1;


	//get the file name via the file handle
	hand=(HANDLE)arg[6];		// ���������������п�ִ���ļ��ľ��
	ObReferenceObjectByHandle(hand,0,0,KernelMode,&fileObject,(POBJECT_HANDLE_INFORMATION)&info);
	if(!fileObject) {
		result = 1;
		goto exit;
	}
	
	// ��ȡ�̷�
	RtlVolumeDeviceToDosName(fileObject->DeviceObject,&deviceVolumn_u);
	RtlUnicodeStringToAnsiString(&deviceVolumn_a,&deviceVolumn_u,1);
	RtlUnicodeStringToAnsiString(&deviceVolumn_a,&deviceVolumn_u,1);
	RtlUnicodeStringToAnsiString(&filepath_withoutV,&fileObject->FileName,1);
	
	if (PATH_BUF_MAX < deviceVolumn_a.Length + filepath_withoutV.Length) {
		result = 1;
		goto exit;
	}
	strncpy(filepath,deviceVolumn_a.Buffer,PATH_BUF_MAX); 
	strncat(filepath, filepath_withoutV.Buffer, PATH_BUF_MAX);
	

	//  ���Ӧ�ó���
	if (checkfilepath(filepath)) {
		result = 1;
		goto exit;
	}


	//now we are going to ask user's opinion. Write file name to the buffer, and wait until
	//the user indicates the response (1 as a first DWORD means we can proceed)

	//synchronize access to the buffer
	KeWaitForSingleObject(&g_mutex_event,Executive,KernelMode,0,0);


	// ���ļ�·����·�����ȷ��뵽������֮��
	// ͨ�����ַ�ʽ�ϴ���Ӧ�ó���
	// ʹ��memcpy��֤����'\0'�����Ը��Ƶ�����������
	memcpy(&exchange_buffer[ADDR_EXCHANGE_FILEPATH],filepath, PATH_BUF_MAX);
	
	// ���á�Ӧ�ó�����ɡ�������
	notify = 1;
	memmove(&exchange_buffer[ADDR_EXCHANGE_NOTIFY_APP],&notify,4);

	// �ȴ�Ӧ�ó���������Ӧ
	while(1)
	{
		// �ȴ�200ms, ��Ȼ���ܻ���;ֹͣ
		LARGE_INTEGER li;
		li.QuadPart=-200;
		KeDelayExecutionThread(KernelMode, FALSE, &li);
		
		// checked�����˿ͻ�Ӧ�ó����Ƿ���������Ӧ
		memmove(&notcheck,&exchange_buffer[ADDR_EXCHANGE_APP_COMP],4);
		
		// Ϊ�˱��⵱���û�������������ٳٵò���������µ�����
		// �������������ȴ�5��
		if (cnt > max_check_num) {
			DbgPrint("[Protector] check timeout");
			result = 1;
			break;
		}
		if(!notcheck) {
			// ��ȡ���
			DbgPrint("[Protector] result return");
			memmove(&result,&exchange_buffer[ADDR_EXCHANGE_APP_RESULT],4);
			break;
		}
		
		cnt++;
	}

exit:
	// �������󻺳���
	// ���Ӧ�ó���û��������������ܲ������ã�������ǻ����������ֶ�����һ��
	memset(&exchange_buffer[ADDR_EXCHANGE_NOTIFY_APP], 0, 4);
	// ʹ���������������
	KeSetEvent(&g_mutex_event,0,0);
	
	if (0 != fileObject) {
		ObDereferenceObject(fileObject);
	}
	
	RtlFreeAnsiString(&deviceVolumn_a);
	RtlFreeAnsiString(&filepath_withoutV);
	RtlFreeUnicodeString(&deviceVolumn_u);
	
	DbgPrint("[Protector] Check complete, path %s return %d", filepath, result);
	return result;
}


//just saves execution contect and calls check() 
_declspec(naked) Proxy()
{
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
	if(loc->Parameters.DeviceIoControl.IoControlCode==IO_CONTROL_BUFFER_INIT)
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
		exchange_buffer=(char*)MmMapIoSpace(MmGetPhysicalAddress((void*)a),EXCHANGE_BUFFER_SIZE,0);
		
		// ��ȡϵͳ·��
		// ע����ڴ˴����ڴ���˵�����clientʹ����ʳ�ڴ�ᵼ�´���
		// �������������������������
		// ������Ϊ�ڴ��ͷŶ�����Ĵ���
		memmove(&a,&buff[INDEX_INPUT_DATA_SYSDIR*4],4);
		tmp=(char*)MmMapIoSpace(MmGetPhysicalAddress((void*)a),PATH_BUF_MAX,0);
		memcpy(SystemDir, tmp, PATH_BUF_MAX);
		LenSystemDir = strlen(SystemDir);
	}



	Irp->IoStatus.Status=0;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return 0;
}



// nothing special
NTSTATUS DrvClose(IN PDEVICE_OBJECT device,IN PIRP Irp)
{
	DbgPrint("[Protector] DrvClose==============");
	// ��Ӧ�ó������ر�ʱ���˺����ᱻ����
	// ��ʱ���򱻷Ƿ��ر�
	disable_driver = 1;
	
	Irp->IoStatus.Information=0;
	Irp->IoStatus.Status=0;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return 0;
}

NTSTATUS DrvCreate(IN PDEVICE_OBJECT device,IN PIRP Irp)
{
	DbgPrint("[Protector] DrvCreate==============");

	disable_driver = 0;
	
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
	MmUnmapIoSpace(exchange_buffer, EXCHANGE_BUFFER_SIZE);

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
	driver->MajorFunction[IRP_MJ_CREATE]=DrvCreate;
	driver->MajorFunction[IRP_MJ_CLOSE]=DrvClose;
	driver->DriverUnload=DrvUnload;
	KeInitializeEvent(&g_mutex_event,SynchronizationEvent,1);

	return 0;
}