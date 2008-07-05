

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Jun 16 20:42:09 2008
 */
/* Compiler settings for .\RulesManagement.idl:
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

MIDL_DEFINE_GUID(IID, IID_IRulesSettings,0x1923DFB6,0x2FA8,0x469A,0xA3,0xB2,0xC4,0x94,0xA8,0xEE,0xA2,0x05);


MIDL_DEFINE_GUID(IID, IID_IRulesChecker,0x06EEABB5,0x577F,0x4D04,0x96,0x72,0xDF,0xF1,0x63,0x6A,0x64,0x54);


MIDL_DEFINE_GUID(IID, LIBID_RulesManagementLib,0x415ED9C8,0xF251,0x47EC,0xB5,0xE8,0x8B,0xE5,0x16,0xED,0x11,0xF8);


MIDL_DEFINE_GUID(CLSID, CLSID_RulesSettings,0x510EB138,0x2FF8,0x4AA3,0x89,0xFD,0x81,0x67,0xA8,0xD0,0xDE,0xA4);


MIDL_DEFINE_GUID(CLSID, CLSID_RulesChecker,0x57DBEF45,0x71BC,0x4E84,0x84,0x74,0x99,0xF0,0x22,0x3E,0xFF,0x9A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

