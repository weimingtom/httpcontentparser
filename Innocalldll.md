# Introduction #

Inno setup提供了调用DLL的方法。本文主要介绍如何使用它调用DLL


# Details #

1. 隐式调用
> 隐式调用有些类似于C++的隐式调用，但是inno setup不支持include头文件。它采用了另外一种申明的方式。
> 你可以在[code](code.md)下加上一下声明

function CheckProgram(lpStatus: String):Integer;
external 'CheckProgram@{app}\wsut.dll stdcall uninstallonly';

function CheckStatus(lpStatus: String):Integer;
external 'CheckStatus@{app}\wsut.dll stdcall uninstallonly';

function CallUtility(lpStatus: String):Integer;
external 'CallUtility@{app}\wsut.dll stdcall uninstallonly';

> 然后再你的函数就可以直接调用了。

2. 显式调用，
> 与C++相同， inno setup提供了一个函数类似于LoadLibrary和GetProcAddress

3. 注意
> 由于C的函数默认使用ccall，而innosetup使用stdcall, 因此在你DLL的函数声明和定义是应该叫上 stdcall, 否则会出现调用错误。