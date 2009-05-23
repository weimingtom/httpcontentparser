#include "StdAfx.h"
#include ".\shellexttest.h"
#include <shell\shellutility.h>

ShellExtTest::ShellExtTest(void) {
	copyhook_installed = isInstallCopyHook();
	appcontrol_installed =isInstallAppControl() ;
}

ShellExtTest::~ShellExtTest(void) {
	if (copyhook_installed) {
		installCopyHook();
	} else {
		uninstallCopyControl();
	}

	if (appcontrol_installed) {
		installAppControl();
	} else {
		uninstallAppControl();
	}
}


void ShellExtTest::testShellExt() {
	uninstallAppControl();
	CPPUNIT_ASSERT(false == isInstallAppControl());
	installAppControl();
	CPPUNIT_ASSERT(true == isInstallAppControl());

	uninstallCopyControl();
	CPPUNIT_ASSERT(false == isInstallCopyHook());
	installCopyHook();
	CPPUNIT_ASSERT(true == isInstallCopyHook());
}