# Introduction #

如何调试外科程序


# Details #

在完成外壳程序之后，添加外科程序配置，如在指定的注册表项中添加一个CLSID， 之后开始菜单中选择关机，按住‘Atl + Ctrl + Shift' 并点击“关机"对话框上的取消按钮，这时候外壳程序explorer.exe就结束了，而且不会再自动启动。

切换到visual studio启动，调试程序，在调试程序中指定程序为c:\\windows\\explorer.exe

OK啦