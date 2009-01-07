#ifndef _FILTERSETTING_REGISTERINFO_H__
#define _FILTERSETTING_REGISTERINFO_H__

#include <string>
#include <atltime.h>

#define SOFTWARE_EDITION_TRIAL		 0x100000F
#define SOFTWARE_EDITION_REGISTERED  0x1000000

// �û���ע����Ϣ
// �û���ϢӦ�ñ�����һ���ļ�����
class RegisterInfo {
public:
	RegisterInfo(void);
	~RegisterInfo(void);

	// �Ƿ��Ѿ�ע��
	bool registered() const {
		return SOFTWARE_EDITION_REGISTERED == edition_type_;
	}

	int getEditionType() const {
		return edition_type_;
	}

	bool trial_ended();

	// ע����Ϣ�Ƿ�ɹ�
	bool registerSoft(const std::string & register_info);
public:
	// �Ӽ������Ϣ�ж�ȡע����Ϣ
	void initialize();

private:
	bool trialEdition();
	void getInstallTime();
private:
	// ʱ������
	int edition_type_; // �汾����

	CTime install_date; // ��װ����
};

#endif  // _FILTERSETTING_REGISTERINFO_H__
