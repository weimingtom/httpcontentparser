# Introduction #

我们希望用户能够制定一些应用程序，在家长模式下可以运行而在孩子模式下不能运行。

方法主要有两个

1. 对CreateProcess函数增加一个HOOK

2. 直接使用windows提供的SHell，但是它只能控制使用ShellExecute函数启动的程序


在使用ShellExecute的时候，如果我们返回S\_OK, 则所有的操作都将由你实现的接口完成，换句话说，如果你想拦截这个程序阻止他的创建，只需要简单的返回S\_OK即可。如果你返回S\_FALSE， 则ShellExecute及ShellExecuteEx则会继续执行正常创建。

再使用这个Shell extenton的时候，只需要在注册表项
HKEY\_LOCAL\_MACHINE\Software\Microsoft\Windows\Current Version\Explorer\ShellExecuteHooks中添加新项

其名称为实现IShellExecuteHook的class的CLSID， 类型为REG\_SZ。

添加后重启外科，COM组件将被启动


# Details #

IShellExecuteHook Interface

Exposes a method that extends the behavior of the ShellExecute or ShellExecuteEx functions. It is typically implemented by subsystems that expose the names of objects that the user can specify in the Run dialog box after clicking the Microsoft Windows Start button.

**Note**  Shell execute hooks are deprecated as of Windows Vista.


**Remark**


You should implement IShellExecuteHook when you have named objects that the user would expect to be able to run from the Run dialog box after clicking the Windows Start button.

Shell execute hooks are registered by adding a value that contains the object's class identifier (CLSID) string under the following key in the registry:

HKEY\_LOCAL\_MACHINE
> Software
> > Microsoft
> > > Windows
> > > > Current Version
> > > > > Explorer
> > > > > > ShellExecuteHooks

You do not use this interface directly. It is generally used by the ShellExecuteEx function's code.