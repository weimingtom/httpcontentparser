# Introduction #

当将SPI安装在一个新的操作系统之上时， 很有可能不能使用。
这其中有很多原因


# Details #

1. 没有安装动态库
> 在原始版本中， 这个包使用了MSVCP.dll（/MD）这个动态库。 当你打开IE或者firefox时，不会显示任何提示，但打不开网页。 当你使用google chrome时， 他就会给提示，说“缺少动态库".