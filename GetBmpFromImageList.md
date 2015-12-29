# Introduction #

想在菜单项上设置图标，貌似只能使用函数SetMenuItemBitmaps, 而此函数必须传入一个Bitmap。 但是图像都保存在CImageList当中了。

# Details #

突然发现CImageList中有一个GetBitmap函数