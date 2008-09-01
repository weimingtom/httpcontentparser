#include "stdafx.h"
#include "sysutility.h"
#include <tchar.h>
#include <direct.h>
#include <conio.h>
#include <process.h>



typedef DWORD (WINAPI *RSP)(DWORD dwProcessId,DWORD dwType);
void RegisterServiceProcess() {
	HMODULE m_hKernel = ::GetModuleHandle(TEXT("Kernel32.DLL"));
	RSP m_rsp = (RSP)::GetProcAddress(m_hKernel, ("RegisterServiceProcessW"));
	m_rsp(::GetCurrentProcessId(),1);
}

namespace {
	DWORD GetScreenSaveDir(TCHAR *moduleDir, const int len, HMODULE hModule);
	DWORD GenerateImageFile(TCHAR *file, const int len, HMODULE hModule);	// 自动生成文件名
	void GetScreen(TCHAR* filename);
	BOOL CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi);
	BOOL CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
};

void StartEyecare(HMODULE hModule) {
}

void SaveScreen(HMODULE hModule) {
	// 获取文件名
	TCHAR filename[MAX_PATH];
	GenerateImageFile(filename, MAX_PATH, hModule);

	GetScreen(filename);
}

void ClearScreen(HMODULE hModule) {
	TCHAR dir[MAX_PATH], arg1 [MAX_PATH];
	GetScreenSaveDir(dir, MAX_PATH, hModule);
	_sntprintf(arg1, MAX_PATH , "%d//*", dir);
	_execlp("del", arg1, "\q");
}


//////////////////////////////////////////////////
// utility functions

namespace {
	
DWORD GetScreenSaveDir(TCHAR *screendir, const int len, HMODULE hModule) {
	TCHAR moduleName[MAX_PATH], driver[MAX_PATH], dir[MAX_PATH], moduleDir[MAX_PATH];
	DWORD length = GetModuleFileName(hModule, moduleName, MAX_PATH);

	_tsplitpath(moduleName, driver, dir, NULL, NULL);
	_sntprintf(moduleDir, MAX_PATH, "%s%s", driver, dir);

	_sntprintf(screendir, MAX_PATH, TEXT("%s%s\\"), moduleDir,TEXT("Screen"));
	if (_tchdir(screendir) == -1)
		_tmkdir(screendir);

	return _tcslen(screendir);
}

DWORD GenerateImageFile(TCHAR *fullpath, const int len, HMODULE hModule) {
	TCHAR dir[MAX_PATH];
	GetScreenSaveDir(dir, MAX_PATH, hModule);

	// 获取时间
	SYSTEMTIME time;
	GetLocalTime(&time);
	TCHAR filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, TEXT("%02d%02d%04d%02d%02d%02d.bmp"), time.wMonth, time.wDay,time.wYear, time.wHour, time.wMinute, time.wSecond);

	// 获取到目录
	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), dir, filename);
	return _tcslen(fullpath);
}


void GetScreen(TCHAR* filename) {
	// 记录屏幕
	CDC dcScreen;
	dcScreen.CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	const int width = GetDeviceCaps(dcScreen.GetSafeHdc(), HORZRES);
	const int height = GetDeviceCaps(dcScreen.GetSafeHdc(), VERTRES);	

	// 记录屏幕
	CDC dcMem;
	CBitmap bmp;
	dcMem.CreateCompatibleDC(NULL);
	bmp.CreateCompatibleBitmap(&dcScreen, width, height);
	CBitmap* pOldBmp = dcMem.SelectObject(&bmp);
	dcMem.BitBlt(0,0,width, height, &dcScreen, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOldBmp);

	PBITMAPINFO bmpinfo;
	if (TRUE == CreateBitmapInfoStruct((HBITMAP)bmp.GetSafeHandle(), bmpinfo)) {
		CreateBMPFile(filename,bmpinfo, (HBITMAP)bmp.GetSafeHandle(), dcMem.GetSafeHdc());
		LocalFree((HLOCAL)bmpinfo);
	}
}

BOOL CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi)
{ 
	BITMAP bmp; 
	//PBITMAPINFO pbmi; 
	WORD    cClrBits; 

	// Retrieve the bitmap color format, width, and height. 
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
		return FALSE;

	// Convert the color format to a count of bits. 
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
	if (cClrBits == 1) 
		cClrBits = 1; 
	else if (cClrBits <= 4) 
		cClrBits = 4; 
	else if (cClrBits <= 8) 
		cClrBits = 8; 
	else if (cClrBits <= 16) 
		cClrBits = 16; 
	else if (cClrBits <= 24) 
		cClrBits = 24; 
	else cClrBits = 32; 

	// Allocate memory for the BITMAPINFO structure. (This structure 
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
	// data structures.) 

	if (cClrBits != 24) 
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
		sizeof(BITMAPINFOHEADER) + 
		sizeof(RGBQUAD) * (1<< cClrBits)); 

	// There is no RGBQUAD array for the 24-bit-per-pixel format. 

	else 
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
		sizeof(BITMAPINFOHEADER)); 

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
	if (cClrBits < 24) 
		pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB; 

	// Compute the number of bytes in the array of color 
	// indices and store the result in biSizeImage. 
	// For Windows NT, the width must be DWORD aligned unless 
	// the bitmap is RLE compressed. This example shows this. 
	// For Windows 95/98/Me, the width must be WORD aligned unless the 
	// bitmap is RLE compressed.
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
		* pbmi->bmiHeader.biHeight; 
	// Set biClrImportant to 0, indicating that all of the 
	// device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0; 
	return TRUE; 
} 

BOOL CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, 
				   HBITMAP hBMP, HDC hDC) 
{ 
	HANDLE hf;                 // file handle 
	BITMAPFILEHEADER hdr;       // bitmap file-header 
	PBITMAPINFOHEADER pbih;     // bitmap info-header 
	LPBYTE lpBits;              // memory pointer 
	DWORD dwTotal;              // total count of bytes 
	DWORD cb;                   // incremental count of bytes 
	BYTE *hp;                   // byte pointer 
	DWORD dwTmp; 

	pbih = (PBITMAPINFOHEADER) pbi; 
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits) 
		return FALSE;

	// Retrieve the color table (RGBQUAD array) and the bits 
	// (array of palette indices) from the DIB. 
	if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
		DIB_RGB_COLORS)) 
	{
		return FALSE;
	}

	// Create the .BMP file. 
	hf = CreateFile(pszFile, 
		GENERIC_READ | GENERIC_WRITE, 
		(DWORD) 0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 
	if (hf == INVALID_HANDLE_VALUE) 
		return FALSE;
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
	// Compute the size of the entire file. 
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof(RGBQUAD) + pbih->biSizeImage); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof (RGBQUAD); 

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
		(LPDWORD) &dwTmp,  NULL)) 
	{
		return FALSE;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
		+ pbih->biClrUsed * sizeof (RGBQUAD), 
		(LPDWORD) &dwTmp, ( NULL))) 
		return FALSE;

	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage; 
	hp = lpBits; 
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
		return FALSE;
	// Close the .BMP file. 
	if (!CloseHandle(hf)) 
		return FALSE;

	// Free memory. 
	GlobalFree((HGLOBAL)lpBits);

	return TRUE;
}
};