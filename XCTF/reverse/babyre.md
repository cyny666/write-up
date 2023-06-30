SMC（Software-Based Memory Encryption）是一种局部代码加密技术，它可以将一个可执行文件的指定区段进行加密，使得黑客无法直接分析区段内的代码，从而增加恶意代码分析难度

SMC的基本原理是在编译可执行文件时，将需要加密的代码区段（例如函数、代码块等）单独编译成一个section（段），并将其标记为可读、可写、不可运行，然后通过某种方式在程序运行时将这个section解密为可执行代码，并将其标记为可读、可执行、不可写

SMC的主要步骤包括：

1.读取PE文件并找到需要加密的代码段

2.将代码段的内容进行异或加密，并更新到内存中的代码段

3.重定向代码段的内存地址，使得加密后的代码能够正确执行

4.执行加密后的代码段

具体加密执行方式：

```c
void fun()
{
    char flag[]="flag{this_is_test}"
     printf("%s",flag)
}
int main()
{
    byte *a=(byte *)fun;
    byte *b = a;
     for( ; a!=(b+0x401451-0x401410+1) ; a++ )
    {
        *a=*a^3;
    }
    fun();
        
}
```

这题的题解如下：

在ida中运行这个python脚本：

```python
s=0x600B00
for i in range(182):
    patch_byte(s+i,get_wide_byte(s+i)^0xC)
```

然后对judge函数进行操作，先用c生成新汇编，然后按p生成新的judge函数，再按F5反汇编即可

得到新的judge函数：

```c
qmemcpy(v2, "fmcd", 4);
v2[4] = 127;
qmemcpy(v3, "k7d;V`;np", sizeof(v3));
for ( i = 0; i <= 13; ++i )
*(_BYTE *)(i + a1) ^= i;
for ( i = 0; i <= 13; ++i )
{
if ( *(_BYTE *)(i + a1) != v2[i] )
return 0LL;
}
return 1LL;
```

编写脚本求解：

```python
# 使用新的字符串变量来保存解密后的结果
decode_flag = "fmcd\x7Fk7d;V`;np"
decoded_flag = ""
for i in range(14):
    decoded_flag += chr(ord(decode_flag[i]) ^ i)
print(decoded_flag)
```

