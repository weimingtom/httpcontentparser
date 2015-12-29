# Introduction #

WTL安装


# Details #

1，从网上下载WTL 7.5 4291 版：http://sourceforge.net/projects/wtl/，得到wtl75_4291.zip

2，将wtl75\_4291.zip解压缩后，得到文件目录结构如下：
AppWiz
> AppWizCE 11,666 CPL.TXT
> > include 102,730


> readme.htm

> Samples

3，进入AppWiz目录，可以看到几个.js脚本文件，本来可以用这个安装的，但我想手工安装。所以不看他了。进入Files目录。此目录称为源路径$SOURCEDIR。准备开始安装了。
> （1）得到VC安装目录$VCDIR: 读注册表："HKLM\\Software\\Microsoft\\VisualStudio\\7.1\\Setup\\VC\\ProductDir"

> （2）将($SOURCEDIR)\WTLAppWiz.**总共三个文件 复制到 ($VCDIR)\vcprojects下。**

> （3）在($VCDIR)\vcprojects下创建目录 WTL

> （4）复制 WTLAppWiz.vsdir到刚创建的目录WTL下。并修改该文件内容： 找到“WTLAppWiz.vsz”，替换为：“..\WTLAppWiz.vsz”。存盘。

> （5）转到目录($VCDIR)\vcwizard,创建目录 WTLWiz (-->$WTLWiz)

> （6）复制($SOURCEDIR)\下的所有目录到刚创建的WTLWiz目录中去。

> （7）修改(($VCDIR)\vcprojects\WTLAppWiz.vsz文件， a，在“Wizard=VsWizard.VsWizardEngine”后添加“.7.1”，变成了“Wizard=VsWizard.VsWizardEngine.7.1” b，修改：Param="ABSOLUTE\_PATH = ."将 .变为 ($WTLWiz)代表的路径。如下： Param="ABSOLUTE\_PATH = D:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\VCWizards\WTLWiz"

> （8）将解压缩后得到的include目录下的所有头文件复制到 ($VCDIR)\atlmfc\include

> （9）安装成功。

### 方法二 ###

> WTL全称为Window Template Library,一个构架于ATL之上的C++类库,它包装了大多数的窗口控制.从网上看的,也只是个大概的了解.先安装了弄个Hello World试试吧,呵呵
1,安装
  1. 1 下个WTL安装包,其实上个压缩包.现在最新的是8.0版,默认解压目录为C:\WTL80,其中80为版本号,如果下的是7.5则为C:\WTL75
  1. 2 自动安装
> 在目录C:\WTL80\AppWiz有四个JS文件,选择一个你机子上安装的VC版本,点击相应的JS脚本进行安装即可,如VS2005的VC版本为8.0,则相应文件为setup80.js
  1. 3 手动安装
> 自动安装有时安装不成功,如点击文件后却打开了一个记事本,其实手动安装也挺不错的.
> 将C:\WTL80\AppWiz\Files目录下的三个WTLAppWiz.**文件考到VC安装目录的vcprojects目录下,如E:\Program Files\Microsoft Visual Studio 8\VC\vcprojects, 打开WTLAppWiz.vsz,原文件为:**


> VSWIZARD 7.0

> Wizard=VsWizard.VsWizardEngine

> Param="WIZARD\_NAME = WTLAppWiz"

> Param="WIZARD\_VERSION = 7.0"

> Param="ABSOLUTE\_PATH = ."

> Param="FALLBACK\_LCID = 1033"

> 将其改为
> VSWIZARD 7.0

> Wizard=VsWizard.VsWizardEngine.8.0

> Param="WIZARD\_NAME = WTLAppWiz"

> Param="WIZARD\_VERSION = 7.0"

> Param="ABSOLUTE\_PATH = C:\WTL80\AppWiz\Files"

> Param="FALLBACK\_LCID = 1033"

> 其中Wizard后面需加上WTL的版本号,否则能在VC里看到WTL项目,但其向导无法工作

> Param ="ABSOLUTE\_PATH后加上WTL解压的路径

> 新将项目时选择WTL项目,接默认选项生成项目，编译时会报'atlapp.h': No such file or directory错误。需要加一个编译路径，工具-->选项-->项目和解决方案-->VC目录，在左边选择包含文件，把WTL解压目录下的C:\WTL80\include路径加上

> 如果编译时报以下两个Bug：

> 错误 1 fatal error CVT1100: 重复的资源。type:MANIFEST, name:1, language:0x0409 CVTRES
> 错误 2 fatal error LNK1123: 转换到 COFF 期间失败: 文件无效或损坏 sdf
> > 则说明资源文件有问题，具体的原因未知，从网上找我资料看，有以下四种解决方法：

  1. 工程属性->配置属性-> 清单工具->输入和输出->嵌入清单，选择[否]


> 2，打开rc文件，找MANIFEST，所属段或行全去掉

> 3，打开此项目属性页，链接器-->嵌入的 IDL-->类型库资源 ID 设一个从1-65535的值

> 4，项目属性页链接器-->清单 文件-->生成清单文件 选项设置为no

> 在我的机子上第一、二种方法可以，三、四的不可以