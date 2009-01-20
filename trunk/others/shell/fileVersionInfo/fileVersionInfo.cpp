// fileVersionInfo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define FILE_PROPERY_COMMENTS			TEXT("Comments")
#define FILE_PROPERY_INTERNAL_NAME		TEXT("InternalName")
#define FILE_PROPERY_PRODUCT_NAME		TEXT("ProductName")
#define FILE_PROPERY_COMPANY_NAME		TEXT("CompanyName")
#define FILE_PROPERY_COPYRIGHT			TEXT("LegalCopyright")
#define FILE_PROPERY_PRODUCT_VER		TEXT("ProductVersion")
#define FILE_PROPERY_DESCRITPTION		TEXT("FileDescription")
#define FILE_PROPERY_TRADEMARKS			TEXT("LegalTrademarks")
#define FILE_PROPERY_PRIVATEBUILD		TEXT("PrivateBuild")
#define FILE_PROPERY_FILEVERSION		TEXT("FileVersion")
#define FILE_PROPERY_ORIGINALFILENAME	TEXT("OriginalFilename")
#define FILE_PROPERY_SPECIALBUILD		TEXT("SpecialBuild")


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwHandle = 0;
	TCHAR filename[] = TEXT("E:\\World of Warcraft\\Wow.exe");
	DWORD size = GetFileVersionInfoSize(filename, &dwHandle);

	if (0 == size) {
		std::cout<<"GetFileVersionInfoSize returns 0!"<<std::endl;
	}

	BYTE * pBlock = new BYTE[size];
	GetFileVersionInfo(filename, dwHandle, size, pBlock);

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
	TCHAR * p;
	// Read the file description for each language and code page.

	for(int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
	{
		// Retrieve file description for language and code page "i". 
		_sntprintf(SubBlock, MAX_PATH, TEXT("\\StringFileInfo\\%04x%04x\\%s"),lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage, FILE_PROPERY_DESCRITPTION);
		VerQueryValue(pBlock, SubBlock, &lpBuffer, &dwBytes); 
		p = (TCHAR *) lpBuffer;
		std::cout<<"File Description : " << p << std::endl;

		// Retrieve file Internal Name for language and code page "i". 
		_sntprintf(SubBlock, MAX_PATH, TEXT("\\StringFileInfo\\%04x%04x\\%s"),lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage, FILE_PROPERY_INTERNAL_NAME);
		VerQueryValue(pBlock, SubBlock, &lpBuffer, &dwBytes); 
		p = (TCHAR *) lpBuffer;
		std::cout<<"File internal name : " << (TCHAR*)lpBuffer << std::endl;

		// Retrieve file Internal Name for language and code page "i". 
		_sntprintf(SubBlock, MAX_PATH, TEXT("\\StringFileInfo\\%04x%04x\\%s"),lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage, FILE_PROPERY_COMPANY_NAME);
		VerQueryValue(pBlock, SubBlock, &lpBuffer, &dwBytes); 
		p = (TCHAR *) lpBuffer;
		std::cout<<"File company name : " << (TCHAR*)lpBuffer << std::endl;
	}


	return 0;
}

