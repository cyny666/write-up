不得不感慨一些工具对于生产力的提升的举足轻重的作用！Wappalyzer是目前遇到最好的插件！！！

先用Wappalyzer插件分析文件体系结构![image-20240114104041970](./assets/image-20240114104041970.png)

Apache的一个关键点在于.htaccess,但是nginx的一个关键点在.user.ini

这个是.user.ini绕过，这里对.user.ini进行解释

## .user.ini

我们先在php手册上看一下对`.user.ini`的介绍：

也就是说我们可以在`.user.ini`中设置`php.ini`中**PHP_INI_PERDIR** 和 **PHP_INI_USER** 模式的 INI 设置，而且只要是在使用 **CGI／FastCGI** 模式的服务器上都可以使用`.user.ini`

在p牛的文章中提到了两个有趣的设置：**auto_prepend_file**和**auto_append_file**

我们再到手册中看了下这两个设置的定义：

大致意思就是：我们指定一个文件（如a.jpg），那么该文件就会被包含在要执行的php文件中（如index.php），**类似于在index.php中插入一句：`require(./a.jpg);`**

这两个设置的区别只是在于**auto_prepend_file**是在文件前插入；**auto_append_file**在文件最后插入（当文件调用的有`exit()`时该设置无效）

由于这里的审查有exif格式的审查，所以前缀放一个 GIF89a

.user.ini的文件内容

```
GIF89a
auto_prepend_file=a.jpg
```

a.jpg的文件内容

```
GIF89a
<script language='php'>system('cat /flag');</script>
```

这里有对于<?的过滤，所以采用script的方式执行php代码

然后访问该目录下的index.php即可获得flag，注意是访问Index.php因为这个.user.ini是在加载index.php之前执行了a.jpg，即执行了payload



