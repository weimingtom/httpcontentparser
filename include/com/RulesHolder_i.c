

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Jul 06 01:05:35 2008
 */
/* Compiler settings for .\RulesHolder.idl:
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

MIDL_DEFINE_GUID(IID, IID_IRulesChecker,0x6ADCEA63,0xC141,0x425B,0x8C,0x89,0x70,0xAF,0x36,0x72,0xD3,0xBF);


MIDL_DEFINE_GUID(IID, IID_IRulesSetting,0x8F30C083,0x6DFA,0x4CA3,0xAD,0x9D,0xD2,0x4E,0xE5,0x58,0x06,0x62);


MIDL_DEFINE_GUID(IID, LIBID_RulesHolderLib,0x8E167E68,0xFAEF,0x48D3,0x87,0xEE,0x44,0xCD,0xAC,0x74,0x08,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_RulesChecker,0xC7425D4F,0xF6D3,0x4F9C,0xA0,0xBB,0x32,0x97,0x32,0x5A,0x45,0xA4);


MIDL_DEFINE_GUID(CLSID, CLSID_RulesSetting,0xA31778F3,0x3300,0x4327,0xB4,0xC4,0x8B,0x24,0xB5,0x55,0x04,0xE3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

