emm SQl注入不会啊:sob:

先打开然后看到用户的登录

然后尝试输入1'or'1'#这里注意到在账号或者密码部分输入这个都行

毕竟sql语句是这样的，唯一需要care的是在hackbar或者url中输入的时候要把#替换成%23,如果输入#可能会被hackbar和浏览器认为是注释

这里后面是选用了报错注入

SQL报错注入常用函数 两个基于XPAT（XML)的报错注入函数 函数updatexml() 是mysql对xml文档数据进行查询和修改的xpath函数

```sql
1'or(updatexml(1,concat(0x7e,database(),0x7e),1))#
```

然后后面即可获取flag的内容

语句的讲解：

1. `updatexml(1,concat(0x7e,database(),0x7e),1)` 是一个特定于 MySQL 的函数，用于更新 XML 文档。在这种情况下，它用于构建一个字符串，其中包含由 `0x7e` 字符（代表波浪线 `~`）括起的数据库名称。`concat` 函数用于连接这些元素。
2. `#` 是 SQL 中的注释字符。`#` 后的所有内容都被视为注释，数据库服务器会忽略它。