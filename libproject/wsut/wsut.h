#ifndef _WSUT_H__
#define _WSUT_H__

#ifdef WSUT_EXPORTS
#define WSUT_API __declspec(dllexport)
#else
#define WSUT_API __declspec(dllimport)
#endif

WSUT_API int __stdcall  CheckProgram(const char * status);
WSUT_API int __stdcall  CheckStatus(const char * status);
WSUT_API int __stdcall  CallUtility(const char * status);

#endif  // 