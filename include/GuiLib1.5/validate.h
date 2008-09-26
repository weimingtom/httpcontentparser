#ifndef _GUI_LIB_VALIDATE_H__
#define _GUI_LIB_VALIDATE_H__

// 验证数据是否有效
class ValidateData {
public:
	virtual bool validate(LPCTSTR str) = 0;
};


#endif  // _GUI_LIB_VALIDATE_H__