凯撒密码罢了：

大概就是设置一个密钥i

然后每个字母的大概为平移i为（注意在小写字母中或者在大写字母中平移）

可以直接穷举：python脚本如下

```python
decoded_words = 'kimaizqaktiaaqkkqxpmz'
flag = []
for i in range(27):
    current_flag = ''
    for s in decoded_words:
        ascii_code = ord(s)-97
        ascii_code = (ascii_code-i) % 26 + 97
        current_flag += chr(ascii_code)
    flag.append(current_flag)
    print(current_flag)
```

然后发现目标单词：caesarisclassiccipher

即可提交flag