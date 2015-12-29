# Introduction #

本文主要介绍windows下的编码装欢


# Details #

其实在windows下， MultiByteToWideChar提供了所有的编码装换方法，当然有些编码不能互相转换。例如同为MCBS，不可能直接用这个函数转换。 这时候可以通过UTF16作为中介，先将字符转换为宽字符，再换变回来的方法进行编码转换。

```
int MultiByteToWideChar(
  UINT CodePage, 
  DWORD dwFlags,         
  LPCSTR lpMultiByteStr, 
  int cbMultiByte,       
  LPWSTR lpWideCharStr,  
  int cchWideChar        
);

int WideCharToMultiByte(
  UINT CodePage, 
  DWORD dwFlags, 
  LPCWSTR lpWideCharStr,
  int cchWideChar, 
  LPSTR lpMultiByteStr, 
  int cbMultiByte,
  LPCSTR lpDefaultChar,    
  LPBOOL lpUsedDefaultChar
);

```

第一个参数是MCBS的codepage, 因为对于宽字符来说codepage其实并不重要，他就是UTF-16.
具体codepage的定义可以在ms-help://MS.MSDNQTR.v90.en/intl/unicode\_81rn.htm（MSDN找到）

第二个参数一般设置为0，不过通过这个参数你可以做一些列事情，例如
WC\_ERR\_INVALID\_CHARS(after vista), 如果字符里有错， 他会返回
。。。详细的请查看MSDN

之后的四个参数意思狠命相，就是原字符串和目的字符串


另外， 宽字符多了两个参数，这是因为在宽字符转换为MCBS的时候，缓冲区的大小跟实际分配的可能有出入。如果没有分配足够大的缓冲区给宽字符转换，那么他会通过后两个参数来通知你相关的情况。

这是一些常用的codepage
|code page | name |
|:---------|:-----|
| 950      | big5 |
| 936      | gb2312 |
|1200      | utf16|
| 12000    | utf32|
| 65001    | uft8 |
| 54936    | GB18030 |