#ifndef _SOFTWARE_ENCRYPT_LICENSEINFO_H__
#define _SOFTWARE_ENCRYPT_LICENSEINFO_H__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace software_encrypt {

const int MAX_DAYS = 0xFFFFFFFF;

class LicenseInfo {
public:
	LicenseInfo(void);
	~LicenseInfo(void);

public:
	int getInstallDays();	// ��ȡʱ������
	int getDaysLeft();	// ʣ�������ʹ��
	bool registered(); // �Ƿ��Ѿ�ע����

	void initialize();		// ��ʼ��
	bool regApp(const std::string &bstr);
	int getAppStatus();
private:
	//======================
	// һ����Ϣ��Ӧ��ֻ���ļ��ж�ȡһ��
	// �������ٴ����������ڷ�ֹ����¼ʱ��"�ĵص㱻����
	// ��װ����
	boost::posix_time::ptime install_time_;

	// ���к�
	std::string sn_;

	// ���ڵ���
	bool initialized_;
};

};

#endif  // _SOFTWARE_ENCRYPT_LICENSEINFO_H__