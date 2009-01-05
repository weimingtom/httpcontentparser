#ifndef _SYSUTILITY_REGISTERINFO_H__
#define _SYSUTILITY_REGISTERINFO_H__

class RegisterInfo {
public:
	RegisterInfo(void);
	~RegisterInfo(void);

	void repair();		// 修复
	bool intacted();	// 验证安装信息是否完整
private:
};

#endif  // _SYSUTILITY_REGISTERINFO_H__