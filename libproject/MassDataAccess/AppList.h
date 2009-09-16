#ifndef  _APPLIST_H__
#define _APPLIST_H__

#include <utility\strutility.h>
#include <map>

class ApplicationList   {
public:
	ApplicationList(void);
	~ApplicationList(void);

public:
		// Ӧ�ó��������
	typedef struct _tagFileInfo {
	}FILEINFO;
public:

	// ����һ��Ӧ�ó�����
	int add_item(const strutility::_tstring &fullpath);
	int remote_item(const strutility::_tstring &fullpath);

	// ö����
	int get_first_item(strutility::_tstring *name, FILEINFO**);
	int get_next_item(const strutility::_tstring & cur, strutility::_tstring *name, FILEINFO**);
private:
	typedef std::map<strutility::_tstring, FILEINFO * > PROGRAM_INFO;
	PROGRAM_INFO data_;
};

#endif  // _APPLIST_H__