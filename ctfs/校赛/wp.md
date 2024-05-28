# SJTU-CTF 2024 Writeup

[TOC]

## 个人信息
平台用户名：cyny666
总排名：19

## WEB

## PWN


## REVERSE

## CRYPTO

## MISC

### Boy's Bullet

直接修改图片的exif元信息即可，耗时最长的是找一张含exif元信息的照片，这时候he3的作用就体现出来了

把这个照片下载下来

![image-20240415162952632](C:/Users/86186/Desktop/%E6%A0%A1%E8%B5%9B/assets/image-20240415162952632.png)

然后修改exif 修改时间为2038即可

![image-20240415163045394](C:/Users/86186/Desktop/%E6%A0%A1%E8%B5%9B/assets/image-20240415163045394.png)

### RealOrNot

google识图然后手动标记picture的real or not

然后跑exp就可以了(data.txt是手动标注的一些数据，感觉数据库比较少就手动标记了)

```python
局from pwn import *
import hashlib
import random
import string
import re
import base64
import os
def verify_pow_solution(challenge, solution, prefix):
    guess = solution + challenge
    guess_hash = hashlib.sha256(guess.encode()).hexdigest()
    return guess_hash.startswith(prefix)
while(True):
    # 创建一个本地进程
    p = process('/bin/sh')

    # 发送命令
    p.sendline("nc -X connect -x instance.penguin.0ops.sjtu.cn:18081 hhhw6fgv6c8pgg6k 1")

    # 接收输出
    output = p.recvline()
    # 使用正则表达式匹配并提取目标字符串
    pattern = rb"PoW Challenge: SHA256\(solution \+ '(.*?)'\) must start with '0000'"
    match = re.search(pattern, output)
    challenge = match.group(1).decode()

    prefix = '0000'
    while(True):
        solution = ''.join(random.choices(string.ascii_letters + string.digits, k=16))
        if verify_pow_solution(challenge, solution, prefix):
            break
    p.sendline(solution)
    data = {}
    with open("data.txt") as f:
        lines = [line.rstrip() for line in f.readlines()]

    for line in lines:
        line_parts = line.split(" ")  # 使用空格分隔每一行的数据
        data[line_parts[0]] = line_parts[-1]
    answer = []
    for _ in range(20):
        filename = f'image{_}.png'
        p.recvuntil("Is this picture real or not (Y/N)? \n")
        image_data = p.recvuntil("\n")
        # 解码Base64图像数据
        decoded_data = base64.b64decode(image_data)

        # 将解码后的数据保存到文件
        with open(filename, "wb") as file:
            file.write(decoded_data)
        # 获取文件大小
        file_size = os.path.getsize(filename)
        value = data.get(str(file_size))
        if value is not None:
            answer.append(value)
        else:
            answer.append("N")
            print(file_size)
            print(filename)


    # 关闭进程
    p.recv()
    result = ''.join(answer)
    p.sendline(result)
    output = p.recv()
    print(output)
    if "flag" in str(output):
        print(output)
        break
```

### RealOrNotRevenge

跟上面那道题一样，略微修改代码直接跑exp

```python
from pwn import *
import hashlib
import random
import string
import re
import base64
import os
def verify_pow_solution(challenge, solution, prefix):
    guess = solution + challenge
    guess_hash = hashlib.sha256(guess.encode()).hexdigest()
    return guess_hash.startswith(prefix)
while (True):
    # 创建一个本地进程
    p = process('/bin/sh')

    # 发送命令
    p.sendline("nc -X connect -x instance.penguin.0ops.sjtu.cn:18081 pqhtth4x4tgmmqr6 1")

    # 接收输出
    output = p.recvline()
    # 使用正则表达式匹配并提取目标字符串
    pattern = rb"PoW Challenge: SHA256\(solution \+ '(.*?)'\) must start with '00000'"
    match = re.search(pattern, output)
    challenge = match.group(1).decode()

    prefix = '00000'
    while(True):
        solution = ''.join(random.choices(string.ascii_letters + string.digits, k=16))
        if verify_pow_solution(challenge, solution, prefix):
            break
    p.sendline(solution)
    data = {}
    with open("data.txt") as f:
        lines = [line.rstrip() for line in f.readlines()]

    for line in lines:
        line_parts = line.split(" ")  # 使用空格分隔每一行的数据
        data[line_parts[0]] = line_parts[-1]
    answer = []
    for _ in range(20):
        filename = f'image{_}.png'
        p.recvuntil("Is this picture real or not (Y/N)? \n")
        image_data = p.recvuntil("\n")
        # 解码Base64图像数据
        decoded_data = base64.b64decode(image_data)

        # 将解码后的数据保存到文件
        with open(filename, "wb") as file:
            file.write(decoded_data)
        # 获取文件大小
        file_size = os.path.getsize(filename)
        value = data.get(str(file_size))
        if value is not None:
            answer.append(value)
        else:
            answer.append("N")
            print(file_size)
            print(filename)


    # 关闭进程
    p.recv()
    result = ''.join(answer)
    p.sendline(result)
    output = p.recv()
    if "flag" in str(output):
        print(output)
        break
    print(output)

```

