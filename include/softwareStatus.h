#ifndef _SNOWMAN_SOFTWARE_STATUS_H__
#define _SNOWMAN_SOFTWARE_STATUS_H__

// ���ļ������˰�װ����״̬�ĳ���
#define SNOWMAN_STATUS_REGISTERED		0x00000000			// �Ѿ�ע��
#define SNOWMAN_STATUS_TRIAL					0x00000001			// ����
#define SNOWMAN_STATUS_OVERTIME			0x00000002			// ���ð泬��
#define SNOWMAN_STATUS_UNINSTALL			0x00000003			// ж��
#define SNOWMAN_STATUS_UPDATE				0x00000004			// ����

inline bool functionEnabled(LONG status) {
	if (SNOWMAN_STATUS_OVERTIME == status ||
		SNOWMAN_STATUS_UNINSTALL == status) {
			return false;
		} else {
			return true;
		}
}

#endif  // _SNOWMAN_SOFTWARE_STATUS_H__