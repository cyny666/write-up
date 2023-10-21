ext3是Linux的一种硬盘格式，是一个[日志文件系统](https://zh.wikipedia.org/wiki/日志文件系统)，常用于[Linux操作系统](https://zh.wikipedia.org/wiki/Linux操作系统)。它是很多[Linux发行版](https://zh.wikipedia.org/wiki/Linux发行版)的默认[文件系统](https://zh.wikipedia.org/wiki/文件系统)。[史提芬·崔迪](https://zh.wikipedia.org/wiki/史提芬·崔迪)在1999年2月的内核邮件列表[[2\]](https://zh.wikipedia.org/zh-hans/Ext3#cite_note-2)中，最早显示了他使用扩展的[ext2](https://zh.wikipedia.org/wiki/Ext2)，该文件系统从2.4.15版本的内核开始，合并到内核主线中[[3\]](https://zh.wikipedia.org/zh-hans/Ext3#cite_note-3)。

ext3文件相当于Linux的一块磁盘，可以挂载

然后用mount挂载在一个文件夹上，即可打开文件夹获取内容

然后find -n 'flag*'即可获取flag.txt的地址，即可用base64解码获得flag