

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Jul 08 22:40:50 2008
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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Rules_management_exe_h__
#define __Rules_management_exe_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IExeRulesChecker_FWD_DEFINED__
#define __IExeRulesChecker_FWD_DEFINED__
typedef interface IExeRulesChecker IExeRulesChecker;
#endif 	/* __IExeRulesChecker_FWD_DEFINED__ */


#ifndef __IExeRulesSetting_FWD_DEFINED__
#define __IExeRulesSetting_FWD_DEFINED__
typedef interface IExeRulesSetting IExeRulesSetting;
#endif 	/* __IExeRulesSetting_FWD_DEFINED__ */


#ifndef __ExeRulesChecker_FWD_DEFINED__
#define __ExeRulesChecker_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExeRulesChecker ExeRulesChecker;
#else
typedef struct ExeRulesChecker ExeRulesChecker;
#endif /* __cplusplus */

#endif 	/* __ExeRulesChecker_FWD_DEFINED__ */


#ifndef __ExeRulesSetting_FWD_DEFINED__
#define __ExeRulesSetting_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExeRulesSetting ExeRulesSetting;
#else
typedef struct ExeRulesSetting ExeRulesSetting;
#endif /* __cplusplus */

#endif 	/* __ExeRulesSetting_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IExeRulesChecker_INTERFACE_DEFINED__
#define __IExeRulesChecker_INTERFACE_DEFINED__

/* interface IExeRulesChecker */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IExeRulesChecker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7DA12468-B290-42A0-8F98-3AB211142AA1")
    IExeRulesChecker : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE checkIp( 
            /* [in] */ ULONG ip,
            /* [retval][out] */ VARIANT_BOOL *bFiltered) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExeRulesCheckerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExeRulesChecker * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExeRulesChecker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExeRulesChecker * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IExeRulesChecker * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IExeRulesChecker * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IExeRulesChecker * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IExeRulesChecker * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *checkIp )( 
            IExeRulesChecker * This,
            /* [in] */ ULONG ip,
            /* [retval][out] */ VARIANT_BOOL *bFiltered);
        
        END_INTERFACE
    } IExeRulesCheckerVtbl;

    interface IExeRulesChecker
    {
        CONST_VTBL struct IExeRulesCheckerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExeRulesChecker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExeRulesChecker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExeRulesChecker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExeRulesChecker_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExeRulesChecker_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExeRulesChecker_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExeRulesChecker_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExeRulesChecker_checkIp(This,ip,bFiltered)	\
    (This)->lpVtbl -> checkIp(This,ip,bFiltered)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExeRulesChecker_checkIp_Proxy( 
    IExeRulesChecker * This,
    /* [in] */ ULONG ip,
    /* [retval][out] */ VARIANT_BOOL *bFiltered);


void __RPC_STUB IExeRulesChecker_checkIp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExeRulesChecker_INTERFACE_DEFINED__ */


#ifndef __IExeRulesSetting_INTERFACE_DEFINED__
#define __IExeRulesSetting_INTERFACE_DEFINED__

/* interface IExeRulesSetting */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IExeRulesSetting;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BE5426ED-C2D5-4C51-9981-A3AA19383FAB")
    IExeRulesSetting : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addFiltederDNS( 
            /* [in] */ BSTR dns) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE enableIpCheck( 
            /* [in] */ VARIANT_BOOL enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeFilteredDNS( 
            BSTR dns) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExeRulesSettingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExeRulesSetting * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExeRulesSetting * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExeRulesSetting * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IExeRulesSetting * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IExeRulesSetting * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IExeRulesSetting * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IExeRulesSetting * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *initialize )( 
            IExeRulesSetting * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addFiltederDNS )( 
            IExeRulesSetting * This,
            /* [in] */ BSTR dns);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *enableIpCheck )( 
            IExeRulesSetting * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeFilteredDNS )( 
            IExeRulesSetting * This,
            BSTR dns);
        
        END_INTERFACE
    } IExeRulesSettingVtbl;

    interface IExeRulesSetting
    {
        CONST_VTBL struct IExeRulesSettingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExeRulesSetting_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExeRulesSetting_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExeRulesSetting_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExeRulesSetting_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExeRulesSetting_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExeRulesSetting_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExeRulesSetting_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExeRulesSetting_initialize(This)	\
    (This)->lpVtbl -> initialize(This)

#define IExeRulesSetting_addFiltederDNS(This,dns)	\
    (This)->lpVtbl -> addFiltederDNS(This,dns)

#define IExeRulesSetting_enableIpCheck(This,enable)	\
    (This)->lpVtbl -> enableIpCheck(This,enable)

#define IExeRulesSetting_removeFilteredDNS(This,dns)	\
    (This)->lpVtbl -> removeFilteredDNS(This,dns)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExeRulesSetting_initialize_Proxy( 
    IExeRulesSetting * This);


void __RPC_STUB IExeRulesSetting_initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExeRulesSetting_addFiltederDNS_Proxy( 
    IExeRulesSetting * This,
    /* [in] */ BSTR dns);


void __RPC_STUB IExeRulesSetting_addFiltederDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExeRulesSetting_enableIpCheck_Proxy( 
    IExeRulesSetting * This,
    /* [in] */ VARIANT_BOOL enable);


void __RPC_STUB IExeRulesSetting_enableIpCheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExeRulesSetting_removeFilteredDNS_Proxy( 
    IExeRulesSetting * This,
    BSTR dns);


void __RPC_STUB IExeRulesSetting_removeFilteredDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExeRulesSetting_INTERFACE_DEFINED__ */



#ifndef __Rules_management_exeLib_LIBRARY_DEFINED__
#define __Rules_management_exeLib_LIBRARY_DEFINED__

/* library Rules_management_exeLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_Rules_management_exeLib;

EXTERN_C const CLSID CLSID_ExeRulesChecker;

#ifdef __cplusplus

class DECLSPEC_UUID("A7A82CE1-26DB-4B36-B0D7-ECFA04AEB03E")
ExeRulesChecker;
#endif

EXTERN_C const CLSID CLSID_ExeRulesSetting;

#ifdef __cplusplus

class DECLSPEC_UUID("F907B189-7F80-4E95-B3AB-22E077ADB495")
ExeRulesSetting;
#endif
#endif /* __Rules_management_exeLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


