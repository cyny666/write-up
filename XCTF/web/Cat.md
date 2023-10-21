每次遇到一个以为很简单的题（确总是很难）:sleeping:

先打开（然后以为是命令行注入漏洞）后来发现自己太年轻

这里用bp进行一下fuzz测试（真的有用！！！）黑盒测试yyds

然后发现关键的几个点

输入@和宽字符都会有异常现象

宽字符会报错

可以将报错的html文件用html格式打开

发现是一个Django的报错

结合django的报错得知了项目的绝对路径为`/opt/api`

这里还需要懂一些django开发的基本知识，我感觉这道题涉及的面有点广了，django项目下一般有个settings.py文件是设置网站数据库路径（django默认使用的的是sqlites数据库），如果使用的是其它数据库的话settings.py则设置用户名和密码。除此外settings.py还会对项目整体的设置进行定义。

读取settings.py文件，这里需要注意django项目生成时settings.py会存放在以项目目录下再以项目名称命名的文件夹下面。

http://61.147.171.105:50031/index.php?url=@/opt/api/settings.py

http://61.147.171.105:50031/index.php?url=@/opt/api/database.sqlite3

然后可以用@读关键文件即可发现flag