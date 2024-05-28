发现有一个特殊的url

```
/?page=about.html 
```

然后尝试一下LFI发现确实可以读取/etc/passwd

![image-20240516101630550](C:/Users/86186/Desktop/write-up/ctfs/TBTLCtf/assets/image-20240516101630550.png)

然后通过猜测获取flag的位置？一直考虑在怎么扩大这个利用

然后猜测flag为../flag.txt ???感觉有点难绷

然后发现

```
Flag is in SQLite3: database.sqlite
```

于是构造

```
/?page=database.sqlite
```

获取flag，如果是我出题，我一定放在proc/self/environ