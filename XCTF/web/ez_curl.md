打ctf后最不相信的就是easy这个词了

先获取到源码

```php
<?php
highlight_file(__FILE__);
$url = 'http://back-end:3000/flag?';
$input = file_get_contents('php://input');      //获取输入流数据
$headers = (array)json_decode($input)->headers;
for($i = 0; $i < count($headers); $i++){
    $offset = stripos($headers[$i], ':');           //key用来获取headers
    $key = substr($headers[$i], 0, $offset);		//value用来获取对应headers的值
    $value = substr($headers[$i], $offset + 1);
    if(stripos($key, 'admin') > -1 && stripos($value, 'true') > -1){
        die('try hard');
    }
}
$params = (array)json_decode($input)->params;
$url .= http_build_query($params);
$url .= '&admin=false';
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
curl_setopt($ch, CURLOPT_TIMEOUT_MS, 5000);
curl_setopt($ch, CURLOPT_NOBODY, FALSE);
$result = curl_exec($ch);
curl_close($ch);
echo $result;
```

然后又附一个app.js

```javascript
const express = require('express');

const app = express();

const port = 3000;
const flag = process.env.flag;

app.get('/flag', (req, res) => {
    if(!req.query.admin.includes('false') && req.headers.admin.includes('true')){
        res.send(flag);
    }else{
        res.send('try hard');
    }
});

app.listen({ port: port , host: '0.0.0.0'});

```

这里的话大概就是

先看一下php代码，有一个file_get_contents('php://input')，这是一个文件包含，当Content-Type为application/x-www-form-urlencoded且提交方法是POST方法时，$_POST数据与php://input数据是一致的。

然后会`$headers = (array)json_decode($input)->headers把post过去的数据解码成数组，很明显post的内容就是http请求里的headers，写post数据的时候要写成json的形式。像这样：

当我们传入的参数超过1000个时，之后的参数会被舍弃掉。于是这里我们最开始发个"admin":"t"设置好admin的值，加上999个没用的参数，把程序拼接的&admin=false挤掉，即可绕过过滤。

```php
有几个判断
    第一个就是 if(!req.query.admin.includes('false') && req.headers.admin.includes('true'))
        要求admin后面的查询参数不包含false 并且admin的请求头部包含true
第二个是
        stripos($key, 'admin') > -1 && stripos($value, 'true') > -1)
```

