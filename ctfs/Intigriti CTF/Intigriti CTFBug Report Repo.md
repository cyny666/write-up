---
title: Intigriti CTFBug Report Repo 
date: 2023-12-21 15:52:25
categories:
  - WriteUp
tags:
  - Web

---

挺难的一道题，也挺有意思的一道题，发篇博客复现一下，主要考察webscoket注入+JWT伪造

先打开一下环境

![image-20231223192353902](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223192353902.png)

然后发现是一个基于websocket实时通讯的一个bug report平台，这里输入一个ID，然后服务器即可返回将这个高亮

需要注意的是ID=11的时候有一个好玩的显示，感觉这里的ethical_hacker是提示

![image-20231223192518962](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223192518962.png)

然后可以用bp抓包其实感觉websocket的抓包和普通的sql注入是差不多的？

这里又做了下载bp的破解版+给chrome导入bp的证书，突然发现bp是可以截取webscoket信息的，比在js上调试好多了，不知道为什么bp截取https总会很慢 不知道是网站问题还是我bp的问题（略微倾向一点网站的问题）真的好奇怪 就我改成系统代理立马就好了，但是用bp的代理就会卡很久、但是最后还是好了，不懂

![](https://notes.sjtu.edu.cn/uploads/upload_f00a80c2e3daf61aa87ba75f2e349208.png)

然后可以用sqlmap进行注入分析，sqlmap真是神

```shell
sqlmap --random-agent -u 'wss://bountyrepo.ctf.intigriti.io/ws' --data '{"id":"11"}' --dbms sqlite -T "bug_reports" --threads 10 --dump --where "id=11" --batch
```

这些参数的介绍

* -random-agent：指随机agent
* -u:后面加URL，这里是指webscoket的服务器端
* -data：`sqlmap` 中的 `-d` 或 `--data` 参数用于指定要用于 POST 请求的数据。在 Web 应用程序渗透测试中，你可能会遇到需要检测和利用 POST 请求中的 SQL 注入漏洞的情况。使用 `-d` 参数，你可以向 `sqlmap` 提供 POST 请求的数据，以便它能够分析和测试可能存在的 SQL 注入漏洞。
* -dbms:指数据库
* -T: 应该是table
* --threads:指多线程
* --dump：指将数据展示出来

然后即可注出漏洞！感觉脚本小子真好

![](https://notes.sjtu.edu.cn/uploads/upload_6a9278bb593bfc9351ebaff070dd6d57.png)

发现这个：crypt0:c4tz on /4dm1n_z0n3, really?!

然后登录

https://bountyrepo.ctf.intigriti.io/4dm1n_z0n3/

输入账号和密码

![](https://notes.sjtu.edu.cn/uploads/upload_015f2fce5d92d4eba06e93f96c839dca.png)

然后发现不是admin，然后查看cookie发现是jwt

![image-20231223194310779](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223194310779.png)

然后用jwt tools爆破获取密钥

这里加个插曲，平时一个人用root跟普通用户习惯了，忘记普通用户的python环境和root不一样了

![](https://notes.sjtu.edu.cn/uploads/upload_9dc8139afb9a358b68ff1f38b8707ec8.png)

爆破出来密钥为catsarethebest，然后伪造admin

![image-20231223194518709](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223194518709.png)

修改cookie即可获得flag

