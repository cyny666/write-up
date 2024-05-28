感觉对SSRF攻击的理解有点问题，这次好好纠正一下

服务端请求伪造（Server Side Request Forgery, SSRF）指的是攻击者在未能取得服务器所有权限时，利用服务器漏洞以服务器的身份发送一条构造好的请求给服务器所在内网。SSRF攻击通常针对外部网络无法直接访问的内部系统。

指的是通过伪造网址为127.0.0.1或者localhost来伪造自己是一个内网环境中，故不用再进行认证

这篇文章讲的太好了：

https://portswigger.net/web-security/ssrf#what-is-the-impact-of-ssrf-attacks

这道题直接在check stock里面抓包修改为

http://localhost/admin/delete?username=carlos

即可

下次用英文搜索，英文的资料会好很多