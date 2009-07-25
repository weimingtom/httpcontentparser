#ifndef _VISUALSTYLE_XP_H_
#define _VISUALSTYLE_XP_H_

#pragma once

#include <uxtheme.h>
#include <tmschema.h>

class CVisualStylesXP
{
private:
	HMODULE m_hThemeDll;
	void* GetProc(LPCSTR szProc, void* pfnFail);

	typedef HTHEME(__stdcall *PFNOPENTHEMEDATA)(HWND hwnd, LPCWSTR pszClassList);
	static HTHEME OpenThemeDataFail(HWND , LPCWSTR )
	{return NULL;}

	typedef HRESULT(__stdcall *PFNCLOSETHEMEDATA)(HTHEME hTheme);
	static HRESULT CloseThemeDataFail(HTHEME)
	{return E_FAIL;}

	typedef HRESULT(__stdcall *PFNDRAWTHEMEBACKGROUND)(HTHEME hTheme, HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pRect,  const RECT *pClipRect);
	static HRESULT DrawThemeBackgroundFail(HTHEME, HDC, INT_PTR, INT_PTR, const RECT *, const RECT *)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMETEXT)(HTHEME hTheme, HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, LPCWSTR pszText, INT_PTR iCharCount, DWORD dwTextFlags, 
		DWORD dwTextFlags2, const RECT *pRect);
	static HRESULT DrawThemeTextFail(HTHEME, HDC, INT_PTR, INT_PTR, LPCWSTR, INT_PTR, DWORD, DWORD, const RECT*)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDCONTENTRECT)(HTHEME hTheme,  HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect);
	static HRESULT GetThemeBackgroundContentRectFail(HTHEME hTheme,  HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect)
	{return E_FAIL;}
	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDEXTENT)(HTHEME hTheme,  HDC hdc,
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pContentRect, 
		RECT *pExtentRect);
	static HRESULT GetThemeBackgroundExtentFail(HTHEME hTheme,  HDC hdc,
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pContentRect, 
		RECT *pExtentRect)
	{return E_FAIL;}

	typedef HRESULT(__stdcall *PFNGETTHEMEPARTSIZE)(HTHEME hTheme, HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId, RECT * pRect, enum THEMESIZE eSize,  SIZE *psz);
	static HRESULT GetThemePartSizeFail(HTHEME, HDC, INT_PTR, INT_PTR, RECT *, enum THEMESIZE, SIZE *)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMETEXTEXTENT)(HTHEME hTheme, HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId, LPCWSTR pszText, INT_PTR iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect);
	static HRESULT GetThemeTextExtentFail(HTHEME hTheme, HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId, LPCWSTR pszText, INT_PTR iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMETEXTMETRICS)(HTHEME hTheme,  HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId,  TEXTMETRIC* ptm);
	static HRESULT GetThemeTextMetricsFail(HTHEME hTheme,  HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId,  TEXTMETRIC* ptm)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDREGION)(HTHEME hTheme,  HDC hdc,  
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pRect,  HRGN *pRegion);
	static HRESULT GetThemeBackgroundRegionFail(HTHEME hTheme,  HDC hdc,  
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pRect,  HRGN *pRegion)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNHITTESTTHEMEBACKGROUND)(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode);
	static HRESULT HitTestThemeBackgroundFail(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEEDGE)(HTHEME hTheme, HDC hdc, INT_PTR iPartId, INT_PTR iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect);
	static HRESULT DrawThemeEdgeFail(HTHEME hTheme, HDC hdc, INT_PTR iPartId, INT_PTR iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEICON)(HTHEME hTheme, HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, const RECT *pRect, HIMAGELIST himl, INT_PTR iImageIndex);
	static HRESULT DrawThemeIconFail(HTHEME hTheme, HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, const RECT *pRect, HIMAGELIST himl, INT_PTR iImageIndex)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEPARTDEFINED)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId);
	static BOOL IsThemePartDefinedFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId)
	{return FALSE;}

	typedef BOOL (__stdcall *PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT)(HTHEME hTheme, 
		INT_PTR iPartId, INT_PTR iStateId);
	static BOOL IsThemeBackgroundPartiallyTransparentFail(HTHEME hTheme, 
		INT_PTR iPartId, INT_PTR iStateId)
	{return FALSE;}

	typedef HRESULT (__stdcall *PFNGETTHEMECOLOR)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  COLORREF *pColor);
	static HRESULT GetThemeColorFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  COLORREF *pColor)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEMETRIC)(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal);
	static HRESULT GetThemeMetricFail(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESTRING)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LPWSTR pszBuff, INT_PTR cchMaxBuffChars);
	static HRESULT GetThemeStringFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LPWSTR pszBuff, INT_PTR cchMaxBuffChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBOOL)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  BOOL *pfVal);
	static HRESULT GetThemeBoolFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  BOOL *pfVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEINT)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal);
	static HRESULT GetThemeIntFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEENUMVALUE)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal);
	static HRESULT GetThemeEnumValueFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEPOSITION)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  POINT *pPoint);
	static HRESULT GetThemePositionFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  POINT *pPoint)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEFONT)(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LOGFONT *pFont);
	static HRESULT GetThemeFontFail(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LOGFONT *pFont)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMERECT)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  RECT *pRect);
	static HRESULT GetThemeRectFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  RECT *pRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEMARGINS)(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  RECT *prc,  MARGINS *pMargins);
	static HRESULT GetThemeMarginsFail(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  RECT *prc,  MARGINS *pMargins)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEINTLIST)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INTLIST *pIntList);
	static HRESULT GetThemeIntListFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INTLIST *pIntList)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEPROPERTYORIGIN)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  enum PROPERTYORIGIN *pOrigin);
	static HRESULT GetThemePropertyOriginFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  enum PROPERTYORIGIN *pOrigin)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNSETWINDOWTHEME)(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList);
	static HRESULT SetWindowThemeFail(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEFILENAME)(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LPWSTR pszThemeFileName, INT_PTR cchMaxBuffChars);
	static HRESULT GetThemeFilenameFail(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LPWSTR pszThemeFileName, INT_PTR cchMaxBuffChars)
	{return E_FAIL;}

	typedef COLORREF (__stdcall *PFNGETTHEMESYSCOLOR)(HTHEME hTheme, INT_PTR iColorId);
	static COLORREF GetThemeSysColorFail(HTHEME hTheme, INT_PTR iColorId)
	{return RGB(255,255,255);}

	typedef HBRUSH (__stdcall *PFNGETTHEMESYSCOLORBRUSH)(HTHEME hTheme, INT_PTR iColorId);
	static HBRUSH GetThemeSysColorBrushFail(HTHEME hTheme, INT_PTR iColorId)
	{return NULL;}

	typedef BOOL (__stdcall *PFNGETTHEMESYSBOOL)(HTHEME hTheme, INT_PTR iBoolId);
	static BOOL GetThemeSysBoolFail(HTHEME hTheme, INT_PTR iBoolId)
	{return FALSE;}

	typedef INT_PTR (__stdcall *PFNGETTHEMESYSSIZE)(HTHEME hTheme, INT_PTR iSizeId);
	static INT_PTR GetThemeSysSizeFail(HTHEME hTheme, INT_PTR iSizeId)
	{return 0;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSFONT)(HTHEME hTheme, INT_PTR iFontId,  LOGFONT *plf);
	static HRESULT GetThemeSysFontFail(HTHEME hTheme, INT_PTR iFontId,  LOGFONT *plf)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSSTRING)(HTHEME hTheme, INT_PTR iStringId, 
		LPWSTR pszStringBuff, INT_PTR cchMaxStringChars);
	static HRESULT GetThemeSysStringFail(HTHEME hTheme, INT_PTR iStringId, 
		LPWSTR pszStringBuff, INT_PTR cchMaxStringChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSINT)(HTHEME hTheme, INT_PTR iIntId, INT_PTR *piValue);
	static HRESULT GetThemeSysIntFail(HTHEME hTheme, INT_PTR iIntId, INT_PTR *piValue)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEACTIVE)();
	static BOOL IsThemeActiveFail()
	{return FALSE;}

	typedef BOOL(__stdcall *PFNISAPPTHEMED)();
	static BOOL IsAppThemedFail()
	{return FALSE;}

	typedef HTHEME (__stdcall *PFNGETWINDOWTHEME)(HWND hwnd);
	static HTHEME GetWindowThemeFail(HWND hwnd)
	{return NULL;}

	typedef HRESULT (__stdcall *PFNENABLETHEMEDIALOGTEXTURE)(HWND hwnd, DWORD dwFlags);
	static HRESULT EnableThemeDialogTextureFail(HWND hwnd, DWORD dwFlags)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEDIALOGTEXTUREENABLED)(HWND hwnd);
	static BOOL IsThemeDialogTextureEnabledFail(HWND hwnd)
	{return FALSE;}

	typedef DWORD (__stdcall *PFNGETTHEMEAPPPROPERTIES)();
	static DWORD GetThemeAppPropertiesFail()
	{return 0;}

	typedef void (__stdcall *PFNSETTHEMEAPPPROPERTIES)(DWORD dwFlags);
	static void SetThemeAppPropertiesFail(DWORD dwFlags)
	{return;}

	typedef HRESULT (__stdcall *PFNGETCURRENTTHEMENAME)(
		LPWSTR pszThemeFileName, INT_PTR cchMaxNameChars, 
		LPWSTR pszColorBuff, INT_PTR cchMaxColorChars,
		LPWSTR pszSizeBuff, INT_PTR cchMaxSizeChars);
	static HRESULT GetCurrentThemeNameFail(
		LPWSTR pszThemeFileName, INT_PTR cchMaxNameChars, 
		LPWSTR pszColorBuff, INT_PTR cchMaxColorChars,
		LPWSTR pszSizeBuff, INT_PTR cchMaxSizeChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEDOCUMENTATIONPROPERTY)(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, INT_PTR cchMaxValChars);
	static HRESULT GetThemeDocumentationPropertyFail(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, INT_PTR cchMaxValChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEPARENTBACKGROUND)(HWND hwnd, HDC hdc,  RECT* prc);
	static HRESULT DrawThemeParentBackgroundFail(HWND hwnd, HDC hdc,  RECT* prc)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNENABLETHEMING)(BOOL fEnable);
	static HRESULT EnableThemingFail(BOOL fEnable)
	{return E_FAIL;}
public:
	HTHEME OpenThemeData(HWND hwnd, LPCWSTR pszClassList);
	HRESULT CloseThemeData(HTHEME hTheme);
	HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pRect, const RECT *pClipRect);
	HRESULT DrawThemeText(HTHEME hTheme, HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, LPCWSTR pszText, INT_PTR iCharCount, DWORD dwTextFlags, 
		DWORD dwTextFlags2, const RECT *pRect);
	HRESULT GetThemeBackgroundContentRect(HTHEME hTheme,  HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect);
	HRESULT GetThemeBackgroundExtent(HTHEME hTheme,  HDC hdc,
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pContentRect, 
		RECT *pExtentRect);
	HRESULT GetThemePartSize(HTHEME hTheme, HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId, RECT * pRect, enum THEMESIZE eSize, SIZE *psz);
	HRESULT GetThemeTextExtent(HTHEME hTheme, HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId, LPCWSTR pszText, INT_PTR iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect);
	HRESULT GetThemeTextMetrics(HTHEME hTheme,  HDC hdc, 
		INT_PTR iPartId, INT_PTR iStateId,  TEXTMETRIC* ptm);
	HRESULT GetThemeBackgroundRegion(HTHEME hTheme,  HDC hdc,  
		INT_PTR iPartId, INT_PTR iStateId, const RECT *pRect,  HRGN *pRegion);
	HRESULT HitTestThemeBackground(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode);
	HRESULT DrawThemeEdge(HTHEME hTheme, HDC hdc, INT_PTR iPartId, INT_PTR iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect);
	HRESULT DrawThemeIcon(HTHEME hTheme, HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, const RECT *pRect, HIMAGELIST himl, INT_PTR iImageIndex);
	BOOL IsThemePartDefined(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId);
	BOOL IsThemeBackgroundPartiallyTransparent(HTHEME hTheme, 
		INT_PTR iPartId, INT_PTR iStateId);
	HRESULT GetThemeColor(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  COLORREF *pColor);
	HRESULT GetThemeMetric(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal);
	HRESULT GetThemeString(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LPWSTR pszBuff, INT_PTR cchMaxBuffChars);
	HRESULT GetThemeBool(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  BOOL *pfVal);
	HRESULT GetThemeInt(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal);
	HRESULT GetThemeEnumValue(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INT_PTR *piVal);
	HRESULT GetThemePosition(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  POINT *pPoint);
	HRESULT GetThemeFont(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LOGFONT *pFont);
	HRESULT GetThemeRect(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  RECT *pRect);
	HRESULT GetThemeMargins(HTHEME hTheme,  HDC hdc, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  RECT *prc,  MARGINS *pMargins);
	HRESULT GetThemeIntList(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  INTLIST *pIntList);
	HRESULT GetThemePropertyOrigin(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  enum PROPERTYORIGIN *pOrigin);
	HRESULT SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList);
	HRESULT GetThemeFilename(HTHEME hTheme, INT_PTR iPartId, 
		INT_PTR iStateId, INT_PTR iPropId,  LPWSTR pszThemeFileName, INT_PTR cchMaxBuffChars);
	COLORREF GetThemeSysColor(HTHEME hTheme, INT_PTR iColorId);
	HBRUSH GetThemeSysColorBrush(HTHEME hTheme, INT_PTR iColorId);
	BOOL GetThemeSysBool(HTHEME hTheme, INT_PTR iBoolId);
	INT_PTR GetThemeSysSize(HTHEME hTheme, INT_PTR iSizeId);
	HRESULT GetThemeSysFont(HTHEME hTheme, INT_PTR iFontId,  LOGFONT *plf);
	HRESULT GetThemeSysString(HTHEME hTheme, INT_PTR iStringId, 
		LPWSTR pszStringBuff, INT_PTR cchMaxStringChars);
	HRESULT GetThemeSysInt(HTHEME hTheme, INT_PTR iIntId, INT_PTR *piValue);
	BOOL IsThemeActive();
	BOOL IsAppThemed();	
	HTHEME GetWindowTheme(HWND hwnd);
	HRESULT EnableThemeDialogTexture(HWND hwnd, DWORD dwFlags);
	BOOL IsThemeDialogTextureEnabled(HWND hwnd);
	DWORD GetThemeAppProperties();
	void SetThemeAppProperties(DWORD dwFlags);
	HRESULT GetCurrentThemeName(
		LPWSTR pszThemeFileName, INT_PTR cchMaxNameChars, 
		LPWSTR pszColorBuff, INT_PTR cchMaxColorChars,
		LPWSTR pszSizeBuff, INT_PTR cchMaxSizeChars);
	HRESULT GetThemeDocumentationProperty(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, INT_PTR cchMaxValChars);
	HRESULT DrawThemeParentBackground(HWND hwnd, HDC hdc,  RECT* prc);
	HRESULT EnableTheming(BOOL fEnable);
public:
	CVisualStylesXP(void);
	~CVisualStylesXP(void);
};

extern CVisualStylesXP g_xpStyle;

#endif