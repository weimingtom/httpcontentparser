#ifndef _SYSUTILITY_FILESYSTEMVALIDATOR_H__
#define _SYSUTILITY_FILESYSTEMVALIDATOR_H__


#define FILE_VALIDATE_SUCCESS					0
#define FILE_VALIDATE_FAILED					-1

// class class FileSystemValidator 
// ��֤������ļ�ϵͳ�Ƿ������� ��Ҫ��Ŀ¼�Ƿ����
class FileSystemValidator {
public:
	FileSystemValidator(void);
	~FileSystemValidator(void);

public:
	// �鿴·���Ƿ���һ���Ϸ���·��
	bool validateDir(const TCHAR * installpath);

	int repair(const TCHAR * installpath);
	int repair(HMODULE hModule);

private:
	void setErrno(int err);
	int errno_;
};

#endif  // _SYSUTILITY_FILESYSTEMVALIDATOR_H__
