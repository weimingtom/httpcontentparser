

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Jul 20 16:53:24 2008
 */
/* Compiler settings for .\FilterSetting.idl:
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

#ifndef __FilterSetting_h__
#define __FilterSetting_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGlobalChecker_FWD_DEFINED__
#define __IGlobalChecker_FWD_DEFINED__
typedef interface IGlobalChecker IGlobalChecker;
#endif 	/* __IGlobalChecker_FWD_DEFINED__ */


#ifndef __GlobalChecker_FWD_DEFINED__
#define __GlobalChecker_FWD_DEFINED__

#ifdef __cplusplus
typedef class GlobalChecker GlobalChecker;
#else
typedef struct GlobalChecker GlobalChecker;
#endif /* __cplusplus */

#endif 	/* __GlobalChecker_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IGlobalChecker_INTERFACE_DEFINED__
#define __IGlobalChecker_INTERFACE_DEFINED__

/* interface IGlobalChecker */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGlobalChecker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5C1696AA-6E3E-4B97-8B0C-FEF2A21FF50F")
    IGlobalChecker : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addBlackDNS( 
            /* [in] */ BSTR dns) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addWhiteDNS( 
            /* [in] */ BSTR dns) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE enableDNSCheck( 
            /* [in] */ VARIANT_BOOL enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeBlackDNS( 
            BSTR blackDNS) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeWhiteDNS( 
            BSTR whiteDNS) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGlobalCheckerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGlobalChecker * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGlobalChecker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGlobalChecker * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGlobalChecker * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGlobalChecker * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGlobalChecker * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGlobalChecker * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addBlackDNS )( 
            IGlobalChecker * This,
            /* [in] */ BSTR dns);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addWhiteDNS )( 
            IGlobalChecker * This,
            /* [in] */ BSTR dns);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *enableDNSCheck )( 
            IGlobalChecker * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeBlackDNS )( 
            IGlobalChecker * This,
            BSTR blackDNS);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeWhiteDNS )( 
            IGlobalChecker * This,
            BSTR whiteDNS);
        
        END_INTERFACE
    } IGlobalCheckerVtbl;

    interface IGlobalChecker
    {
        CONST_VTBL struct IGlobalCheckerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGlobalChecker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGlobalChecker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGlobalChecker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGlobalChecker_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGlobalChecker_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGlobalChecker_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGlobalChecker_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGlobalChecker_addBlackDNS(This,dns)	\
    (This)->lpVtbl -> addBlackDNS(This,dns)

#define IGlobalChecker_addWhiteDNS(This,dns)	\
    (This)->lpVtbl -> addWhiteDNS(This,dns)

#define IGlobalChecker_enableDNSCheck(This,enable)	\
    (This)->lpVtbl -> enableDNSCheck(This,enable)

#define IGlobalChecker_removeBlackDNS(This,blackDNS)	\
    (This)->lpVtbl -> removeBlackDNS(This,blackDNS)

#define IGlobalChecker_removeWhiteDNS(This,whiteDNS)	\
    (This)->lpVtbl -> removeWhiteDNS(This,whiteDNS)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGlobalChecker_addBlackDNS_Proxy( 
    IGlobalChecker * This,
    /* [in] */ BSTR dns);


void __RPC_STUB IGlobalChecker_addBlackDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGlobalChecker_addWhiteDNS_Proxy( 
    IGlobalChecker * This,
    /* [in] */ BSTR dns);


void __RPC_STUB IGlobalChecker_addWhiteDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGlobalChecker_enableDNSCheck_Proxy( 
    IGlobalChecker * This,
    /* [in] */ VARIANT_BOOL enable);


void __RPC_STUB IGlobalChecker_enableDNSCheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGlobalChecker_removeBlackDNS_Proxy( 
    IGlobalChecker * This,
    BSTR blackDNS);


void __RPC_STUB IGlobalChecker_removeBlackDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGlobalChecker_removeWhiteDNS_Proxy( 
    IGlobalChecker * This,
    BSTR whiteDNS);


void __RPC_STUB IGlobalChecker_removeWhiteDNS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGlobalChecker_INTERFACE_DEFINED__ */



#ifndef __FilterSettingLib_LIBRARY_DEFINED__
#define __FilterSettingLib_LIBRARY_DEFINED__

/* library FilterSettingLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FilterSettingLib;

EXTERN_C const CLSID CLSID_GlobalChecker;

#ifdef __cplusplus

class DECLSPEC_UUID("406FA387-8E48-4A60-B13B-30B7EB9E32F3")
GlobalChecker;
#endif
#endif /* __FilterSettingLib_LIBRARY_DEFINED__ */

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


