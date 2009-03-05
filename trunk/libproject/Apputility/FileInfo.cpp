#include "StdAfx.h"
#include ".\fileinfo.h"
#include <string>
#include <utility\strutility.h>
#include <shellapi.h>

#define FILE_PROPERY_COMMENTS				TEXT("Comments")
#define FILE_PROPERY_INTERNAL_NAME		TEXT("InternalName")
#define FILE_PROPERY_PRODUCT_NAME		TEXT("ProductName")
#define FILE_PROPERY_COMPANY_NAME		TEXT("CompanyName")
#define FILE_PROPERY_COPYRIGHT					TEXT("LegalCopyright")
#define FILE_PROPERY_PRODUCT_VER			TEXT("ProductVersion")
#define FILE_PROPERY_DESCRITPTION			TEXT("FileDescription")
#define FILE_PROPERY_TRADEMARKS			TEXT("LegalTrademarks")
#define FILE_PROPERY_PRIVATEBUILD			TEXT("PrivateBuild")
#define FILE_PROPERY_FILEVERSION				TEXT("FileVersion")
#define FILE_PROPERY_ORIGINALFILENAME	TEXT("OriginalFilename")
#define FILE_PROPERY_SPECIALBUILD				TEXT("SpecialBuild")

CFileInfo::CFileInfo(const strutility::_tstring &filename) : filename_(filename),
	hIcon_(NULL), product_name_(""), company_(""), description_("") {
	getInformation();
}

CFileInfo::~CFileInfo(void) {
}

void CFileInfo::getInformation() {
	DWORD dwHandle = 0;
	DWORD size = GetFileVersionInfoSize(filename_.c_str(), &dwHandle);

	if (0 == size) {
		return;
	}

	BYTE * pBlock = new BYTE[size];
	GetFileVersionInfo(filename_.c_str(), dwHandle, size, pBlock);

	LPVOID lpBuffer  = NULL;
	UINT	cbTranslate;


	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;


	VerQueryValue(pBlock, 
		TEXT("\\VarFileInfo\\Translation"),
		(LPVOID*)&lpTranslate,
		&cbTranslate);

	TCHAR SubBlock[MAX_PATH];
	UINT dwBytes;

	// Read the file description for each language and code page.
	for(int i=0; i < static_cast<int>((cbTranslate/sizeof(struct LANGANDCODEPAGE))); i++ )
	{
		// Retrieve file description for language and code page "i". 
		_sntprintf(SubBlock, MAX_PATH, TEXT("\\StringFileInfo\\%04x%04x\\%s"),lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage, FILE_PROPERY_DESCRITPTION);
		VerQueryValue(pBlock, SubBlock, &lpBuffer, &dwBytes); 
		description_  = (TCHAR *) lpBuffer;

		// Retrieve file Internal Name for language and code page "i". 
		_sntprintf(SubBlock, MAX_PATH, TEXT("\\StringFileInfo\\%04x%04x\\%s"),lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage, FILE_PROPERY_PRODUCT_NAME);
		VerQueryValue(pBlock, SubBlock, &lpBuffer, &dwBytes); 
		product_name_ = (TCHAR *) lpBuffer;

		// Retrieve file Internal Name for language and code page "i". 
		_sntprintf(SubBlock, MAX_PATH, TEXT("\\StringFileInfo\\%04x%04x\\%s"),lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage, FILE_PROPERY_COMPANY_NAME);
		VerQueryValue(pBlock, SubBlock, &lpBuffer, &dwBytes); 
		company_ = (TCHAR *) lpBuffer;
	}

	// ªÒ»°Õº±»
	SHFILEINFO  info = {0};
	SHGetFileInfo(filename_.c_str(), 0 , &info, sizeof(info), SHGFI_ICON);
	hIcon_ = info.hIcon;
}

