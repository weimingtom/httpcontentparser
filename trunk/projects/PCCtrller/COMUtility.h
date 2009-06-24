#ifndef _PCCTRL_COMUTILITY_H__
#define _PCCTRL_COMUTILITY_H__

BOOL ValidatePassword(LPCTSTR password);

BOOL IsRunInEnterModel() ;
BOOL IsRuninParentModel() ;
BOOL TRYEndEyecare(LPCTSTR password);
LONG GetEyecareLeftSeconds() ;

const int UNKNOW_MODEL = -1;
const int EYECARE_MODEL = 0;
const int LOCKPC_MODEL  = 1;

#endif  // _PCCTRL_COMUTILITY_H__