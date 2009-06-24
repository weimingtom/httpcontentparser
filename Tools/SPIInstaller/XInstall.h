
#ifndef _SPI_INSTALLER_XINSTALL_H__
#define _SPI_INSTALLER_XINSTALL_H__

#include <app_constants.h>

#define	XERR_SUCCESS						0
#define XERR_PROVIDER_NOT_INSTALL			-801
#define XERR_PROVIDER_ALREADY_INSTALL		-802
#define XERR_PROVIDER_OPEN_REG_FAILED		-803
#define XERR_PROVIDER_SAVE_PATH_FAILED		-804
#define XERR_PROVIDER_READ_VALUE_FAILED		-805
#define XERR_PROVIDER_CREATE_ITEM_FAILED	-806
#define XERR_PROVIDER_SET_VALUE_FAILED		-807
#define XERR_PROVIDER_REG_DELETE_FAILED		-808

#include <windows.h>

class CXInstall
{
private:
	int EnumHookKey(BOOL IsRemove = FALSE);
	int SaveHookKey(HKEY hkey, LPCTSTR sSubKey, BOOL IsRemove = FALSE);

public:
	BOOL	IsWinsock2();
	BOOL	IsInstalled(TCHAR *sPathName = NULL);
	int		InstallProvider(TCHAR *sPathName);
	int		RemoveProvider();

public:
	BOOL ReadReg(
		TCHAR	*sKey,
		BYTE	*pBuffer,
		DWORD	dwBufSize, 
		HKEY	hkey	= HKEY_LOCAL_MACHINE, 
		TCHAR	*sSubKey = REG_INSTALL_KEY,
		DWORD	ulType	= REG_BINARY
		);

	BOOL SaveReg(
		TCHAR	*sKey, 
		BYTE	*pBuffer, 
		DWORD	dwBufSize, 
		HKEY	hkey	= HKEY_LOCAL_MACHINE, 
		TCHAR	*sSubKey = REG_INSTALL_KEY,	
		DWORD	ulType	= REG_BINARY
		);

	BOOL DeleteReg(
		HKEY	hkey	= HKEY_LOCAL_MACHINE,
		TCHAR	*sSubKey = REG_INSTALL_KEY, 
		TCHAR	*sItem	= NULL
		);

public:
	TCHAR m_sPathName[MAX_PATH];
};

#endif // _SPI_INSTALLER_XINSTALL_H__