这题还挺有意思的

```php
<?php

require 'flag.php';

mt_srand(time());

if (intval($_GET['r1']) === mt_rand(0, 1 << 6) &&
  intval($_GET['r2']) === mt_rand(1 << 6, 1 << 12) &&
  intval($_GET['r3']) === mt_rand(1 << 12, 1 << 18) &&
  intval($_GET['r4']) === mt_rand(1 << 18, 1 << 24) &&
  intval($_GET['r5']) === mt_rand()) {
  echo $flag;
}

show_source(__FILE__);
```



大概就是用time()当种子产生随机数，手动实现time（）就行了，好一个伪随机数

payload

```php
<?php
mt_srand(time()+5);
$r1=mt_rand(0, 1 << 6);
$r2=mt_rand(1 << 6, 1 << 12);
$r3=mt_rand(1 << 12, 1 << 18);
$r4= mt_rand(1 << 18, 1 << 24);
$r5=mt_rand();
echo("http://web1.0ops.sjtu.cn:40036/rand1/index.php?".
"r1=".$r1."&r2=".$r2."&r3=".$r3."&r4=".$r4."&r5=".$r5);
```

