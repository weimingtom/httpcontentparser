#ifndef _APPUTILITY_CFILEINFO_H__
#define _APPUTILITY_CFILEINFO_H__

#include <string>
#include <utility\strutility.h>
// class CFileInfo
// 用于获取文件的版本信息， 图标等
class CFileInfo {
public:
	CFileInfo(const strutility::_tstring &filename);
	~CFileInfo(void);

public:
	const HICON getICON() const { return hIcon_;}
	const strutility::_tstring & getFilePath() const {return filename_;}
	const strutility::_tstring & getProductName() const { return product_name_;}
	const strutility::_tstring & getCompanyName() const { return company_;}
	const strutility::_tstring & getDescription() const { return description_;}

protected:
	void getInformation();
protected:
	// 文件名称
	strutility::_tstring filename_;

	// 图标
	HICON hIcon_;

	// 产品名称
	strutility::_tstring product_name_;

	// 公司名称
	strutility::_tstring company_;

	// 描述信息
	strutility::_tstring description_;
};

#endif  // _APPUTILITY_CFILEINFO_H__