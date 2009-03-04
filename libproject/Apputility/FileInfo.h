#ifndef _APPUTILITY_CFILEINFO_H__
#define _APPUTILITY_CFILEINFO_H__

#include <string>
#include <utility\strutility.h>
// class CFileInfo
// ���ڻ�ȡ�ļ��İ汾��Ϣ�� ͼ���
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
	// �ļ�����
	strutility::_tstring filename_;

	// ͼ��
	HICON hIcon_;

	// ��Ʒ����
	strutility::_tstring product_name_;

	// ��˾����
	strutility::_tstring company_;

	// ������Ϣ
	strutility::_tstring description_;
};

#endif  // _APPUTILITY_CFILEINFO_H__