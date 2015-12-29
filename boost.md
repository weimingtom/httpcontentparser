#Boost no libaray

# Introduction #

Boost为了达到编译器独立的目的，大量使用了基于头文件的库。只有少数几个库需要编译，其他都可以直接使用.h文件进行编译。但是有时候这样也会提示没有lib文件。此时只需要加上一个预定义

> /D BOOST\_ALL\_NO\_LIB