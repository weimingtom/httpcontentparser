

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Jul 13 18:07:58 2008
 */
/* Compiler settings for .\Rules_management_exe.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IExeRulesChecker,0x7DA12468,0xB290,0x42A0,0x8F,0x98,0x3A,0xB2,0x11,0x14,0x2A,0xA1);


MIDL_DEFINE_GUID(IID, IID_IExeRulesSetting,0xBE5426ED,0xC2D5,0x4C51,0x99,0x81,0xA3,0xAA,0x19,0x38,0x3F,0xAB);


MIDL_DEFINE_GUID(IID, LIBID_Rules_management_exeLib,0x1D97C684,0x6D93,0x4F41,0xB0,0x23,0xAB,0x4A,0x98,0x8B,0x49,0x05);


MIDL_DEFINE_GUID(CLSID, CLSID_ExeRulesChecker,0xA7A82CE1,0x26DB,0x4B36,0xB0,0xD7,0xEC,0xFA,0x04,0xAE,0xB0,0x3E);


MIDL_DEFINE_GUID(CLSID, CLSID_ExeRulesSetting,0xF907B189,0x7F80,0x4E95,0xB3,0xAB,0x22,0xE0,0x77,0xAD,0xB4,0x95);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

