~~在给我点时间，一定能做出来~~

先用dirsearch扫一下发现有一个.DS_Store文件

.DS_Store 是 Mac OS 保存文件夹的自定义属性的隐藏文件。

**通过.DS_Store可以知道这个目录里面所有文件的清单。**

.DS_Store可以直接使用记事本打开，但是打开后乱码居多；也可以使用 Python-dsstore 这个工具 (https://github.com/gehaxelt/Python-dsstore) 来完成 .DS_Store 文件的解析，直观一些

后来发现目录下有flag文件

凑md5特定后缀的如下(还挺快--意料之外)

```python
import hashlib

target_suffix = "04b02f"

# 循环生成字符串并计算哈希值
i = 0
while True:
    # 构造字符串
    string = str(i)
    # 计算哈希值
    hash_value = hashlib.md5(string.encode()).hexdigest()
    # 提取哈希值的后六位
    suffix = hash_value[-6:]
    # 检查是否符合条件
    if suffix == target_suffix:
        break
    i += 1

print("生成的字符串:", string)
print("对应的哈希值:", hash_value)
```

然后用url编码和file协议即可获取flag

file:///%66%6c%61%67