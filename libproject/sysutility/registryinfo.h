#ifndef _SYSUTILITY_REGISTERINFO_H__
#define _SYSUTILITY_REGISTERINFO_H__

class RegisterInfo {
public:
	RegisterInfo(void);
	~RegisterInfo(void);

	void repair();		// �޸�
	bool intacted();	// ��֤��װ��Ϣ�Ƿ�����
private:
};

#endif  // _SYSUTILITY_REGISTERINFO_H__