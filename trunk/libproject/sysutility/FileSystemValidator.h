#ifndef _SYSUTILITY_FILESYSTEMVALIDATOR_H__
#define _SYSUTILITY_FILESYSTEMVALIDATOR_H__


#define FILE_VALIDATE_SUCCESS					0
#define FILE_VALIDATE_FAILED					-1

// class class FileSystemValidator 
// 验证软件的文件系统是否完整！ 主要是目录是否存在
class FileSystemValidator {
public:
	FileSystemValidator(void);
	~FileSystemValidator(void);

public:
	// 查看路径是否是一个合法的路径
	bool validateDir(const TCHAR * installpath);

	int repair(const TCHAR * installpath);
	int repair(HMODULE hModule);

private:
	void setErrno(int err);
	int errno_;
};

#endif  // _SYSUTILITY_FILESYSTEMVALIDATOR_H__
