

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Jul 13 14:21:07 2008
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

#ifndef __RulesHolder_h__
#define __RulesHolder_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRulesChecker_FWD_DEFINED__
#define __IRulesChecker_FWD_DEFINED__
typedef interface IRulesChecker IRulesChecker;
#endif 	/* __IRulesChecker_FWD_DEFINED__ */


#ifndef __IRulesSetting_FWD_DEFINED__
#define __IRulesSetting_FWD_DEFINED__
typedef interface IRulesSetting IRulesSetting;
#endif 	/* __IRulesSetting_FWD_DEFINED__ */


#ifndef __RulesChecker_FWD_DEFINED__
#define __RulesChecker_FWD_DEFINED__

#ifdef __cplusplus
typedef class RulesChecker RulesChecker;
#else
typedef struct RulesChecker RulesChecker;
#endif /* __cplusplus */

#endif 	/* __RulesChecker_FWD_DEFINED__ */


#ifndef __RulesSetting_FWD_DEFINED__
#define __RulesSetting_FWD_DEFINED__

#ifdef __cplusplus
typedef class RulesSetting RulesSetting;
#else
typedef struct RulesSetting RulesSetting;
#endif /* __cplusplus */

#endif 	/* __RulesSetting_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IRulesChecker_INTERFACE_DEFINED__
#define __IRulesChecker_INTERFACE_DEFINED__

/* interface IRulesChecker */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRulesChecker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6ADCEA63-C141-425B-8C89-70AF3672D3BF")
    IRulesChecker : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE checkIp( 
            /* [in] */ ULONG ip,
            /* [retval][out] */ VARIANT_BOOL *bFiltered) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRulesCheckerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRulesChecker * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRulesChecker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRulesChecker * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRulesChecker * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRulesChecker * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRulesChecker * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRulesChecker * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *checkIp )( 
            IRulesChecker * This,
            /* [in] */ ULONG ip,
            /* [retval][out] */ VARIANT_BOOL *bFiltered);
        
        END_INTERFACE
    } IRulesCheckerVtbl;

    interface IRulesChecker
    {
        CONST_VTBL struct IRulesCheckerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRulesChecker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRulesChecker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRulesChecker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRulesChecker_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRulesChecker_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRulesChecker_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRulesChecker_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRulesChecker_checkIp(This,ip,bFiltered)	\
    (This)->lpVtbl -> checkIp(This,ip,bFiltered)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesChecker_checkIp_Proxy( 
    IRulesChecker * This,
    /* [in] */ ULONG ip,
    /* [retval][out] */ VARIANT_BOOL *bFiltered);


void __RPC_STUB IRulesChecker_checkIp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRulesChecker_INTERFACE_DEFINED__ */


#ifndef __IRulesSetting_INTERFACE_DEFINED__
#define __IRulesSetting_INTERFACE_DEFINED__

/* interface IRulesSetting */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRulesSetting;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F30C083-6DFA-4CA3-AD9D-D24EE5580662")
    IRulesSetting : public IDispatch
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

    typedef struct IRulesSettingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRulesSetting * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRulesSetting * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRulesSetting * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRulesSetting * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRulesSetting * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRulesSetting * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRulesSetting * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *initialize )( 
            IRulesSetting * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addFiltederDNS )( 
            IRulesSetting * This,
            /* [in] */ BSTR dns);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *enableIpCheck )( 
            IRulesSetting * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeFilteredDNS )( 
            IRulesSetting * This,
            BSTR dns);
        
        END_INTERFACE
    } IRulesSettingVtbl;

    interface IRulesSetting
    {
        CONST_VTBL struct IRulesSettingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRulesSetting_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRulesSetting_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRulesSetting_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRulesSetting_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRulesSetting_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRulesSetting_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRulesSetting_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRulesSetting_initialize(This)	\
    (This)->lpVtbl -> initialize(This)

#define IRulesSetting_addFiltederDNS(This,dns)	\
    (This)->lpVtbl -> addFiltederDNS(This,dns)

#define IRulesSetting_enableIpCheck(This,enable)	\
    (This)->lpVtbl -> enableIpCheck(This,enable)

#define IRulesSetting_removeFilteredDNS(This,dns)	\
    (This)->lpVtbl -> removeFilteredDNS(This,dns)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSetting_initialize_Proxy( 
    IRulesSetting * This);


void __RPC_STUB IRulesSetting_initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSetting_addFiltederDNS_Proxy( 
    IRulesSetting * This,
    /* [in] */ BSTR dns);


void __RPC_STUB IRulesSetting_addFiltederDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSetting_enableIpCheck_Proxy( 
    IRulesSetting * This,
    /* [in] */ VARIANT_BOOL enable);


void __RPC_STUB IRulesSetting_enableIpCheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSetting_removeFilteredDNS_Proxy( 
    IRulesSetting * This,
    BSTR dns);


void __RPC_STUB IRulesSetting_removeFilteredDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRulesSetting_INTERFACE_DEFINED__ */



#ifndef __RulesHolderLib_LIBRARY_DEFINED__
#define __RulesHolderLib_LIBRARY_DEFINED__

/* library RulesHolderLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RulesHolderLib;

EXTERN_C const CLSID CLSID_RulesChecker;

#ifdef __cplusplus

class DECLSPEC_UUID("C7425D4F-F6D3-4F9C-A0BB-3297325A45A4")
RulesChecker;
#endif

EXTERN_C const CLSID CLSID_RulesSetting;

#ifdef __cplusplus

class DECLSPEC_UUID("A31778F3-3300-4327-B4C4-8B24B55504E3")
RulesSetting;
#endif
#endif /* __RulesHolderLib_LIBRARY_DEFINED__ */

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


