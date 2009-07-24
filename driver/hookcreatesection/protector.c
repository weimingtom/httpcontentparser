
#include "ntddk.h"
#include "driver_const.h"


struct SYS_SERVICE_TABLE { 
	void **ServiceTable; 
	unsigned long CounterTable; 
	unsigned long ServiceLimit; 
	void **ArgumentsTable; 
}; 


// 系统路径及系统路径长度
// 由于无法调用相关API, 
// 安装程序将在加载驱动程序时传入相关参数

char SystemDir[PATH_BUF_MAX];
int  LenSystemDir = 0;

// 当用户应用程序启动后， 此函数设为1
// 当应用程序关闭后，此变量设为0
// 当此变量值为1的时候，不再接受IoControl的控制
// 当此函数为0是，不在检测应用程序创建
int  ClientAppLaunch = 0;

// 保证能够互斥调用Check
FAST_MUTEX mutex_exchange_buffer;
ULONG Index;
ULONG RealCallee;
const int max_check_num = 10; // 如果检测一段时间，上层程序没有反应，则直接返回true

// 与上层程序交互的程序。
char * exchange_buffer;
extern struct SYS_SERVICE_TABLE *KeServiceDescriptorTable; 

int InstallAPIHook();
int UninstallAPIHook();
int checkfilepath(const char *str);


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
	
	// 客户应用程序已经关闭
	if (ClientAppLaunch == 0) {
		return 1;
	}
	
	//check the flags. If PAGE_EXECUTE access to the section is not requested,
	//it does not make sense to be bothered about it	
	if((arg[4]&0xf0)==0)
		return 1;
	if((arg[5]&0x01000000)==0)
		return 1;

	//get the file name via the file handle
	hand=(HANDLE)arg[6];		// 第六个参数保存有可执行文件的句柄
	ObReferenceObjectByHandle(hand,0,0,KernelMode,&fileObject,(POBJECT_HANDLE_INFORMATION)&info);
	if(!fileObject) {
		result = 1;
		goto exit;
	}
	
	// 获取盘符
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
	

	//  检测应用程序
	if (checkfilepath(filepath)) {
		result = 1;
		goto exit;
	}
	
	DbgPrint("[Protector] {%s} Need to poat to application to check!", filepath);

	//synchronize access to the buffer
	ExAcquireFastMutex(&mutex_exchange_buffer);

	// 将文件路径及路径长度放入到缓冲区之中
	// 通过此种方式上传给应用程序
	// 使用memcpy保证所有'\0'都可以复制到缓冲区当中
	memcpy(&exchange_buffer[ADDR_EXCHANGE_FILEPATH],filepath, PATH_BUF_MAX);	
	// 重置“应用程序完成”缓冲区
	notify = 1;
	memmove(&exchange_buffer[ADDR_EXCHANGE_NOTIFY_APP],&notify,4);

	// 等待应用程序作出回应
	while(1)
	{
		// 等待200ms, 当然可能会中途停止
		LARGE_INTEGER li;
		li.QuadPart=-200;
		KeDelayExecutionThread(KernelMode, FALSE, &li);
		
		// checked保存了客户应用程序是否做出了相应
		memmove(&notcheck,&exchange_buffer[ADDR_EXCHANGE_APP_COMP],4);
		
		// 为了避免当用用户程序结束，而迟迟得不到结果导致的死锁
		// 我们最多在这里等待5次
		if (cnt > max_check_num) {
			DbgPrint("[Protector] check timeout");
			result = 1;
			break;
		}
		if(!notcheck) {
			// 获取结果
			memmove(&result,&exchange_buffer[ADDR_EXCHANGE_APP_RESULT],4);
			DbgPrint("[Protector] result return %d", result);
			break;
		}
		
		cnt++;
	}
	
	// 重置请求缓冲区
	// 如果应用程序没有启动，这里可能不被重置，因此我们还是在这里手动重置一次
	memset(&exchange_buffer[ADDR_EXCHANGE_NOTIFY_APP], 0, 4);
	// 使其他请求可以运行
	
	ExReleaseFastMutex(&mutex_exchange_buffer);
	
exit:
	if (0 != fileObject) {
		ObDereferenceObject(fileObject);
	}
	
	RtlFreeAnsiString(&deviceVolumn_a);
	RtlFreeAnsiString(&filepath_withoutV);
	RtlFreeUnicodeString(&deviceVolumn_u);

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
			call check				// 调用check
			cmp eax,1
			jne block

			//proceed to the actual callee
			popad
			popfd
			jmp RealCallee			// 调用原来的函数

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
	
	PIO_STACK_LOCATION loc=IoGetCurrentIrpStackLocation(Irp);
	
	
	if (ClientAppLaunch == 1) {
		DbgPrint("[Protector] ClientApp Has Initialize, Return directly");
		goto exit;
	} else {
		DbgPrint("[Protector] DrvDispatch Initialize");
		ClientAppLaunch = 1;
	}

	
	ExAcquireFastMutex(&mutex_exchange_buffer);
	if(loc->Parameters.DeviceIoControl.IoControlCode==IO_CONTROL_BUFFER_INIT)
	{
		buff=(UCHAR*)Irp->AssociatedIrp.SystemBuffer;

		// hook service dispatch table
		memmove(&Index,&(buff[INDEX_INPUT_DATA_NTCREATESECTION*4]),4);
		InstallAPIHook();

		// 获取交换缓冲区
		memmove(&a,&buff[INDEX_INPUT_DATA_EXCHANGE_BUFFER*4],4);
		exchange_buffer=(char*)MmMapIoSpace(MmGetPhysicalAddress((void*)a),EXCHANGE_BUFFER_SIZE,0);
		
		// 获取系统路径
		// 注意对于此处的内存来说，如果client使用零食内存会导致错误
		// 因此我们在这里拷贝到自身缓冲区
		// 避免因为内存释放而引起的错误
		memmove(&a,&buff[INDEX_INPUT_DATA_SYSDIR*4],4);
		tmp=(char*)MmMapIoSpace(MmGetPhysicalAddress((void*)a),PATH_BUF_MAX,0);
		memcpy(SystemDir, tmp, PATH_BUF_MAX);
		LenSystemDir = strlen(SystemDir);
	}

	ExReleaseFastMutex(&mutex_exchange_buffer);
exit:
	Irp->IoStatus.Status=0;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return 0;
}



// nothing special
NTSTATUS DrvClose(IN PDEVICE_OBJECT device,IN PIRP Irp)
{
	DbgPrint("[Protector] DrvClose==============");
	// 当应用程序程序关闭时，此函数会被调用
	// 即使是程序被非法关闭
	// 那么既然此函数已经被调用，
	// 那么上面的检测应用程序创建的代码应该也已经失效了吧
	
	ExAcquireFastMutex(&mutex_exchange_buffer);
	
	// 如果安装了APIHook则卸载它
	// 玩一起他程序在调用一次IOCtrl, 那不是安装了两次API Hook
	if (ClientAppLaunch != 0) {
		UninstallAPIHook();
	}
	
	ClientAppLaunch = 0;
	Irp->IoStatus.Information=0;
	Irp->IoStatus.Status=0;
	ExReleaseFastMutex(&mutex_exchange_buffer);
	
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return 0;
}

NTSTATUS DrvCreate(IN PDEVICE_OBJECT device,IN PIRP Irp)
{
	DbgPrint("[Protector] DrvCreate==============");
		
	Irp->IoStatus.Information=0;
	Irp->IoStatus.Status=0;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return 0;
}


// nothing special -just a cleanup
void DrvUnload(IN PDRIVER_OBJECT driver)
{
	UNICODE_STRING devlink;
	DbgPrint("[Protector] DrvUnload");

	RtlInitUnicodeString(&devlink,devicelink);
	IoDeleteSymbolicLink(&devlink);
	IoDeleteDevice(driver->DeviceObject);
}


//DriverEntry just creates our device - nothing special here
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver,IN PUNICODE_STRING path)
{
	PDEVICE_OBJECT devobject = 0;
	UNICODE_STRING devlink,devname;
	NTSTATUS ntStatus;
	NTSTATUS ntResult;
	ULONG a,b;

	DbgPrint("[Protector] DriverEntry");
	RtlInitUnicodeString(&devname,devicename);
	RtlInitUnicodeString(&devlink,devicelink);

	// 如果设备已经存在，则先删除它
	
	ntStatus = IoCreateDevice(driver,256,&devname,FILE_DEVICE_UNKNOWN,0,TRUE,&devobject);
	if (STATUS_SUCCESS == ntStatus) {
		IoCreateSymbolicLink(&devlink,&devname);
		ntResult = ntStatus;
	} else if (STATUS_OBJECT_NAME_EXISTS == ntStatus){
		// 如果已经创建代表用户已经打开驱动
		// 直接退出，并返回失败
		DbgPrint("[Protector] The Device has exist.");
		ntResult = ntStatus;
		goto exit;
	} else if(STATUS_OBJECT_NAME_COLLISION == ntStatus){
		// STATUS_INSUFFICIENT_RESOURCES
		ntResult = ntStatus;
		goto exit;
	} else {
		// 直接返回吧
		ntResult = ntStatus;
		goto exit;
	}



	driver->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DrvDispatch;
	driver->MajorFunction[IRP_MJ_CREATE]=DrvCreate;
	driver->MajorFunction[IRP_MJ_CLOSE]=DrvClose;
	driver->DriverUnload=DrvUnload;
	ExInitializeFastMutex(&mutex_exchange_buffer);
	
	ntResult = STATUS_SUCCESS;
exit:
	return ntResult;
}

InstallAPIHook() {
	ULONG a;
	ULONG base;
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
}

int UninstallAPIHook() {
	ULONG a,base;
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
}

int checkfilepath(const char *str) {
	const char * DOTEXT = ".exe";
	const int DOTEXE_LENGTH = 4;
	int len = 0;
	
	// 这种情况其实不该出现，防御编码
	if (NULL == str) {
		goto passed;
	} 
	
	len = strlen(str);
	if (len < DOTEXE_LENGTH) {
		// 太短了吧
		goto passed;
	}

	// 比较最后字符字符是不是.exe
	if(_strnicmp(&(str[len - DOTEXE_LENGTH]), DOTEXT, DOTEXE_LENGTH)) { 
		goto passed;
	}
	
	// 如果以{systemdir}开头则返回为真
	if(0 == _strnicmp(str, SystemDir, LenSystemDir)) { 
		goto passed;
	}

	return 0;
passed:
	return 1;
}