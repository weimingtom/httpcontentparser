#ifndef _SNOWMAN_SOFTWARE_STATUS_H__
#define _SNOWMAN_SOFTWARE_STATUS_H__

// 及文件保存了安装程序状态的常量
#define SNOWMAN_STATUS_REGISTERED		0x00000000			// 已经注册
#define SNOWMAN_STATUS_TRIAL					0x00000001			// 试用
#define SNOWMAN_STATUS_OVERTIME			0x00000002			// 试用版超期
#define SNOWMAN_STATUS_UNINSTALL			0x00000003			// 卸载
#define SNOWMAN_STATUS_UPDATE				0x00000004			// 升级

inline bool functionEnabled(LONG status) {
	if (SNOWMAN_STATUS_OVERTIME == status ||
		SNOWMAN_STATUS_UNINSTALL == status) {
			return false;
		} else {
			return true;
		}
}

#endif  // _SNOWMAN_SOFTWARE_STATUS_H__