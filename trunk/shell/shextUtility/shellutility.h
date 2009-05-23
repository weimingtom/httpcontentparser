#ifndef _SHELLUTILITY_H__
#define _SHELLUTILITY_H__

// 拷贝控制是否安装
bool isInstallCopyHook(); 
bool installCopyHook();
int uninstallCopyControl();

// AppControl是否安装
bool isInstallAppControl();
// 安装APP Control
int installAppControl();
int uninstallAppControl();



#endif  // _SHELLUTILITY_H__