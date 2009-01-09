#ifndef _SPI_INSTALLER_SPIDEFINES_H__
#define _SPI_INSTALLER_SPIDEFINES_H__

#include <assert.h>

#define PACKETSGRASPER_DLL_NAME		_T("PacketsGrasper.dll")
#define REG_INSTALL_KEY				_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\PacketsCapture_SPI")
#define REG_INSTALL_PATH_ITEM		_T("PathName")
#define	REG_PROTOCOL_CATALOG_KEY	_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\Parameters\\Protocol_Catalog9\\Catalog_Entries")
#define REG_PROTOCOL_CATALOG_ITEM	_T("PackedCatalogItem")

// ����������װ��ע�����Ϣ
#define REG_SOFTWARE_DIR			_T("SOFTWARE\\family007")
#define REG_SOFTWARE_INSTALLPATH	_T("InstallPath")
#define REG_SOFTWARE_INSTALLDATE	_T("InstallKey")		// ��װ����

#define MAX_PROTOCOL_CATALOG_LENTH	sizeof(WSAPROTOCOL_INFOW) + MAX_PATH

#define SERVICE_FILENAME			_T("nwrs.exe")

#define PACKETSFILTERED_INSTALL_SUCC			0
#define	PACKETSFILTERED_FILE_NOT_FOUND			-800
#define PACKETSFILTERED_NOT_INSTALL				-801
#define PACKETSFILTERED_ALREADY_INSTALL			-802
#define PACKETSFILTERED_OPEN_REG_FAILED			-803
#define PACKETSFILTERED_SAVE_PATH_FAILED		-804
#define PACKETSFILTERED_READ_VALUE_FAILED		-805
#define PACKETSFILTERED_CREATE_ITEM_FAILED		-806
#define PACKETSFILTERED_SET_VALUE_FAILED		-807
#define PACKETSFILTERED_REG_DELETE_FAILED		-808

// ���ڷ���Service�������
#define COM_SERVICE_MUTEX	TEXT("7F6E3389-60CF-4b19-B1BD-BC6258E63BDC")

// Ӧ�ó��������
#define APPLICATION_MAINUI_NAME	TEXT("MainUI")

// ע���������
#define REGISTER_MAINUI_KEY	APPLICATION_MAINUI_NAME


// �ȼ�����
#define HOTKEY_LANUCH_MAINUI	100
#define	HOTKEY_SHOW_MAINUI		200
#define HOTKEY_SHOW_SWITCH_USER	300

#define CONFIG_HOTKEY_LAUNCH					TEXT("launch")
#define CONFIG_HOTKEY_SHOWUI					TEXT("showui")
#define CONFIG_HOTKEY_SWITCHUSER				TEXT("switchuser")

inline
TCHAR * getHotkeyname(const int type) {
	switch (type) {
		case HOTKEY_SHOW_MAINUI:
			return CONFIG_HOTKEY_SHOWUI;
		case HOTKEY_SHOW_SWITCH_USER:
			return CONFIG_HOTKEY_SWITCHUSER;
		case HOTKEY_LANUCH_MAINUI:
			return CONFIG_HOTKEY_LAUNCH;
		default:
			assert(false);
			return TEXT("");
	}
}

// Ӧ�ó���ĳ����� �������� ������

#define MAIN_WINDOW_TITLE (TEXT("MainUI"))
#define MAIN_WINDOW_CLASS (TEXT("#32770"))

#define MAIN_WINDOW_PROP_NAME	(TEXT("Unicode_value"))
#define MAIN_WINDOW_PROP_VALUE  7777

// for Eyecare windows
#define EYECARE_MAIN_WND_CLASS (TEXT("Eyecare_main_wnd_class"))
#define EYECARE_MAIN_WND_TITLE (TEXT(""))
#define EYECARE_MUTEX_NAME		TEXT("8EF40F9D-71A7-40d9-A229-599105419DAE")

#endif // _SPI_INSTALLER_SPIDEFINES_H__