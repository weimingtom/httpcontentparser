

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Mar 09 10:05:33 2009
 */
/* Compiler settings for .\exts.idl:
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

#ifndef __exts_h__
#define __exts_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAppLaunchFilter_FWD_DEFINED__
#define __IAppLaunchFilter_FWD_DEFINED__
typedef interface IAppLaunchFilter IAppLaunchFilter;
#endif 	/* __IAppLaunchFilter_FWD_DEFINED__ */


#ifndef __AppLaunchFilter_FWD_DEFINED__
#define __AppLaunchFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class AppLaunchFilter AppLaunchFilter;
#else
typedef struct AppLaunchFilter AppLaunchFilter;
#endif /* __cplusplus */

#endif 	/* __AppLaunchFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IAppLaunchFilter_INTERFACE_DEFINED__
#define __IAppLaunchFilter_INTERFACE_DEFINED__

/* interface IAppLaunchFilter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAppLaunchFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FB90EC3-8BE4-4ED3-A103-9B1070C84C7A")
    IAppLaunchFilter : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAppLaunchFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAppLaunchFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAppLaunchFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAppLaunchFilter * This);
        
        END_INTERFACE
    } IAppLaunchFilterVtbl;

    interface IAppLaunchFilter
    {
        CONST_VTBL struct IAppLaunchFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAppLaunchFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAppLaunchFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAppLaunchFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAppLaunchFilter_INTERFACE_DEFINED__ */



#ifndef __extsLib_LIBRARY_DEFINED__
#define __extsLib_LIBRARY_DEFINED__

/* library extsLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_extsLib;

EXTERN_C const CLSID CLSID_AppLaunchFilter;

#ifdef __cplusplus

class DECLSPEC_UUID("B0C0589E-9692-44E0-B2F1-378BE31B61C1")
AppLaunchFilter;
#endif
#endif /* __extsLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


