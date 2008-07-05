

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __RulesManagement_h__
#define __RulesManagement_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRulesSettings_FWD_DEFINED__
#define __IRulesSettings_FWD_DEFINED__
typedef interface IRulesSettings IRulesSettings;
#endif 	/* __IRulesSettings_FWD_DEFINED__ */


#ifndef __IRulesChecker_FWD_DEFINED__
#define __IRulesChecker_FWD_DEFINED__
typedef interface IRulesChecker IRulesChecker;
#endif 	/* __IRulesChecker_FWD_DEFINED__ */


#ifndef __RulesSettings_FWD_DEFINED__
#define __RulesSettings_FWD_DEFINED__

#ifdef __cplusplus
typedef class RulesSettings RulesSettings;
#else
typedef struct RulesSettings RulesSettings;
#endif /* __cplusplus */

#endif 	/* __RulesSettings_FWD_DEFINED__ */


#ifndef __RulesChecker_FWD_DEFINED__
#define __RulesChecker_FWD_DEFINED__

#ifdef __cplusplus
typedef class RulesChecker RulesChecker;
#else
typedef struct RulesChecker RulesChecker;
#endif /* __cplusplus */

#endif 	/* __RulesChecker_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IRulesSettings_INTERFACE_DEFINED__
#define __IRulesSettings_INTERFACE_DEFINED__

/* interface IRulesSettings */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRulesSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1923DFB6-2FA8-469A-A3B2-C494A8EEA205")
    IRulesSettings : public IDispatch
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

    typedef struct IRulesSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRulesSettings * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRulesSettings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRulesSettings * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRulesSettings * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRulesSettings * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRulesSettings * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRulesSettings * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *initialize )( 
            IRulesSettings * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addFiltederDNS )( 
            IRulesSettings * This,
            /* [in] */ BSTR dns);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *enableIpCheck )( 
            IRulesSettings * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeFilteredDNS )( 
            IRulesSettings * This,
            BSTR dns);
        
        END_INTERFACE
    } IRulesSettingsVtbl;

    interface IRulesSettings
    {
        CONST_VTBL struct IRulesSettingsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRulesSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRulesSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRulesSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRulesSettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRulesSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRulesSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRulesSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRulesSettings_initialize(This)	\
    (This)->lpVtbl -> initialize(This)

#define IRulesSettings_addFiltederDNS(This,dns)	\
    (This)->lpVtbl -> addFiltederDNS(This,dns)

#define IRulesSettings_enableIpCheck(This,enable)	\
    (This)->lpVtbl -> enableIpCheck(This,enable)

#define IRulesSettings_removeFilteredDNS(This,dns)	\
    (This)->lpVtbl -> removeFilteredDNS(This,dns)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSettings_initialize_Proxy( 
    IRulesSettings * This);


void __RPC_STUB IRulesSettings_initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSettings_addFiltederDNS_Proxy( 
    IRulesSettings * This,
    /* [in] */ BSTR dns);


void __RPC_STUB IRulesSettings_addFiltederDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSettings_enableIpCheck_Proxy( 
    IRulesSettings * This,
    /* [in] */ VARIANT_BOOL enable);


void __RPC_STUB IRulesSettings_enableIpCheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRulesSettings_removeFilteredDNS_Proxy( 
    IRulesSettings * This,
    BSTR dns);


void __RPC_STUB IRulesSettings_removeFilteredDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRulesSettings_INTERFACE_DEFINED__ */


#ifndef __IRulesChecker_INTERFACE_DEFINED__
#define __IRulesChecker_INTERFACE_DEFINED__

/* interface IRulesChecker */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRulesChecker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("06EEABB5-577F-4D04-9672-DFF1636A6454")
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



#ifndef __RulesManagementLib_LIBRARY_DEFINED__
#define __RulesManagementLib_LIBRARY_DEFINED__

/* library RulesManagementLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RulesManagementLib;

EXTERN_C const CLSID CLSID_RulesSettings;

#ifdef __cplusplus

class DECLSPEC_UUID("510EB138-2FF8-4AA3-89FD-8167A8D0DEA4")
RulesSettings;
#endif

EXTERN_C const CLSID CLSID_RulesChecker;

#ifdef __cplusplus

class DECLSPEC_UUID("57DBEF45-71BC-4E84-8474-99F0223EFF9A")
RulesChecker;
#endif
#endif /* __RulesManagementLib_LIBRARY_DEFINED__ */

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


