---
title: EnableMe
date: 2024-02-09 13:56:12
categories:
  - WriteUp
tags:
  - Forensics
---

给了一个docm后缀的文件。然后搜索得知 启用宏的Microsoft Word 文档

宏也就是可以执行一些代码（也就是用于勒索）

这里打开后然后出现了一个

![img](https://notes.sjtu.edu.cn/uploads/upload_016339c996f73e45e0b9ba1d86946943.png)

意思是被勒索了是吧hhh

然后查看宏文件，这里可以利用[olevba](https://github.com/decalage2/oletools/wiki/olevba)来查看文件，丢一篇这个软件的[介绍](https://medium.com/r3d-buck3t/extracting-macros-with-oletools-6c3a64c02549)然后即可分析

![img](https://github.com/HashemSalhi/CTF-Writeups/raw/main/UofTCTF%202024/Forensics/EnableMe/Screenshots/Screenshot1.png)

然后在word里面编辑

![](https://notes.sjtu.edu.cn/uploads/upload_763e058d7d5dd3372505e79537f704c1.png)

即可弹出flag
