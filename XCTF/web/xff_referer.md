主要是对xff和refer的伪造

X-Forwarded-For (XFF) 是一个 HTTP 请求标头，用于识别客户端的原始 IP 地址。当请求通过代理服务器或负载均衡器时，原始客户端的 IP 地址会被替换为代理服务器的 IP 地址。通过 XFF 标头，可以获取到客户端的真实 IP 地址，尤其在多层代理的情况下。

Referer（有时写作 "Referrer"）是一个 HTTP 请求标头，用于指示请求的来源页面。当用户通过点击链接或提交表单等方式访问某个页面时，浏览器会在发送请求时附带 Referer 标头，其中包含了来源页面的 URL 信息。这对于网站分析和跟踪用户来源非常有用。

需要注意的是，XFF 和 Referer 标头都可以被修改或伪造，因此在进行安全相关的操作时，不能完全依赖于它们的值。

伪造后的数据包：

GET / HTTP/1.1
Host: 61.147.171.105:50549
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
X-Forwarded-For: 123.123.123.123
Referer:https://www.google.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.5845.97 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Connection: close