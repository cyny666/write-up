源码如下

```php
<?php

error_reporting(0); 

require 'flag.php';

$str = $_GET['O_O'] ?? false;

if(!$str) {
  highlight_file(__FILE__);
  die();
}

if (stristr($_SERVER['QUERY_STRING'], "O_O") !== false) {
  die();
}

if ($str < 0xffffffff) {
  die();
} 

if ((string)$str > 0) {
  die();
}

echo $flag;
```

ps:跟2018“安恒杯”WEB安全测试秋季资格赛的题目真像（合理怀疑抄袭）

首先需要生成一个GET请求并且参数为O_O,但是第二个判断要求GET请求的参数不能为O_O,PHP的特性会把.替换为_

然后后面两个判断也要满足，可以使$str为一个数组，由于类型不同无法判断，所以一定会不成立