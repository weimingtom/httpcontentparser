// Rules_management_exe.cpp : WinMain µÄÊµÏÖ

#include "stdafx.h"
#include "resource.h"
#include "Rules_management_exe.h"
#include ".\globaldata.h"

CGlobalData g_globalData;

class CRules_management_exeModule : public CAtlExeModuleT< CRules_management_exeModule >
{
public :
	DECLARE_LIBID(LIBID_Rules_management_exeLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_RULES_MANAGEMENT_EXE, "{A1CB2A13-725A-4077-BA89-3388AC7F6701}")
};

CRules_management_exeModule _AtlModule;


//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

