// RulesHolder.cpp : WinMain µÄÊµÏÖ

#include "stdafx.h"
#include "resource.h"
#include "RulesHolder.h"
#include ".\globaldata.h"

CGlobalData g_globalData;

class CRulesHolderModule : public CAtlExeModuleT< CRulesHolderModule >
{
public :
	DECLARE_LIBID(LIBID_RulesHolderLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_RULESHOLDER, "{F46D7A2F-7F21-49D8-8CB5-601B4767AB5F}")
};

CRulesHolderModule _AtlModule;


//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

