#ifndef _FILTERSETTING_REGISTERINFO_H__
#define _FILTERSETTING_REGISTERINFO_H__

#include <string>

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

	// ע����Ϣ�Ƿ�ɹ�
	bool registerSoft(const std::string & register_info);
public:
	// �Ӽ������Ϣ�ж�ȡע����Ϣ
	void initialize();
private:
	// ʱ������
	int edition_type_; // �汾����
};

#endif  // _FILTERSETTING_REGISTERINFO_H__
