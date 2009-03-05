#ifndef _COM_RESULT_VALUE_H__
#define _COM_RESULT_VALUE_H__

#define SELF_COM_FAILED					1	
#define SELF_COM_SUCCEED				0

inline  bool SeflComReturnValueSucc(DWORD hr) {
	if (hr != 0) {
		return false;
	} else {
		return true;
	}
}

#endif  // _COM_RESULT_VALUE_H__