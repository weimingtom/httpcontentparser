# Introduction #

Add your content here.


# Details #


代码
```
// str 为文件名称 
SHGetFileInfo(str,0,&sfi,sizeof(sfi),SHGFI_ICON|SHGFI_LARGEICON|SHGFI_USEFILEATTRIBUTES);
int i=sfi.iIcon;
CStatic* pStatic = (CStatic*) GetDlgItem(IDC_STATIC);
HICON hIcon=sfi.hIcon;
pStatic->SetIcon (hIcon);
```