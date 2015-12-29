# Introduction #

我下网用户在窗口托盘之后或是选中托盘菜单之后能够激活主界面。

# Details #


### 1. 使用`SetWindowPos` ###
开始的时候我用的函数是, `ShowWindow(SW_SHOW)`, 发现窗口在任务栏出现了， 可是仍然在其他窗口后面，于是我又加上了一个SetWindowPos()发现他只是部分时间可以正常工作。

当用户鼠标右键单击菜单的时候激活窗口，它可以正常工作；但是当用户左键双击托盘图标的时候，并不能正常工作。此外还出现了另外一个问题，当用户从托盘退出程序的时候，主界面会闪烁一下，然后退出，我认为这可能是因为`SetWindowPos`导致的z-order紊乱的问题，因此在每次调用HideWindows()的时候，除了调用`ShowWindow(SW_HIDE)`; 我还添加了一个`SetWindowPos(&CWnd::wndBottom...)`, 这个问题就解决了。


### 2. 使用`SetActiveWindow()` ###
之后我在`SetWindowsPos()`之后增加了一个`SetActiveWindow()`函数，这时候第一次双击托盘图标，界面可以正常显示，但是之后再双击的时候，效果就跟之前的现象一样了。


### 3.使用`SetForegroundWindow()` ###
后来发现了这个函数，这个函数似乎可以完全满足要求了了， 尤其在他的remark当中有一句话“

The **SetActiveWindow** function activates a window, but not if the application is in the background. The window will be brought into the foreground — the top of z-order — if the application is in the foreground when it sets the activation.

**SetForegroundWindow** window function, on the other hand, activates a window and forces it into the foreground. An application should only call SetForegroundWindow if it needs to display critical errors or information that needs the user's immediate attention. ”