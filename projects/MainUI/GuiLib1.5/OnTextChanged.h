#ifndef _GUI_LIB_ON_TEXT_CHANGED_H__
#define _GUI_LIB_ON_TEXT_CHANGED_H__

class OnTextChanged {
public:
	virtual void OnDelete(const CString &str)  = 0;
	virtual void OnBeginEdit(const CString &strOld) = 0;
	virtual bool OnEndEdit(const CString &strNew) = 0;
	virtual bool OnAdd(const CString &str)  = 0;
};

#endif  // _GUI_LIB_ON_TEXT_CHANGED_H__