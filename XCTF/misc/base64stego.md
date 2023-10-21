大概就是先解密zip文件，是一个伪加密

压缩源文件目录区： 50 4B 01 02：目录中文件文件头标记

 3F 00：压缩使用的 pkware 版本 

14 00：解压文件所需 pkware 版本 

00 00：全局方式位标记（有无加密，这个更改这里进行伪加密，改为09 00打开就会提示有密码了） 压缩源文件目录结束标志 ：50 

4B 05 06：目录结束标记 把09 00改写成00 00就可以成功解压了

然后就是一个base64隐写

```python
base64chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'

flag = ''
with open('stego.txt', 'r') as f:
    for line in f.readlines():
        line = line[:-1]
        num = line.count('=')
        if num == 0:
            continue
        lastchar = line[-(num + 1)]

        # print(line,num,lastchar)
        myindex = base64chars.index(lastchar)
        # print(myindex)
        bin_str = bin(myindex)[2:].zfill(6)
        # print(bin_str)
        flag += bin_str[6 - 2 * num:]
        # print(bin_str[6-2*num:])
print(''.join([chr(int(flag[i:i + 8], 2)) for i in range(0, len(flag), 8)]))

```

