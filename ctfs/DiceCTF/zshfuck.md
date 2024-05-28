很符合misc的一道题，先给了zsh脚本文件的源码

```sh
#!/bin/zsh
print -n -P "%F{green}Specify your charset: %f"
read -r charset
# get uniq characters in charset
charset=("${(us..)charset}")
banned=('*' '?' '`')

if [[ ${#charset} -gt 6 || ${#charset:|banned} -ne ${#charset} ]]; then
    print -P "\n%F{red}That's too easy. Sorry.%f\n"
    exit 1
fi
print -P "\n%F{green}OK! Got $charset.%f"
charset+=($'\n')

# start jail via coproc
coproc zsh -s
exec 3>&p 4<&p

# read chars from fd 4 (jail stdout), print to stdout
while IFS= read -u4 -r -k1 char; do
    print -u1 -n -- "$char"
done &
# read chars from stdin, send to jail stdin if valid
while IFS= read -u0 -r -k1 char; do
    if [[ ! ${#char:|charset} -eq 0 ]]; then
        print -P "\n%F{red}Nope.%f\n"
        exit 1
    fi
    # send to fd 3 (jail stdin)
    print -u3 -n -- "$char"
done
```

就是根据zsh然后想办法执行getflag就可以了

先试一下find .,获取当前目录下的文件

```shell
root@cyny666:~# nc mc.ax 31774
Specify your charset: find .

OK! Got f i n d   ..
find .
.
./y0u
./y0u/w1ll
./y0u/w1ll/n3v3r_g3t
./y0u/w1ll/n3v3r_g3t/th1s
./y0u/w1ll/n3v3r_g3t/th1s/getflag
./run
```

然后想办法执行这个exe  ./y0u/w1ll/n3v3r_g3t/th1s/getflag

这里可以用字符匹配，但是禁用了*和?

于是可以用正则匹配

```
[--~][--~][--~]/[--~][--~][--~][--~]/[--~][--~][--~][--~][--~][--~][--~][--~][--~]/[--~][--~][--~][--~]/[--~][--~][--~][--~][--~][--~][--~]
```

然后即可执行这个文件