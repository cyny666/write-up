妈的，原来传递序列化对象的时候真的可以把引用传递过去

```php
<?php 
class unserialize1 {
    var $input;
    var $secret;
    function unserialize1()
    {
    $this->input=&$this->secret;
    }
    }
echo serialize(new unserialize1());
?>
```

输出这个O:12:"unserialize1":2:{s:5:"input";N;s:6:"secret";R:2;}**这里面的R2代表引用**

不加这个引用的话

```
O:12:"unserialize1":2:{s:5:"input";N;s:6:"secret";N;}
```