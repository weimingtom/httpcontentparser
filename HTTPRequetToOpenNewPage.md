# Introduction #

识别打开网页的包


# Details #

一下是几个打开网页的包， 可以发现他打开请求的网址非常简单。经过仔细观察我们发现， 其中的Host+Get就是浏览器地址拦中的地址。 既然是这样，我们可以很容易的总结出规律， 地址栏中出现的后缀可以是
1. 什么都没有
2. php, asp, aspx,jsp之类的

而其他的请求通常请求的是 .jpg, .gif, .png, .js, .swt, .bmp, .css之类的内容。当然有些请求也会发送html网页。因此我们只能对这几类非网页内容的东西确认，他们不是打开新的网页。


也许我们还能从Accept当中找到些东西， 但是我不确信。


以下是我们收集的一些打开网页的包

// 第一次打开网页

GET / HTTP/1.1

Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/xaml+xml, application/vnd.ms-xpsdocument, application/x-ms-xbap, application/x-ms-application, application/msword, application/vnd.ms-excel, application/vnd.ms-powerpoint, **/**

Accept-Language: zh-cn

Accept-Encoding: gzip, deflate

Host: www.sogou.com

Connection: Keep-Alive


// 打开一个网页

GET /SkinChange/?p=40030117& HTTP/1.1

Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/xaml+xml, application/vnd.ms-xpsdocument, application/x-ms-xbap, application/x-ms-application, application/msword, application/vnd.ms-excel, application/vnd.ms-powerpoint, **/**

Referer: http://www.sogou.com/

Accept-Language: zh-cn

Accept-Encoding: gzip, deflate

Host: www.sogou.com

Connection: Keep-Alive



// google网页
// 注意期望值为 http://www.google.com/support/accounts/?hl=zh-CN

GET /support/accounts/?hl=zh-CN HTTP/1.1

Host: www.google.com

Connection: keep-alive