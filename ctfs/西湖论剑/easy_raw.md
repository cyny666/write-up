---
title: easy_raw
date: 2023-12-21 15:52:25
categories:
  - WriteUp
tags:
  - Forensics

---

感觉要在取证的路上越走越远了hhh

先分析raw文件的系统

```shell
vol.py -f rawraw.raw imageinfo
```

然后发现是Win7SP1x64，从此以后都要加上--profile=Win7SP1x64 了

然后查看进程

```shell
vol.py -f rawraw.raw --profile=Win7SP1x64 pslist
```

发现可疑进程  WinRAR.exe和 VeraCrypt.exe

然后查看cmdline

```shell
vol.py -f rawraw.raw --profile=Win7SP1x64 cmdline
```

发现Command line : "C:\Program Files\WinRAR\WinRAR.exe" "C:\Users\Administrator\Documents\pass.zip"

把一个pass.zip压缩了，把这个进程dump出来

```shell
vol.py -f rawraw.raw --profile=Win7SP1x64 memdump -p 2088 -D output_directory
```

然后发现一个pass.txt加密的

![img](https://notes.sjtu.edu.cn/uploads/upload_bc8786a594a3bdef87084a71529923b3.png)

然后有个提示为Have a good New Year!!!

然后输入新年的那一天

20240210

然后破解成功

然后查看编辑栏 clipboard -v 获得secret的密码为

![img](https://notes.sjtu.edu.cn/uploads/upload_27903a5af83b9503c6e4a055170fe16e.png)

密码为 `DasrIa456sAdmIn987`使用密码 `DasrIa456sAdmIn987` 对 mysecretfile.rar 进行解压，获得 mysecretfile 文件

然后感觉为VeraCrypt加密

[VeraCrypt](https://www.veracrypt.fr/) 是一个开源的磁盘加密工具，用于创建加密容器和加密整个磁盘分区。它是 TrueCrypt 项目的继任者

然后把pass.txt当做密钥解密发现一个data.xslk然后用vol的插件mimikatz即可获取密码，打开搜索flag即可获得

这里吐槽一下mimikatz这个插件装了好久！！！啊啊啊python2的东西装的好麻烦啊

要不是mimikatz太重要了，一定就去用系统配置的了