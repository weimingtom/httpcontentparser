#include "StdAfx.h"
#include ".\filesystemvalidator.h"
#include ".\apputility.h"

#define INVALIDATE_INSTALL_PATH 1


FileSystemValidator::FileSystemValidator(void)
{
}

FileSystemValidator::~FileSystemValidator(void)
{
}

bool FileSystemValidator::validateDir(const TCHAR * installpath) {
	return true;
}

int FileSystemValidator::repair(HMODULE hModule) {
	TCHAR filename[MAX_PATH], installPath[MAX_PATH];

	/// 获取安装路径
	GetModuleFileName(hModule, filename, MAX_PATH);
	GetFileNameDir(filename, installPath, MAX_PATH);

	return repair(installPath);

}

int FileSystemValidator::repair(const TCHAR * installpath) {
	if (!validateDir(installpath)) {
		setErrno(INVALIDATE_INSTALL_PATH);
		return FILE_VALIDATE_FAILED;
	}

	// 查看Screen目录


	return FILE_VALIDATE_SUCCESS;
}

//=================
//
void FileSystemValidator::setErrno(int err) {
	if (err != FILE_VALIDATE_SUCCESS)
		errno_ = err;
}